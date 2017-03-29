# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Dropbox\blog\UV sensor\SW\UVSensorCypress\UV Sensor.cydsn\UV Sensor.cyprj
# Date: Wed, 29 Mar 2017 03:19:46 GMT
#set_units -time ns
create_clock -name {ADC_intClock(FFB)} -period 187.5 -waveform {0 93.75} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {CyRouted1} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {ADC_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 7} [list]


# Component constraints for D:\Dropbox\blog\UV sensor\SW\UVSensorCypress\UV Sensor.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Dropbox\blog\UV sensor\SW\UVSensorCypress\UV Sensor.cydsn\UV Sensor.cyprj
# Date: Wed, 29 Mar 2017 03:19:44 GMT