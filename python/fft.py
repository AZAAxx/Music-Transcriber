import matplotlib.pyplot as plt

with open("python/FFT-result.txt", "r") as f:
    data = list(map(float, f.read().split(", ")))

x = range(len(data))

plt.plot(x, data)
plt.xlabel("w")
plt.ylabel("|X|")
plt.title("Frequency Domain Chart")
plt.grid()

plt.show()

plt.savefig("python/fft_plot.png")
print("Plot saved as fft_plot.png")