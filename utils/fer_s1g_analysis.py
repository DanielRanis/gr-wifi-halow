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
fer_mcs_0 = np.array([1.0,1.0,0.8064,0.306,0.0349,0.00255])
fer_mcs_1 = np.array([1.0,1.0,1.0,1.0,1.0,0.966,0.660,0.255,0.0689,0.0099])
fer_mcs_2 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9615,0.692,0.267,0.0548,0.006])
fer_mcs_3 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9216,0.5319,0.151,0.041,0.0075])
fer_mcs_4 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.862,0.4514,0.1367,0.030,0.0053])
fer_mcs_5 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.985,0.692,0.2849,0.0874,0.0187,0.00346])
fer_mcs_6 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.7575,0.3448,0.1058,0.023,0.00429])
fer_mcs_7 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.8547,0.475,0.1874,0.0515,0.011,0.0022])
fer_mcs_8 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9167,0.5602,0.2567,0.0693,0.0166,0.0034])

fer_mcs0_cfo = np.array([1.0,1.0,0.8547,0.378,0.0737,0.008])
fer_mcs1_cfo = np.array([1.0,1.0,1.0,1.0,1.0,0.98039,0.7017,0.3257,0.0987,0.01739])
fer_mcs2_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.75188,0.30165,0.07532,0.01155])
fer_mcs3_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9615,0.61349,0.20682,0.05506,0.01133])
fer_mcs4_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9259,0.542,0.20141,0.04927,0.00786])
fer_mcs5_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.85106,0.44943,0.16103,0.03810,0.00984])
fer_mcs6_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.995,0.88495,0.5154,0.1974,0.0665,0.0196])
fer_mcs7_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.995,0.9756,0.692,0.3597,0.14749,0.04292,0.01238])
fer_mcs8_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.94339,0.70422,0.41322,0.19627,0.08822])


# Create figure
fig, ax1 = plt.subplots(1, 1)

# log y axis
ax1.semilogy(snr0, fer_mcs_0,'-ro')
ax1.semilogy(snr1, fer_mcs_1,'-gs')
ax1.semilogy(snr2, fer_mcs_2,'-bs')
ax1.semilogy(snr3, fer_mcs_3,'-cv')
ax1.semilogy(snr4, fer_mcs_4,'-mv')
ax1.semilogy(snr5, fer_mcs_5,'-rd')
ax1.semilogy(snr6, fer_mcs_6,'-gd')
ax1.semilogy(snr7, fer_mcs_7,'-bd')
ax1.semilogy(snr8, fer_mcs_8,'-cX')

# cfo values
ax1.semilogy(snr0, fer_mcs0_cfo,'--kx')
ax1.semilogy(snr1, fer_mcs1_cfo,'--kx')
ax1.semilogy(snr2, fer_mcs2_cfo,'--kx')
ax1.semilogy(snr3, fer_mcs3_cfo,'--kx')
ax1.semilogy(snr4, fer_mcs4_cfo,'--kx')
ax1.semilogy(snr5, fer_mcs5_cfo,'--kx')
ax1.semilogy(snr6, fer_mcs6_cfo,'--kx')
ax1.semilogy(snr7, fer_mcs7_cfo,'--kx')
ax1.semilogy(snr8, fer_mcs8_cfo,'--kx')

ax1.legend(['S1G BPSK 1/2 (MCS 0)', 
            'S1G QPSK 1/2 (MCS 1)', 
            'S1G QPSK 3/4 (MCS 2)',
            'S1G 16-QAM 1/2 (MCS 3)',
            'S1G 16-QAM 3/4 (MCS 4)',
            'S1G 64-QAM 2/3 (MCS 5)',
            'S1G 64-QAM 3/4 (MCS 6)',
            'S1G 64-QAM 5/6 (MCS 7)',
            'S1G 256-QAM 3/4 (MCS 8)',
            'CFO: 25kHz'])

ax1.set(title='Frame Error Rate (FER) for S1G_SHORT')
ax1.set_ylabel('FER')
ax1.set_xlabel('Signal to Noise Ratio (SNR) in dB')
plt.grid(True, which="both")
plt.xlim([0,40])
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