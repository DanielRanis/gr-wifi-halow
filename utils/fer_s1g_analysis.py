import numpy as np
import matplotlib.pyplot as plt

# Data for plotting
snr0_values = np.arange(0.0,6.0, 1)
snr1_values = np.arange(0.0,10.0, 1)
snr2_values = np.arange(0.0,12.0, 1)
snr3_values = np.arange(0.0,16.0, 1)
snr4_values = np.arange(0.0,19.0, 1)
snr5_values = np.arange(0.0,24.0, 1)
snr6_values = np.arange(0.0,25.0, 1)
snr7_values = np.arange(0.0,27.0, 1)
snr8_values = np.arange(0.0,31.0, 1)

snr0= np.array(snr0_values)
snr1= np.array(snr1_values)
snr2= np.array(snr2_values)
snr3= np.array(snr3_values)
snr4= np.array(snr4_values)
snr5= np.array(snr5_values)
snr6= np.array(snr6_values)
snr7= np.array(snr7_values)
snr8= np.array(snr8_values)


#snr = np.array([0.0, 1.0, 3.0])
fer_mcs_0 = np.array([1.0,1.0,0.813,0.289,0.035,0.0025])
fer_mcs_1 = np.array([1.0,1.0,1.0,1.0,1.0,0.966,0.656,0.251,0.070,0.01])
fer_mcs_2 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.971,0.680,0.272,0.056,0.006])
fer_mcs_3 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.922,0.536,0.156,0.041,0.008])
fer_mcs_4 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.855,0.449,0.138,0.030,0.005])
fer_mcs_5 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.976,0.699,0.291,0.087,0.02,0.0035])
fer_mcs_6 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.760,0.354,0.105,0.024,0.004])
fer_mcs_7 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.877,0.485,0.193,0.053,0.012,0.002])
fer_mcs_8 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.935,0.573,0.256,0.071,0.018,0.004])

# Create figure
fig, ax1 = plt.subplots(1, 1)

# log y axis
ax1.semilogy(snr0, fer_mcs_0,'--ro')
ax1.semilogy(snr1, fer_mcs_1,'--gs')
ax1.semilogy(snr2, fer_mcs_2,'--bs')
ax1.semilogy(snr3, fer_mcs_3,'--cv')
ax1.semilogy(snr4, fer_mcs_4,'--mv')
ax1.semilogy(snr5, fer_mcs_5,'--rd')
ax1.semilogy(snr6, fer_mcs_6,'--gd')
ax1.semilogy(snr7, fer_mcs_7,'--bd')
ax1.semilogy(snr8, fer_mcs_8,'--cX')

ax1.legend(['S1G BPSK 1/2 (MCS 0)', 
            'S1G QPSK 1/2 (MCS 1)', 
            'S1G QPSK 3/4 (MCS 2)',
            'S1G 16-QAM 1/2 (MCS 3)',
            'S1G 16-QAM 3/4 (MCS 4)',
            'S1G 64-QAM 2/3 (MCS 5)',
            'S1G 64-QAM 3/4 (MCS 6)',
            'S1G 64-QAM 5/6 (MCS 7)',
            'S1G 256-QAM 3/4 (MCS 8)'])

ax1.set(title='Frame Error Rate (FER) for S1G_SHORT')
ax1.set_ylabel('FER')
ax1.set_xlabel('Signal to Noise Ratio (SNR) in dB')
plt.grid(True, which="both")
plt.xlim([0,35])
#plt.ylim([0.01,1.2])

# log x axis
# ax2.semilogx(t, np.sin(2 * np.pi * t))
# ax2.set(title='semilogx')
# ax2.grid()

# log x and y axis
# ax3.loglog(t, 20 * np.exp(-t / 10.0), basex=2)
# ax3.set(title='loglog base 2 on x')
# ax3.grid()

# With errorbars: clip non-positive values
# Use new data for plotting
# x = 10.0**np.linspace(0.0, 2.0, 20)
# y = x**2.0

# ax4.set_xscale("log", nonposx='clip')
# ax4.set_yscale("log", nonposy='clip')
# ax4.set(title='Errorbars go negative')
# ax4.errorbar(x, y, xerr=0.1 * x, yerr=5.0 + 0.75 * y)
# ylim must be set after errorbar to allow errorbar to autoscale limits
# ax4.set_ylim(bottom=0.1)

fig.tight_layout()
plt.show()