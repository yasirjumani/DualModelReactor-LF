#!/usr/bin/env python3
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import make_classification
import joblib
import os

os.makedirs("models", exist_ok=True)

for step in [2, 4, 6, 7]:
    X, y = make_classification(
        n_samples=100, n_features=17, n_informative=10, n_redundant=2, random_state=step
    )
    clf = RandomForestClassifier(n_estimators=10, random_state=step)
    clf.fit(X, y)
    model_path = f"models/random_forest_step_{step}.joblib"
    joblib.dump(clf, model_path)
    print(f"Saved dummy model: {model_path}")
