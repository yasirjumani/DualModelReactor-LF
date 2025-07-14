import pandas as pd

df = pd.read_csv("stepwise_predictions.csv")

print("\nPrediction summary:")
print(df["pred_flag"].value_counts())

print("\nSteps with most wrong predictions:")
wrong = df[df["pred_flag"] != df["target"]]
print(wrong["step"].value_counts())

print("\nFirst few mismatches:")
print(wrong.head())
