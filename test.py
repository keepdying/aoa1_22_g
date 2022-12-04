import os
import time

import matplotlib
import matplotlib.pyplot as plt


def measure_time(input, n):
    total_time = 0
    times = []
    for i in range(n):
        start = time.time()
        os.system(f"./homework2 {input} > /dev/null")
        end = time.time()
        times.append(end - start)
    return times


if __name__ == "__main__":
    results = {}
    fig, axs = plt.subplots(2, 4)
    funcs = ["firstq", "max", "mean", "median", "min", "std", "thirdq"]

    for func in funcs:
        results[func] = {}
        nums = ["10", "100", "1000", "10000", "100000"]
        for num in nums:
            file = f"input_{func}_{num}.txt"
            print(f"Running time for file {file}: ", end="")
            dt = measure_time(f"./inputs/{file}", 10)
            results[func][(int(num))] = dt
            print(f"{sum(dt)}")

    for n in range(len(funcs)):
        func = funcs[n]
        x = list(results[func].keys())
        y = [sum(val)/len(val) for val in results[func].values()]
        i = n % 2
        j = n // 2
        axs[i, j].boxplot(results[func].values())
        axs[i, j].set_title(func)
        n += 1

    plt.show()
    fig, axs = plt.subplots(2, 4)

    for n in range(len(funcs)):
        func = funcs[n]
        x = list(results[func].keys())
        y = [sum(val)/len(val) for val in results[func].values()]
        i = n % 2
        j = n // 2
        axs[i, j].plot(x, y)
        axs[i, j].set_title(func)
        n += 1

    plt.show()
