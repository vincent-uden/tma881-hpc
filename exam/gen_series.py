import subprocess

if __name__ == "__main__":
    runs = 20

    N = [1000, 10000, 100000, 1000000, 10000000]

    for n in N:
        output = subprocess.run(["hyperfine", "--warmup", "5", "--runs", n, "./build/naive"], capture_output=True)
