from argparse import ArgumentParser
import numpy as np


if __name__ == "__main__":
    parser = ArgumentParser(
        "Average all the velocities reported by compare_flat_rates program"
    )
    parser.add_argument(
        "-f",
        "--file",
        type=str,
        required=True,
        help="output from compare_flat_rates program",
    )

    args = parser.parse_args()

    with open(args.file, "r") as f:
        lines = f.readlines()

    lines = list(map(lambda x: int(x.strip()), lines))
    print(f"Average velocity of moving cars: {np.mean(lines):.2f}")
