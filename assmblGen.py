import pandas as pd
import sys

def main():
    print(sys.argv[1])
    print(sys.argv[2])
    df = pd.read_csv("test.smbtbl", delimiter='\t')
    print(df["MLo"])

if __name__ == "__main__":
    main()