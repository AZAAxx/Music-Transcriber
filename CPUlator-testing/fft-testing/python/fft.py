import numpy as np
import matplotlib.pyplot as plt

res = np.loadtxt("FFT-result.txt", delimiter=",")
N_fft = len(res)
f_s = 8000   # example: 8 kHz sampling rate

res_half = res[:N_fft//2]
freq = np.arange(N_fft//2) * f_s / N_fft

plt.plot(freq, res_half)
plt.title("Frequency Domain Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("|X(f)|")
plt.grid(True)


plt.savefig("python/fft_plot.png")
print("Plot saved as fft_plot.png")