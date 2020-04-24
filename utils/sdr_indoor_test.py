import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt

# fer_perc_mcs0 = 100.0#-(0.0000456*100.0)
# fer_perc_mcs1 = 100.0
# fer_perc_mcs2 = 100.0-(0.000455*100.0)
# fer_perc_mcs3 = 100-(0.00366*100.0)
# fer_perc_mcs4 = 100-(0.341*100.0)
# fer_perc_mcs5 = 100-(0.494*100.0)
# fer_perc_mcs6 = 100-(0.728*100.0)
# fer_perc_mcs7 = 100-(0.924*100.0)
# fer_perc_mcs8 = 100-(0.968*100.0)

fer_perc_mcs0 = 100.0#-(0.0000456*100.0)
fer_perc_mcs1 = 100.0-(0.000137*100.0)
fer_perc_mcs2 = 100.0-(0.000135*100.0)
fer_perc_mcs3 = 100-(0.000673*100.0)
fer_perc_mcs4 = 100
fer_perc_mcs5 = 100-(0.00147*100.0)
fer_perc_mcs6 = 100-(0.00430*100.0)
fer_perc_mcs7 = 100-(0.0358*100.0)
fer_perc_mcs8 = 100-(0.143*100.0)

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
ax.text(50.0, 0.12,'7183 / 7183', color='white', fontweight='bold')
ax.text(fer_perc_mcs0+0.5, 0.25, 'AVG SNR: 28 dB', color='black')

ax.text(fer_perc_mcs1+0.5, 1.0, str(fer_perc_mcs1)+' %', color='black', fontweight='bold')
ax.text(50.0, 1.12,'7323 / 7324', color='white', fontweight='bold')
ax.text(fer_perc_mcs1+0.5, 1.25, 'AVG SNR: 28.36 dB', color='black')

ax.text(fer_perc_mcs2+0.5, 2.0, str(fer_perc_mcs2)+' %', color='black', fontweight='bold')
ax.text(50.0, 2.12,'7389 / 7390', color='white', fontweight='bold')
ax.text(fer_perc_mcs2+0.5, 2.25, 'AVG SNR: 28.75 dB', color='black')

ax.text(fer_perc_mcs3+0.5, 3.0, str(fer_perc_mcs3)+' %', color='black', fontweight='bold')
ax.text(50.0, 3.12,'7425 / 7430', color='white', fontweight='bold')
ax.text(fer_perc_mcs3+0.5, 3.25, 'AVG SNR: 33.61 dB', color='black')

ax.text(fer_perc_mcs4+0.5, 4.0, str(fer_perc_mcs4)+' %', color='black', fontweight='bold')
ax.text(50.0, 4.12,'7453 / 7453', color='white', fontweight='bold')
ax.text(fer_perc_mcs4+0.5, 4.25, 'AVG SNR: 30.44 dB', color='black')

ax.text(fer_perc_mcs5+0.5, 5.0, str(fer_perc_mcs5)+' %', color='black', fontweight='bold')
ax.text(50.0, 5.12,'7469 / 7480', color='white', fontweight='bold')
ax.text(fer_perc_mcs5+0.5, 5.25, 'AVG SNR: 30.33 dB', color='black')

ax.text(fer_perc_mcs6+0.5, 6.0, str(fer_perc_mcs6)+' %', color='black', fontweight='bold')
ax.text(50.0, 6.12,'7417 / 7449', color='white', fontweight='bold')
ax.text(fer_perc_mcs6+0.5, 6.25, 'AVG SNR: 30.16 dB', color='black')

ax.text(fer_perc_mcs7+0.5, 7.0, str(fer_perc_mcs7)+' %', color='black', fontweight='bold')
ax.text(50.0, 7.12,'7187 / 7454', color='white', fontweight='bold')
ax.text(fer_perc_mcs7+0.5, 7.25, 'AVG SNR: 30 dB', color='black')

ax.text(fer_perc_mcs8+0.5, 8.0, str(fer_perc_mcs8)+' %', color='black', fontweight='bold')
ax.text(50.0, 8.12,'6400 / 7466', color='white', fontweight='bold')
ax.text(fer_perc_mcs8+0.5, 8.25, 'AVG SNR: 33.75 dB', color='black')

ax.set_xlabel('Successfully delivered frames [%]')
ax.set_title('Frame Delivery Ratio',fontweight='bold')
plt.xlim([0,115])
ax.xaxis.grid(linestyle='-.')
plt.show()