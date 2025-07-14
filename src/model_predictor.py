#!/usr/bin/env python3
import sys
import argparse
import joblib
import numpy as np
import time
import os
import pandas as pd
import warnings

warnings.filterwarnings("ignore", category=UserWarning)

# Valid D1 StepIDs (pre, core, post)
VALID_STEPS = {-1, 1, 2, 4, 6, 7, -2}

def load_model(step, model_dir):
    """
    Load a pre-trained model for the given step from the specified directory.
    """
    model_filename = f"model_step_{step}_D1.pkl"
    model_path = os.path.join(model_dir, model_filename)
    if not os.path.exists(model_path):
        print(f"[ERROR] Model file '{model_filename}' not found in '{model_dir}'", file=sys.stderr)
        sys.exit(1)
    return joblib.load(model_path)

def main():
    parser = argparse.ArgumentParser(
        description="Wafer D1 phase predictor. Valid StepIDs: -1, 1, 2, 4, 6, 7, -2"
    )
    parser.add_argument("step", type=int, help="Production StepID")
    parser.add_argument("wafer_id", type=int, help="Wafer ID (MaterialID in CSV)")
    parser.add_argument("--csv", required=True, help="Path to CSV with time-series features")
    parser.add_argument("--model-dir", default="models", help="Directory of serialized RF models")
    parser.add_argument("--agg", choices=["mean","median","max"], default="mean",
                        help="Aggregate per-sample probabilities into a single score")
    parser.add_argument("--threshold", type=float, default=0.5,
                        help="Probability threshold for abnormal classification")
    args = parser.parse_args()

    if args.step not in VALID_STEPS:
        print(f"[ERROR] Invalid StepID {args.step}. Must be one of {sorted(VALID_STEPS)}", file=sys.stderr)
        sys.exit(1)

    start_ts = time.strftime('%Y-%m-%d %H:%M:%S')
    print(f"[INFO {start_ts}] Starting prediction: Step={args.step}, Wafer={args.wafer_id}", file=sys.stderr)

    try:
        # Load and verify data
        df = pd.read_csv(args.csv)
        req_cols = {'MaterialID','StepID','duration_ms'} | {f"feature_{i}" for i in range(1,16)}
        missing = req_cols - set(df.columns)
        if missing:
            print(f"[ERROR] Missing columns: {', '.join(sorted(missing))}", file=sys.stderr)
            sys.exit(1)

        # Subset to specific wafer and step
        subset = df[(df.MaterialID == args.wafer_id) & (df.StepID == args.step)]
        if subset.empty:
            raise ValueError(f"No data for wafer {args.wafer_id} at step {args.step}")

        # Check duration normalization
        mn, mx = subset.duration_ms.min(), subset.duration_ms.max()
        if mn < 0 or mx > 1:
            warnings.warn(f"duration_ms out of [0,1]: ({mn:.3f},{mx:.3f})", UserWarning)

        # Features array
        feat_cols = ['duration_ms'] + [f"feature_{i}" for i in range(1,16)]
        X = subset[feat_cols].values

        # Predict
        model = load_model(args.step, args.model_dir)
        probs = model.predict_proba(X)[:,1]

        # Aggregate
        if args.agg == 'mean':
            score = float(np.mean(probs))
        elif args.agg == 'median':
            score = float(np.median(probs))
        else:
            score = float(np.max(probs))

        # Decision
        flag = int(score >= args.threshold)
        label = 'Abnormal' if flag else 'Normal'

        # Outputs
        print(label, flush=True)
        print(flag, flush=True)
        print(f"{score:.4f}", flush=True)

        end_ts = time.strftime('%Y-%m-%d %H:%M:%S')
        print(f"[INFO {end_ts}] Done: {label} (flag={flag}), score={score:.4f}", file=sys.stderr)

    except Exception as e:
        print(f"[ERROR] Prediction failed: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()
