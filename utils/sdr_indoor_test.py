import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt

fer_perc_mcs0 = 100.0
fer_perc_mcs1 = 100.0
fer_perc_mcs2 = 100.0-(0.000341*100.0)
fer_perc_mcs3 = 100-(0.00168*100.0)
fer_perc_mcs4 = 100-(0.281*100.0)
fer_perc_mcs5 = 100-(0.364*100.0)
fer_perc_mcs6 = 100-(0.638*100.0)
fer_perc_mcs7 = 100-(0.923*100.0)
fer_perc_mcs8 = 100-(0.978*100.0)

# original default Parameter werden wiederhergestellt:
plt.rcdefaults() 
fig, ax = plt.subplots()
mcs =      ('MCS0',
            'MCS1',
            'MCS2',
            'MCS3',
            'MCS4',
            'MCS5',
            'MCS6',
            'MCS7',
            'MCS8')
y_pos = np.arange(len(mcs))
fer = (fer_perc_mcs0,
       fer_perc_mcs1,
       fer_perc_mcs2,
       fer_perc_mcs3,
       fer_perc_mcs4,
       fer_perc_mcs5,
       fer_perc_mcs6,
       fer_perc_mcs7,
       fer_perc_mcs8)
ax.barh(y_pos, fer, align='center',color='green', ecolor='black')
ax.set_yticks(y_pos)
ax.set_yticklabels(mcs,fontweight='bold')
ax.invert_yaxis()  # labels von oben nach unten
ax.text(fer_perc_mcs0+0.5, 0.0, str(fer_perc_mcs0)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs0+0.5, 0.25, 'AVG SNR: 30.22 dB', color='black')

ax.text(fer_perc_mcs1+0.5, 1.0, str(fer_perc_mcs1)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs1+0.5, 1.25, 'AVG SNR: 30.25 dB', color='black')

ax.text(fer_perc_mcs2+0.5, 2.0, str(fer_perc_mcs2)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs2+0.5, 2.25, 'AVG SNR: 35.09 dB', color='black')

ax.text(fer_perc_mcs3+0.5, 3.0, str(fer_perc_mcs3)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs3+0.5, 3.25, 'AVG SNR: 31.16 dB', color='black')

ax.text(fer_perc_mcs4+0.5, 4.0, str(fer_perc_mcs4)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs4+0.5, 4.25, 'AVG SNR: 31.65 dB', color='black')

ax.text(fer_perc_mcs5+0.5, 5.0, str(fer_perc_mcs5)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs5+0.5, 5.25, 'AVG SNR: 31.09 dB', color='black')

ax.text(fer_perc_mcs6+0.5, 6.0, str(fer_perc_mcs6)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs6+0.5, 6.25, 'AVG SNR: 30.45 dB', color='black')

ax.text(fer_perc_mcs7+0.5, 7.0, str(fer_perc_mcs7)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs7+0.5, 7.25, 'AVG SNR: 31.14 dB', color='black')

ax.text(fer_perc_mcs8+0.5, 8.0, str(fer_perc_mcs8)+' %', color='black', fontweight='bold')
ax.text(fer_perc_mcs8+0.5, 8.25, 'AVG SNR: 30.39 dB', color='black')

ax.set_xlabel('Frame Delivery Rate [%]')
ax.set_title('SDR Frame Delivery Rate',fontweight='bold')
plt.xlim([0,115])
ax.xaxis.grid(linestyle='-.')
plt.show()