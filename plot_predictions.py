import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_path = '/workspace/playground-lingua-franca/cleaned_predictions_log.csv'

try:
    df = pd.read_csv(csv_path)

    df.columns = [col.strip() for col in df.columns]  # Clean column names

    df = df[df['Material'].astype(str).isin(['1', '2'])]  # Filter valid material entries
    df['Material'] = df['Material'].astype(int)

    plt.figure(figsize=(12, 5))

    # Power plot
    plt.subplot(1, 2, 1)
    sns.boxplot(data=df, x='Material', y='Power')
    plt.title("Power Consumption by Material")
    plt.xlabel("Material Type")
    plt.ylabel("Power (W)")

    # Time plot
    plt.subplot(1, 2, 2)
    sns.boxplot(data=df, x='Material', y='Time')
    plt.title("Process Time by Material")
    plt.xlabel("Material Type")
    plt.ylabel("Time (sec)")

    plt.tight_layout()
    plt.savefig("material_prediction_summary.png")
    print("Plot saved as 'material_prediction_summary.png'")

except Exception as e:
    print("Error during plot generation:", e)
