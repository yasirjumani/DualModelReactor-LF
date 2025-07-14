#!/usr/bin/env python3
import pandas as pd
import subprocess
import os
import time
import sys
import argparse

# Helper to assert file existence
def assert_file(path):
    if not os.path.exists(path):
        print(f"[ERROR] File not found: {path}")
        sys.exit(1)

# Argument parsing for aggregation and threshold
parser = argparse.ArgumentParser(
    description="Batch run predictor over all wafers and steps with configurable aggregation and threshold"
)
parser.add_argument("--csv", default="D1.csv", help="Path to D1.csv dataset")
parser.add_argument("--model-dir", default="models", help="Directory of serialized models")
parser.add_argument("--agg", choices=["mean", "median", "max"], default="mean",
                    help="Aggregation method for per-sample probabilities")
parser.add_argument("--threshold", type=float, default=0.5,
                    help="Threshold for classifying abnormal")
args = parser.parse_args()

# Configuration
CSV_PATH = args.csv
MODEL_DIR = args.model_dir
MODEL_PREDICTOR = "src/model_predictor.py"

# Verify CSV exists
assert_file(CSV_PATH)

df_all = pd.read_csv(CSV_PATH)

# Determine dynamic step sequence based on actual data
unique_steps = sorted(df_all["StepID"].unique())
pre_step = -1 if -1 in unique_steps else None
post_step = -2 if -2 in unique_steps else None
core_steps = [s for s in unique_steps if s not in (pre_step, post_step)]

STEPS = []
if pre_step is not None:
    STEPS.append(pre_step)
STEPS.extend(core_steps)
if post_step is not None:
    STEPS.append(post_step)

print(f"Running steps in order: {STEPS}")

# Required columns
required_cols = {"MaterialID", "StepID", "duration_ms"} | {f"feature_{i}" for i in range(1, 16)}
if not required_cols.issubset(df_all.columns):
    missing = required_cols - set(df_all.columns)
    print(f"[ERROR] Dataset missing required columns: {', '.join(sorted(missing))}")
    sys.exit(1)

wafer_ids = df_all["MaterialID"].unique()
results = []
total_wafers = len(wafer_ids)

for idx, wafer_id in enumerate(wafer_ids, start=1):
    wafer_start = time.time()
    wafer_rows = df_all[df_all["MaterialID"] == wafer_id]
    target = int(wafer_rows["target"].max()) if "target" in wafer_rows else None

    print(f"\n[{idx}/{total_wafers}] Wafer {int(wafer_id)} (Target: {target if target is not None else 'N/A'})")

    for step in STEPS:
        step_rows = wafer_rows[wafer_rows["StepID"] == step]
        if step_rows.empty:
            print(f"Step {step}: No data")
            continue

        cmd = [
            sys.executable, MODEL_PREDICTOR,
            str(step), str(int(wafer_id)),
            "--csv", CSV_PATH,
            "--model-dir", MODEL_DIR,
            "--agg", args.agg,
            "--threshold", str(args.threshold)
        ]

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=30
            )
            output_lines = result.stdout.strip().splitlines()

            if len(output_lines) >= 3:
                label = output_lines[0]
                flag = int(output_lines[1])
                prob = float(output_lines[2])
                print(f"Step {step}: {label} ({flag}) — p={prob:.2f}")
                if result.stderr:
                    for ln in result.stderr.strip().splitlines():
                        print(f"  {ln}")
                results.append({
                    "wafer_id": wafer_id,
                    "step": step,
                    "target": target,
                    "pred_label": label,
                    "pred_flag": flag,
                    "probability": prob
                })
            else:
                print(f"Step {step}: Unexpected output: {result.stdout.strip()}")
        except Exception as e:
            print(f"Step {step}: Error ({e})")

    elapsed = time.time() - wafer_start
    print(f"-> Completed wafer {int(wafer_id)} in {elapsed:.2f}s")

# Save results
results_df = pd.DataFrame(results)
results_df.to_csv("stepwise_predictions.csv", index=False)
print("\nResults saved to stepwise_predictions.csv")

# Accuracy if available
if not results_df.empty and 'target' in results_df:
    total = len(results_df)
    correct = (results_df['target'] == results_df['pred_flag']).sum()
    accuracy = correct / total if total>0 else 0
    print(f"\nAccuracy: {accuracy:.2%} ({correct}/{total})")
    
    mismatches = results_df[results_df['target'] != results_df['pred_flag']]
    if not mismatches.empty:
        print("First 10 mismatches:")
        print(mismatches.head(10).to_string(index=False))
