#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Wifi Loopback
# GNU Radio version: 3.7.13.5
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt4 import Qt
from PyQt4.QtCore import QObject, pyqtSlot
from gnuradio import blocks
from gnuradio import channels
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.filter import pfb
from gnuradio.qtgui import Range, RangeWidget
from optparse import OptionParser
from wifi_phy_hier import wifi_phy_hier  # grc-generated hier_block
import foo
import ieee802_11
import pmt
import sip
from gnuradio import qtgui


class wifi_loopback(gr.top_block, Qt.QWidget):

    def __init__(self, pilot_carriers=((-21, -7, 7, 21), ), pilot_symbols=((1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (1, 1, 1, -1), (1, 1, 1, -1), (1, 1, 1, -1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1), (-1, -1, -1, 1))):
        gr.top_block.__init__(self, "Wifi Loopback")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Wifi Loopback")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "wifi_loopback")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())


        ##################################################
        # Parameters
        ##################################################
        self.pilot_carriers = pilot_carriers
        self.pilot_symbols = pilot_symbols

        ##################################################
        # Variables
        ##################################################
        self.s1g_sig = s1g_sig = ieee802_11.s1g_signal_field().formatter()
        self.snr = snr = 50
        self.sig_field = sig_field = s1g_sig
        self.samp_rate = samp_rate = 2e6
        self.s1g_encoding = s1g_encoding = 0
        self.s1g_cw = s1g_cw = 2
        self.s1g_carriers = s1g_carriers = (range(-28, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 28+1),)
        self.s1g_cap = s1g_cap = True
        self.pdu_length = pdu_length = 483
        self.out_buf_size = out_buf_size = 96000
        self.interval = interval = 300
        self.freq = freq = 900e6
        self.epsilon = epsilon = 0
        self.encoding = encoding = 0
        self.def_sig = def_sig = ieee802_11.signal_field().formatter()
        self.def_carriers = def_carriers = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 26+1),)
        self.chan_est = chan_est = 0

        ##################################################
        # Blocks
        ##################################################
        self.tab1 = Qt.QTabWidget()
        self.tab1_widget_0 = Qt.QWidget()
        self.tab1_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab1_widget_0)
        self.tab1_grid_layout_0 = Qt.QGridLayout()
        self.tab1_layout_0.addLayout(self.tab1_grid_layout_0)
        self.tab1.addTab(self.tab1_widget_0, 'Overall Settings')
        self.tab1_widget_1 = Qt.QWidget()
        self.tab1_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab1_widget_1)
        self.tab1_grid_layout_1 = Qt.QGridLayout()
        self.tab1_layout_1.addLayout(self.tab1_grid_layout_1)
        self.tab1.addTab(self.tab1_widget_1, 'IEEE 802.11a/g/p Settings')
        self.tab1_widget_2 = Qt.QWidget()
        self.tab1_layout_2 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab1_widget_2)
        self.tab1_grid_layout_2 = Qt.QGridLayout()
        self.tab1_layout_2.addLayout(self.tab1_grid_layout_2)
        self.tab1.addTab(self.tab1_widget_2, 'IEEE 802.11ah  Settings (S1G_SHORT)')
        self.tab1_widget_3 = Qt.QWidget()
        self.tab1_layout_3 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab1_widget_3)
        self.tab1_grid_layout_3 = Qt.QGridLayout()
        self.tab1_layout_3.addLayout(self.tab1_grid_layout_3)
        self.tab1.addTab(self.tab1_widget_3, 'Channel Model Settings')
        self.top_grid_layout.addWidget(self.tab1)
        self.tab3 = Qt.QTabWidget()
        self.tab3_widget_0 = Qt.QWidget()
        self.tab3_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab3_widget_0)
        self.tab3_grid_layout_0 = Qt.QGridLayout()
        self.tab3_layout_0.addLayout(self.tab3_grid_layout_0)
        self.tab3.addTab(self.tab3_widget_0, 'Time Domain Diagram')
        self.tab3_widget_1 = Qt.QWidget()
        self.tab3_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab3_widget_1)
        self.tab3_grid_layout_1 = Qt.QGridLayout()
        self.tab3_layout_1.addLayout(self.tab3_grid_layout_1)
        self.tab3.addTab(self.tab3_widget_1, 'Constellation Diagram')
        self.top_grid_layout.addWidget(self.tab3)
        self.tab2 = Qt.QTabWidget()
        self.tab2_widget_0 = Qt.QWidget()
        self.tab2_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab2_widget_0)
        self.tab2_grid_layout_0 = Qt.QGridLayout()
        self.tab2_layout_0.addLayout(self.tab2_grid_layout_0)
        self.tab2.addTab(self.tab2_widget_0, 'Performance Evaluation')
        self.top_grid_layout.addWidget(self.tab2)
        self._snr_range = Range(-15, 100, 0.1, 50, 200)
        self._snr_win = RangeWidget(self._snr_range, self.set_snr, 'Signal to Noise Ratio (SNR)', "counter_slider", float)
        self.tab1_grid_layout_3.addWidget(self._snr_win)
        self._sig_field_options = (s1g_sig, def_sig, )
        self._sig_field_labels = ('Enable', 'Disable', )
        self._sig_field_group_box = Qt.QGroupBox('Enable SIG Field')
        self._sig_field_box = Qt.QHBoxLayout()
        class variable_chooser_button_group(Qt.QButtonGroup):
            def __init__(self, parent=None):
                Qt.QButtonGroup.__init__(self, parent)
            @pyqtSlot(int)
            def updateButtonChecked(self, button_id):
                self.button(button_id).setChecked(True)
        self._sig_field_button_group = variable_chooser_button_group()
        self._sig_field_group_box.setLayout(self._sig_field_box)
        for i, label in enumerate(self._sig_field_labels):
        	radio_button = Qt.QRadioButton(label)
        	self._sig_field_box.addWidget(radio_button)
        	self._sig_field_button_group.addButton(radio_button, i)
        self._sig_field_callback = lambda i: Qt.QMetaObject.invokeMethod(self._sig_field_button_group, "updateButtonChecked", Qt.Q_ARG("int", self._sig_field_options.index(i)))
        self._sig_field_callback(self.sig_field)
        self._sig_field_button_group.buttonClicked[int].connect(
        	lambda i: self.set_sig_field(self._sig_field_options[i]))
        self.tab1_grid_layout_2.addWidget(self._sig_field_group_box)
        self._samp_rate_options = (20e6, 2e6, )
        self._samp_rate_labels = ('Default Sample Rate (20 MSPS)', 'S1G Sample Rate (2 MSPS)', )
        self._samp_rate_group_box = Qt.QGroupBox('Sample Rate')
        self._samp_rate_box = Qt.QHBoxLayout()
        class variable_chooser_button_group(Qt.QButtonGroup):
            def __init__(self, parent=None):
                Qt.QButtonGroup.__init__(self, parent)
            @pyqtSlot(int)
            def updateButtonChecked(self, button_id):
                self.button(button_id).setChecked(True)
        self._samp_rate_button_group = variable_chooser_button_group()
        self._samp_rate_group_box.setLayout(self._samp_rate_box)
        for i, label in enumerate(self._samp_rate_labels):
        	radio_button = Qt.QRadioButton(label)
        	self._samp_rate_box.addWidget(radio_button)
        	self._samp_rate_button_group.addButton(radio_button, i)
        self._samp_rate_callback = lambda i: Qt.QMetaObject.invokeMethod(self._samp_rate_button_group, "updateButtonChecked", Qt.Q_ARG("int", self._samp_rate_options.index(i)))
        self._samp_rate_callback(self.samp_rate)
        self._samp_rate_button_group.buttonClicked[int].connect(
        	lambda i: self.set_samp_rate(self._samp_rate_options[i]))
        self.tab1_grid_layout_0.addWidget(self._samp_rate_group_box)
        self._s1g_encoding_options = [0, 1, 2,  3, 4, 5, 6, 7, 8, 9]
        self._s1g_encoding_labels = ["BPSK 1/2 (MCS 0)", "QPSK 1/2 (MCS 1)", "QPSK 3/4 (MCS 2)", "16-QAM 1/2 (MCS 3)", "16-QAM 3/4 (MCS 4)", "64-QAM 2/3 (MCS 5)", "64-QAM 3/4 (MCS 6)", "64-QAM 5/6 (MCS 7)",  "256-QAM 3/4 (MCS 8)",  "256-QAM 5/6 (MCS 9)"]
        self._s1g_encoding_tool_bar = Qt.QToolBar(self)
        self._s1g_encoding_tool_bar.addWidget(Qt.QLabel('Encoding'+": "))
        self._s1g_encoding_combo_box = Qt.QComboBox()
        self._s1g_encoding_tool_bar.addWidget(self._s1g_encoding_combo_box)
        for label in self._s1g_encoding_labels: self._s1g_encoding_combo_box.addItem(label)
        self._s1g_encoding_callback = lambda i: Qt.QMetaObject.invokeMethod(self._s1g_encoding_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._s1g_encoding_options.index(i)))
        self._s1g_encoding_callback(self.s1g_encoding)
        self._s1g_encoding_combo_box.currentIndexChanged.connect(
        	lambda i: self.set_s1g_encoding(self._s1g_encoding_options[i]))
        self.tab1_grid_layout_2.addWidget(self._s1g_encoding_tool_bar)
        self._s1g_cw_options = [2,4,8,16]
        self._s1g_cw_labels = ["2 MHz","4 MHz","8 MHz","16 MHz"]
        self._s1g_cw_tool_bar = Qt.QToolBar(self)
        self._s1g_cw_tool_bar.addWidget(Qt.QLabel('Channelwidth'+": "))
        self._s1g_cw_combo_box = Qt.QComboBox()
        self._s1g_cw_tool_bar.addWidget(self._s1g_cw_combo_box)
        for label in self._s1g_cw_labels: self._s1g_cw_combo_box.addItem(label)
        self._s1g_cw_callback = lambda i: Qt.QMetaObject.invokeMethod(self._s1g_cw_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._s1g_cw_options.index(i)))
        self._s1g_cw_callback(self.s1g_cw)
        self._s1g_cw_combo_box.currentIndexChanged.connect(
        	lambda i: self.set_s1g_cw(self._s1g_cw_options[i]))
        self.tab1_grid_layout_2.addWidget(self._s1g_cw_tool_bar)
        self._s1g_cap_options = (True, False, )
        self._s1g_cap_labels = ('Enable', 'Disable', )
        self._s1g_cap_group_box = Qt.QGroupBox('S1G')
        self._s1g_cap_box = Qt.QHBoxLayout()
        class variable_chooser_button_group(Qt.QButtonGroup):
            def __init__(self, parent=None):
                Qt.QButtonGroup.__init__(self, parent)
            @pyqtSlot(int)
            def updateButtonChecked(self, button_id):
                self.button(button_id).setChecked(True)
        self._s1g_cap_button_group = variable_chooser_button_group()
        self._s1g_cap_group_box.setLayout(self._s1g_cap_box)
        for i, label in enumerate(self._s1g_cap_labels):
        	radio_button = Qt.QRadioButton(label)
        	self._s1g_cap_box.addWidget(radio_button)
        	self._s1g_cap_button_group.addButton(radio_button, i)
        self._s1g_cap_callback = lambda i: Qt.QMetaObject.invokeMethod(self._s1g_cap_button_group, "updateButtonChecked", Qt.Q_ARG("int", self._s1g_cap_options.index(i)))
        self._s1g_cap_callback(self.s1g_cap)
        self._s1g_cap_button_group.buttonClicked[int].connect(
        	lambda i: self.set_s1g_cap(self._s1g_cap_options[i]))
        self.tab1_grid_layout_2.addWidget(self._s1g_cap_group_box)
        self._pdu_length_range = Range(0, 483, 1, 483, 200)
        self._pdu_length_win = RangeWidget(self._pdu_length_range, self.set_pdu_length, 'PDU Length', "counter_slider", int)
        self.tab1_grid_layout_0.addWidget(self._pdu_length_win)
        self._interval_range = Range(10, 10000, 1, 300, 200)
        self._interval_win = RangeWidget(self._interval_range, self.set_interval, 'Message Interval', "counter_slider", int)
        self.tab1_grid_layout_0.addWidget(self._interval_win)
        self._freq_range = Range(100e6, 900e6, 1e6, 900e6, 200)
        self._freq_win = RangeWidget(self._freq_range, self.set_freq, 'Frequency', "counter_slider", float)
        self.tab1_grid_layout_3.addWidget(self._freq_win)
        self._epsilon_range = Range(-20e-6, 20e-6, 1e-6, 0, 200)
        self._epsilon_win = RangeWidget(self._epsilon_range, self.set_epsilon, 'Epsilon', "counter_slider", float)
        self.tab1_grid_layout_3.addWidget(self._epsilon_win)
        self._encoding_options = [0, 1, 2, 3, 4, 5, 6, 7]
        self._encoding_labels = ["BPSK 1/2", "BPSK 3/4", "QPSK 1/2", "QPSK 3/4", "16QAM 1/2", "16QAM 3/4", "64QAM 2/3", "64QAM 3/4"]
        self._encoding_group_box = Qt.QGroupBox('Encoding')
        self._encoding_box = Qt.QHBoxLayout()
        class variable_chooser_button_group(Qt.QButtonGroup):
            def __init__(self, parent=None):
                Qt.QButtonGroup.__init__(self, parent)
            @pyqtSlot(int)
            def updateButtonChecked(self, button_id):
                self.button(button_id).setChecked(True)
        self._encoding_button_group = variable_chooser_button_group()
        self._encoding_group_box.setLayout(self._encoding_box)
        for i, label in enumerate(self._encoding_labels):
        	radio_button = Qt.QRadioButton(label)
        	self._encoding_box.addWidget(radio_button)
        	self._encoding_button_group.addButton(radio_button, i)
        self._encoding_callback = lambda i: Qt.QMetaObject.invokeMethod(self._encoding_button_group, "updateButtonChecked", Qt.Q_ARG("int", self._encoding_options.index(i)))
        self._encoding_callback(self.encoding)
        self._encoding_button_group.buttonClicked[int].connect(
        	lambda i: self.set_encoding(self._encoding_options[i]))
        self.tab1_grid_layout_1.addWidget(self._encoding_group_box)
        self._chan_est_options = [ieee802_11.LS, ieee802_11.LMS, ieee802_11.STA, ieee802_11.COMB]
        self._chan_est_labels = ["LS", "LMS", "STA", "Linear Comb"]
        self._chan_est_group_box = Qt.QGroupBox('Channel Estimation')
        self._chan_est_box = Qt.QHBoxLayout()
        class variable_chooser_button_group(Qt.QButtonGroup):
            def __init__(self, parent=None):
                Qt.QButtonGroup.__init__(self, parent)
            @pyqtSlot(int)
            def updateButtonChecked(self, button_id):
                self.button(button_id).setChecked(True)
        self._chan_est_button_group = variable_chooser_button_group()
        self._chan_est_group_box.setLayout(self._chan_est_box)
        for i, label in enumerate(self._chan_est_labels):
        	radio_button = Qt.QRadioButton(label)
        	self._chan_est_box.addWidget(radio_button)
        	self._chan_est_button_group.addButton(radio_button, i)
        self._chan_est_callback = lambda i: Qt.QMetaObject.invokeMethod(self._chan_est_button_group, "updateButtonChecked", Qt.Q_ARG("int", self._chan_est_options.index(i)))
        self._chan_est_callback(self.chan_est)
        self._chan_est_button_group.buttonClicked[int].connect(
        	lambda i: self.set_chan_est(self._chan_est_options[i]))
        self.tab1_grid_layout_1.addWidget(self._chan_est_group_box)
        self.wifi_phy_hier_0 = wifi_phy_hier(
            bandwidth=samp_rate,
            chan_est=chan_est,
            encoding=encoding,
            fft_size=64,
            frequency=freq,
            occupied_carriers=def_carriers,
            pilot_carrier=pilot_carriers,
            pilot_symbols=pilot_symbols,
            s1g_cap=s1g_cap,
            s1g_cw=s1g_cw,
            s1g_encoding=s1g_encoding,
            s1g_sync_words=((0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), (0, 0j, 0, 0j, 1, -1j, -1, 1j, -1, 1j, -1, 1j, -1, -1j, 1, 1j, 1, -1j, -1, 1j, 1, 1j, 1, 1j, 1, 1j, -1, (-0-1j), 1, -1j, -1, 1j, 0, -1j, 1, (-0-1j), 1, -1j, 1, 1j, -1, -1j, 1, (-0-1j), -1, 1j, 1, 1j, 1, 1j, 1, 1j, -1, -1j, 1, 1j, 1, -1j, -1, (-0-1j), -1, 0j, 0, 0j), (0, 0, 0, 0, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 0, 1, -1, -1, 1, 1, -1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 0, 0, 0)),
            sensitivity=0.56,
            sig_field_bpsk_mod=[-1,1],
            sig_formatter=sig_field,
            sync_words=((0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (-1.4719601443879746-1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, (1.4719601443879746+1.4719601443879746j), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), (0, 0j, 0, 0j, 0, 0j, -1, 1j, -1, 1j, -1, 1j, -1, -1j, 1, 1j, 1, -1j, -1, 1j, 1, 1j, 1, 1j, 1, 1j, -1, (-0-1j), 1, -1j, -1, 1j, 0, -1j, 1, (-0-1j), 1, -1j, 1, 1j, -1, -1j, 1, (-0-1j), -1, 1j, 1, 1j, 1, 1j, 1, 1j, -1, -1j, 1, 1j, 1, -1j, -1, 0j, 0, 0j, 0, 0j), (0, 0, 0, 0, 0, 0, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 0, 1, -1, -1, 1, 1, -1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, 0, 0, 0, 0, 0)),
        )
        self.qtgui_time_sink_x_0 = qtgui.time_sink_c(
        	1024, #size
        	samp_rate, #samp_rate
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-3, 3)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_TAG, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "packet_len")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(True)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(True)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)

        if not True:
          self.qtgui_time_sink_x_0.disable_legend()

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in xrange(2):
            if len(labels[i]) == 0:
                if(i % 2 == 0):
                    self.qtgui_time_sink_x_0.set_line_label(i, "Re{{Data {0}}}".format(i/2))
                else:
                    self.qtgui_time_sink_x_0.set_line_label(i, "Im{{Data {0}}}".format(i/2))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.tab3_grid_layout_0.addWidget(self._qtgui_time_sink_x_0_win)
        self.qtgui_sink_x_0 = qtgui.sink_c(
        	1024, #fftsize
        	firdes.WIN_BLACKMAN_hARRIS, #wintype
        	0, #fc
        	samp_rate, #bw
        	"", #name
        	True, #plotfreq
        	True, #plotwaterfall
        	False, #plottime
        	False, #plotconst
        )
        self.qtgui_sink_x_0.set_update_time(1.0/10)
        self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_sink_x_0_win)

        self.qtgui_sink_x_0.enable_rf_freq(False)



        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_NONE,
            1
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title('')

        labels = ['Error Rate', '', '', '', '',
                  '', '', '', '', '']
        units = ['Percent', '', '', '', '',
                 '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
                  ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [3, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        for i in xrange(1):
            self.qtgui_number_sink_0.set_min(i, 0)
            self.qtgui_number_sink_0.set_max(i, 100)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.pyqwidget(), Qt.QWidget)
        self.tab2_grid_layout_0.addWidget(self._qtgui_number_sink_0_win)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
        	52*10, #size
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(True)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)

        if not True:
          self.qtgui_const_sink_x_0.disable_legend()

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
                  "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.tab3_grid_layout_1.addWidget(self._qtgui_const_sink_x_0_win)
        self.pfb_arb_resampler_xxx_0 = pfb.arb_resampler_ccf(
        	  1+epsilon,
                  taps=None,
        	  flt_size=32)
        self.pfb_arb_resampler_xxx_0.declare_sample_delay(0)

        self.ieee802_11_parse_mac_0 = ieee802_11.parse_mac(False, False)
        self.ieee802_11_mac_0 = ieee802_11.mac(([0x23, 0x23, 0x23, 0x23, 0x23, 0x23]), ([0x42, 0x42, 0x42, 0x42, 0x42, 0x42]), ([0xff, 0xff, 0xff, 0xff, 0xff, 0xff]), False)
        self.foo_packet_pad2_0 = foo.packet_pad2(False, False, 0.001, 500, 0)
        (self.foo_packet_pad2_0).set_min_output_buffer(96000)
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=1,
        	frequency_offset=epsilon * 5.89e9 / 10e6,
        	epsilon=1.0,
        	taps=(1.0, ),
        	noise_seed=0,
        	block_tags=False
        )
        self.blocks_pdu_to_tagged_stream_0_0 = blocks.pdu_to_tagged_stream(blocks.complex_t, 'packet_len')
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.float_t, 'packet_len')
        self.blocks_multiply_const_vxx_1 = blocks.multiply_const_vcc((1, ))
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc(((10**(snr/10.0))**.5, ))
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("".join("x" for i in range(pdu_length))), interval)



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.ieee802_11_mac_0, 'app in'))
        self.msg_connect((self.ieee802_11_mac_0, 'phy out'), (self.wifi_phy_hier_0, 'mac_in'))
        self.msg_connect((self.ieee802_11_parse_mac_0, 'fer'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))
        self.msg_connect((self.wifi_phy_hier_0, 'carrier'), (self.blocks_pdu_to_tagged_stream_0_0, 'pdus'))
        self.msg_connect((self.wifi_phy_hier_0, 'mac_out'), (self.ieee802_11_parse_mac_0, 'in'))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.channels_channel_model_0, 0))
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.qtgui_sink_x_0, 0))
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.qtgui_number_sink_0, 0))
        self.connect((self.blocks_pdu_to_tagged_stream_0_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.channels_channel_model_0, 0), (self.pfb_arb_resampler_xxx_0, 0))
        self.connect((self.foo_packet_pad2_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.pfb_arb_resampler_xxx_0, 0), (self.wifi_phy_hier_0, 0))
        self.connect((self.wifi_phy_hier_0, 0), (self.blocks_multiply_const_vxx_1, 0))
        self.connect((self.wifi_phy_hier_0, 0), (self.foo_packet_pad2_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "wifi_loopback")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_pilot_carriers(self):
        return self.pilot_carriers

    def set_pilot_carriers(self, pilot_carriers):
        self.pilot_carriers = pilot_carriers
        self.wifi_phy_hier_0.set_pilot_carrier(self.pilot_carriers)

    def get_pilot_symbols(self):
        return self.pilot_symbols

    def set_pilot_symbols(self, pilot_symbols):
        self.pilot_symbols = pilot_symbols
        self.wifi_phy_hier_0.set_pilot_symbols(self.pilot_symbols)

    def get_s1g_sig(self):
        return self.s1g_sig

    def set_s1g_sig(self, s1g_sig):
        self.s1g_sig = s1g_sig
        self.set_sig_field(self.s1g_sig)

    def get_snr(self):
        return self.snr

    def set_snr(self, snr):
        self.snr = snr
        self.blocks_multiply_const_vxx_0.set_k(((10**(self.snr/10.0))**.5, ))

    def get_sig_field(self):
        return self.sig_field

    def set_sig_field(self, sig_field):
        self.sig_field = sig_field
        self._sig_field_callback(self.sig_field)
        self.wifi_phy_hier_0.set_sig_formatter(self.sig_field)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self._samp_rate_callback(self.samp_rate)
        self.wifi_phy_hier_0.set_bandwidth(self.samp_rate)
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.qtgui_sink_x_0.set_frequency_range(0, self.samp_rate)

    def get_s1g_encoding(self):
        return self.s1g_encoding

    def set_s1g_encoding(self, s1g_encoding):
        self.s1g_encoding = s1g_encoding
        self._s1g_encoding_callback(self.s1g_encoding)
        self.wifi_phy_hier_0.set_s1g_encoding(self.s1g_encoding)

    def get_s1g_cw(self):
        return self.s1g_cw

    def set_s1g_cw(self, s1g_cw):
        self.s1g_cw = s1g_cw
        self._s1g_cw_callback(self.s1g_cw)
        self.wifi_phy_hier_0.set_s1g_cw(self.s1g_cw)

    def get_s1g_carriers(self):
        return self.s1g_carriers

    def set_s1g_carriers(self, s1g_carriers):
        self.s1g_carriers = s1g_carriers

    def get_s1g_cap(self):
        return self.s1g_cap

    def set_s1g_cap(self, s1g_cap):
        self.s1g_cap = s1g_cap
        self._s1g_cap_callback(self.s1g_cap)
        self.wifi_phy_hier_0.set_s1g_cap(self.s1g_cap)

    def get_pdu_length(self):
        return self.pdu_length

    def set_pdu_length(self, pdu_length):
        self.pdu_length = pdu_length
        self.blocks_message_strobe_0.set_msg(pmt.intern("".join("x" for i in range(self.pdu_length))))

    def get_out_buf_size(self):
        return self.out_buf_size

    def set_out_buf_size(self, out_buf_size):
        self.out_buf_size = out_buf_size

    def get_interval(self):
        return self.interval

    def set_interval(self, interval):
        self.interval = interval
        self.blocks_message_strobe_0.set_period(self.interval)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.wifi_phy_hier_0.set_frequency(self.freq)

    def get_epsilon(self):
        return self.epsilon

    def set_epsilon(self, epsilon):
        self.epsilon = epsilon
        self.pfb_arb_resampler_xxx_0.set_rate(1+self.epsilon)
        self.channels_channel_model_0.set_frequency_offset(self.epsilon * 5.89e9 / 10e6)

    def get_encoding(self):
        return self.encoding

    def set_encoding(self, encoding):
        self.encoding = encoding
        self._encoding_callback(self.encoding)
        self.wifi_phy_hier_0.set_encoding(self.encoding)

    def get_def_sig(self):
        return self.def_sig

    def set_def_sig(self, def_sig):
        self.def_sig = def_sig

    def get_def_carriers(self):
        return self.def_carriers

    def set_def_carriers(self, def_carriers):
        self.def_carriers = def_carriers
        self.wifi_phy_hier_0.set_occupied_carriers(self.def_carriers)

    def get_chan_est(self):
        return self.chan_est

    def set_chan_est(self, chan_est):
        self.chan_est = chan_est
        self._chan_est_callback(self.chan_est)
        self.wifi_phy_hier_0.set_chan_est(self.chan_est)


def argument_parser():
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option)
    return parser


def main(top_block_cls=wifi_loopback, options=None):
    if options is None:
        options, _ = argument_parser().parse_args()

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
