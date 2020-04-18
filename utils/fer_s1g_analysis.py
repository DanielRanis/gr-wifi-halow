import numpy as np
import matplotlib.pyplot as plt

offset = True;
fer = True;

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

snr0_no_cfo_values = np.arange(0.0,19.0, 1)
snr1_no_cfo_values = np.arange(0.0,19.0, 1)
snr2_no_cfo_values = np.arange(0.0,19.0, 1)


snr0= np.array(snr0_values)
snr1= np.array(snr1_values)
snr2= np.array(snr2_values)
snr3= np.array(snr3_values)
snr4= np.array(snr4_values)
snr5= np.array(snr5_values)
snr6= np.array(snr6_values)
snr7= np.array(snr7_values)
snr8= np.array(snr8_values)


fer_mcs_0 = np.array([1.0,1.0,0.813,0.289,0.03586,0.00255])
fer_mcs_1 = np.array([1.0,1.0,1.0,1.0,1.0,0.96618,0.6557,0.2506,0.07049,0.00985])
fer_mcs_2 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.97078,0.6802,0.2721,0.0560,0.0064])
fer_mcs_3 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9216,0.5361,0.1564,0.0414,0.00779])
fer_mcs_4 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8547,0.4484,0.1383,0.03029,0.00536])
fer_mcs_5 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.97561,0.6993,0.2906,0.0864,0.01898,0.00356])
fer_mcs_6 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.7604,0.3552,0.1051,0.0241,0.004299])
fer_mcs_7 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.87719,0.4854,0.1932,0.0530,0.0117,0.00244])
fer_mcs_8 = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9345,0.5730,0.2557,0.0709,0.01845,0.00366])

# fer_mcs0_cfo_no_sfo_comp = np.array([1.0,1.0,0.8064,0.3154,0.0477,0.00529])
# fer_mcs1_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,0.9523,0.625,0.2398,0.0661,0.0119])
# fer_mcs2_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9569,0.6711,0.2624,0.04738,0.00619])
# fer_mcs3_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9216,0.4819,0.1876,0.0456,0.0076])
# fer_mcs4_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8849,0.4629,0.1429,0.0304,0.0059])
# fer_mcs5_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9803,0.6734,0.3007,0.0829,0.0196,0.00329])
# fer_mcs6_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9756,0.7722,0.4048,0.1251,0.0239,0.00529])
# fer_mcs7_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.87719,0.4854,0.1932,0.0530,0.0117,0.00244])
# fer_mcs8_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.909,0.6097,0.2770,0.0741,0.0165,0.0039])

# fer_mcs0_no_cfo_no_sfo_comp = np.array([1.0,0.986,0.8064,0.2896,0.0434,0.0044])
# fer_mcs1_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,0.9803,0.6968,0.2642,0.0626,0.0099])
# fer_mcs2_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9569,0.6711,0.2624,0.04738,0.00619])
# fer_mcs3_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9216,0.4819,0.1876,0.0456,0.0076])
# fer_mcs4_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8849,0.4629,0.1429,0.0304,0.0059])
# fer_mcs5_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9803,0.6734,0.3007,0.0829,0.0196,0.00329])
# fer_mcs6_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9756,0.7722,0.4048,0.1251,0.0239,0.00529])
# fer_mcs7_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.87719,0.4854,0.1932,0.0530,0.0117,0.00244])
# fer_mcs8_no_cfo_no_sfo_comp = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.909,0.6097,0.2770,0.0741,0.0165,0.0039])


fer_mcs0_sfo = np.array([1.0,1.0,0.930,0.5494,0.1675,0.0324])
fer_mcs1_sfo = np.array([1.0,1.0,1.0,1.0,1.0,0.9852,0.8097,0.42255,0.17652,0.05263])
fer_mcs2_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9852,0.833,0.4246,0.11806,0.02505])
fer_mcs3_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9302,0.6430,0.3210,0.1035,0.03105])
fer_mcs4_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9090,0.6211,0.27285,0.1079,0.02654])
fer_mcs5_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8968,0.5555,0.2728,0.1295,0.0754])
fer_mcs6_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.9049,0.5555,0.3125,0.1640,0.0888])
fer_mcs7_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9389,0.7633,0.5012,0.2954,0.1673,0.1062])
fer_mcs8_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9174,0.7082,0.5194,0.3952,0.3125])
fer_mcs8t_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.623,0.2781,0.0744,0.0166,0.0])

fer_mcs0_cfo = np.array([1.0,1.0,0.8196,0.3623,0.0655,0.0067])
fer_mcs1_cfo = np.array([1.0,1.0,1.0,1.0,1.0,0.9756,0.6849,0.2785,0.07451,0.01615])
fer_mcs2_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.980,0.70922,0.2809,0.05664,0.00854])
fer_mcs3_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8928,0.5509,0.1986,0.0490,0.00856])
fer_mcs4_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9009,0.51679,0.1712,0.0377,0.00692])
fer_mcs5_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.7575,0.3384,0.10934,0.02530,0.00564])
fer_mcs6_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.995,0.81967,0.4866,0.14749,0.0384,0.0081])
fer_mcs7_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9569,0.6269,0.2614,0.0882,0.02271,0.00512])
fer_mcs8_cfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.990,0.7407,0.4175,0.1790,0.05617,0.018])

fer_mcs0_cfo_sfo = np.array([1.0,1.0,0.8968,0.4264,0.1124,0.01926])
fer_mcs1_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,0.990,0.8,0.3913,0.1515,0.0421])
fer_mcs2_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8264,0.3861,0.1061,0.0225])
fer_mcs3_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.9216,0.5665,0.25873,0.09429,0.02910])
fer_mcs4_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8888,0.5586,0.2541,0.0885,0.0242])
fer_mcs5_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8097,0.4750,0.2525,0.1136,0.05709])
fer_mcs6_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.995,0.8695,0.5830,0.2894,0.1490,0.0762])
fer_mcs7_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8888,0.6993,0.3937,0.2293,0.1333,0.09385])
fer_mcs8_cfo_sfo = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.8695,0.5917,0.4514,0.3305,0.27855])






# no CFO and no SFO
if fer:
    fig1, ax1 = plt.subplots(1, 1)
    ax1.set(title='Frame Error Rate (FER), Total Frame Size: 274 Byte, No Frequency Offset')
    ax1.semilogy(snr0, fer_mcs_0,'-ro')
    ax1.semilogy(snr1, fer_mcs_1,'-gs')
    ax1.semilogy(snr2, fer_mcs_2,'-bs')
    ax1.semilogy(snr3, fer_mcs_3,'-kv')
    ax1.semilogy(snr4, fer_mcs_4,'-mv')
    ax1.semilogy(snr5, fer_mcs_5,'-rd')
    ax1.semilogy(snr6, fer_mcs_6,'-gd')
    ax1.semilogy(snr7, fer_mcs_7,'-bd')
    ax1.semilogy(snr8, fer_mcs_8,'-kX')
    ax1.legend(['MCS 0: BPSK 1/2', 
                'MCS 1: QPSK 1/2', 
                'MCS 2: QPSK 3/4',
                'MCS 3: 16-QAM 1/23',
                'MCS 4: 16-QAM 3/44',
                'MCS 5: 64-QAM 2/35',
                'MCS 6: 64-QAM 3/46',
                'MCS 7: 64-QAM 5/67',
                'MCS 8: 256-QAM 3/4'])
    ax1.set_ylabel('FER')
    ax1.set_xlabel('Signal to Noise Ratio (SNR) in dB')
    plt.grid(True, which="both")
    plt.xlim([0,40])
    fig1.tight_layout()
    plt.show()

if offset:
    fig2, ax2 = plt.subplots(1, 1)
    ax2.set(title='Frame Error Rate (FER), Total Frame Size: 274 Byte, Frequency Offset')
    # CFO and SFO
    ax2.semilogy(snr0, fer_mcs0_cfo_sfo,'-ro')
    ax2.semilogy(snr1, fer_mcs1_cfo_sfo,'-rs',label='_nolegend_')
    ax2.semilogy(snr2, fer_mcs2_cfo_sfo,'-rs',label='_nolegend_')
    ax2.semilogy(snr3, fer_mcs3_cfo_sfo,'-rv',label='_nolegend_')
    ax2.semilogy(snr4, fer_mcs4_cfo_sfo,'-rv',label='_nolegend_')
    ax2.semilogy(snr5, fer_mcs5_cfo_sfo,'-rd',label='_nolegend_')
    ax2.semilogy(snr6, fer_mcs6_cfo_sfo,'-rd',label='_nolegend_')
    ax2.semilogy(snr7, fer_mcs7_cfo_sfo,'-rd',label='_nolegend_')
    ax2.semilogy(snr8, fer_mcs8_cfo_sfo,'-rX',label='_nolegend_')
    # SFO and no CFO 
    ax2.semilogy(snr0, fer_mcs0_sfo,'-bo')
    ax2.semilogy(snr1, fer_mcs1_sfo,'-bs',label='_nolegend_')
    ax2.semilogy(snr2, fer_mcs2_sfo,'-bs',label='_nolegend_')
    ax2.semilogy(snr3, fer_mcs3_sfo,'-bv',label='_nolegend_')
    ax2.semilogy(snr4, fer_mcs4_sfo,'-bv',label='_nolegend_')
    ax2.semilogy(snr5, fer_mcs5_sfo,'-bd',label='_nolegend_')
    ax2.semilogy(snr6, fer_mcs6_sfo,'-bd',label='_nolegend_')
    ax2.semilogy(snr7, fer_mcs7_sfo,'-bd',label='_nolegend_')
    ax2.semilogy(snr8, fer_mcs8_sfo,'-bX',label='_nolegend_')
    # CFO and no SFO 
    ax2.semilogy(snr0, fer_mcs0_cfo,'-go')
    ax2.semilogy(snr1, fer_mcs1_cfo,'-gs',label='_nolegend_')
    ax2.semilogy(snr2, fer_mcs2_cfo,'-gs',label='_nolegend_')
    ax2.semilogy(snr3, fer_mcs3_cfo,'-gv',label='_nolegend_')
    ax2.semilogy(snr4, fer_mcs4_cfo,'-gv',label='_nolegend_')
    ax2.semilogy(snr5, fer_mcs5_cfo,'-gd',label='_nolegend_')
    ax2.semilogy(snr6, fer_mcs6_cfo,'-gd',label='_nolegend_')
    ax2.semilogy(snr7, fer_mcs7_cfo,'-gd',label='_nolegend_')
    ax2.semilogy(snr8, fer_mcs8_cfo,'-gX',label='_nolegend_')
    ax2.legend(['MCS[0:8], CFO: +20 ppm, SFO: +20 ppm',
                'MCS[0:8], CFO: 0 ppm, SFO: +20 ppm',
                'MCS[0:8], CFO: +20 ppm, SFO: 0 ppm'])
    ax2.set_ylabel('FER')
    ax2.set_xlabel('Signal to Noise Ratio (SNR) in dB')
    plt.grid(True, which="both")
    plt.xlim([0,40])
    fig2.tight_layout()
    plt.show()