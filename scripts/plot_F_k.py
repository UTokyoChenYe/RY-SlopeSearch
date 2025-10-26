import pandas as pd
import matplotlib.pyplot as plt
import argparse
import os

def plot_fk(files, use_log_fk=False, save_path=None):
    plt.figure(figsize=(10, 6))

    for file in files:
        df = pd.read_csv(file)
        label = os.path.basename(file).replace(".csv", "")
        x = df["k"]
        y = df["log_Fk"] if use_log_fk else df["Fk"]
        y_label = "log(Fk)" if use_log_fk else "Fk"
        plt.plot(x, y, marker='o', label=label)

    plt.xlabel("k")
    plt.ylabel(y_label)
    plt.title("Fk curve")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()

    if save_path:
        plt.savefig(save_path)
        print(f"Save image to {save_path}")
    else:
        plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot Fk curve")
    parser.add_argument("csv_files", nargs='+', help="One or more CSV files")
    parser.add_argument("--log", action="store_true", help="Whether to use log(Fk)")
    parser.add_argument("--save", type=str, help="Save path (e.g.: output.png)")
    args = parser.parse_args()

    plot_fk(args.csv_files, use_log_fk=args.log, save_path=args.save)
