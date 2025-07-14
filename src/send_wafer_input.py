import subprocess
import random

PREDICTOR_PATH = "/workspace/playground-lingua-franca/src/model_predictor.py"
PYTHON_EXEC = "/workspace/playground-lingua-franca/.venv/bin/python"

def generate_features(normal=True):
    if normal:
        return [round(random.uniform(0.05, 1.0), 2) for _ in range(20)]
    else:
        return [round(random.uniform(2.0, 5.0), 2) for _ in range(20)]

def run_prediction(phase, features):
    cmd = [PYTHON_EXEC, PREDICTOR_PATH, str(phase)] + list(map(str, features))
    result = subprocess.run(cmd, capture_output=True, text=True)
    output_lines = result.stdout.strip().splitlines()
    score = float(output_lines[0])
    nature = output_lines[1]
    return score, nature

def main():
    num_wafers = 10
    for i in range(1, num_wafers + 1):
        features = generate_features(random.choice([True, False]))
        score1, nature1 = run_prediction(1, features)
        score2, nature2 = run_prediction(2, features)

        final_status = "Abnormal" if "Abnormal" in (nature1, nature2) else "Normal"

        print(f"\nWafer #{i}:")
        print(f"  Phase 1 Score (Pre): {score1:.2f} → {nature1}")
        print(f"  Phase 2 Score (Post): {score2:.2f} → {nature2}")
        print(f"  Final Status: {final_status}")

if __name__ == "__main__":
    main()
