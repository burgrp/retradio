EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:device.farm
LIBS:PAM8320
LIBS:retradio-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Conn_01x05 J?
U 1 1 5C26BCAE
P 5750 2600
F 0 "J?" H 5750 2900 50  0000 C CNN
F 1 "Encoder" H 6000 2650 50  0000 C CNN
F 2 "" H 5750 2600 50  0001 C CNN
F 3 "" H 5750 2600 50  0001 C CNN
	1    5750 2600
	1    0    0    1   
$EndComp
$Comp
L R R?
U 1 1 5C26BD7D
P 5400 2200
F 0 "R?" H 5500 2250 50  0000 C CNN
F 1 "10k" H 5550 2150 50  0000 C CNN
F 2 "" V 5330 2200 50  0001 C CNN
F 3 "" H 5400 2200 50  0001 C CNN
	1    5400 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5C26BE29
P 5100 2200
F 0 "R?" H 5200 2250 50  0000 C CNN
F 1 "10k" H 5250 2150 50  0000 C CNN
F 2 "" V 5030 2200 50  0001 C CNN
F 3 "" H 5100 2200 50  0001 C CNN
	1    5100 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5C26BE4A
P 4800 2200
F 0 "R?" H 4900 2250 50  0000 C CNN
F 1 "10k" H 4950 2150 50  0000 C CNN
F 2 "" V 4730 2200 50  0001 C CNN
F 3 "" H 4800 2200 50  0001 C CNN
	1    4800 2200
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5C26BE8C
P 5450 2700
F 0 "#PWR?" H 5450 2550 50  0001 C CNN
F 1 "+3V3" H 5450 2840 50  0000 C CNN
F 2 "" H 5450 2700 50  0001 C CNN
F 3 "" H 5450 2700 50  0001 C CNN
	1    5450 2700
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5C26BEAE
P 4800 2050
F 0 "#PWR?" H 4800 1900 50  0001 C CNN
F 1 "+3V3" H 4800 2190 50  0000 C CNN
F 2 "" H 4800 2050 50  0001 C CNN
F 3 "" H 4800 2050 50  0001 C CNN
	1    4800 2050
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5C26BEE1
P 5100 2050
F 0 "#PWR?" H 5100 1900 50  0001 C CNN
F 1 "+3V3" H 5100 2190 50  0000 C CNN
F 2 "" H 5100 2050 50  0001 C CNN
F 3 "" H 5100 2050 50  0001 C CNN
	1    5100 2050
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 5C26BEF8
P 5400 2050
F 0 "#PWR?" H 5400 1900 50  0001 C CNN
F 1 "+3V3" H 5400 2190 50  0000 C CNN
F 2 "" H 5400 2050 50  0001 C CNN
F 3 "" H 5400 2050 50  0001 C CNN
	1    5400 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5C26BF31
P 5450 2800
F 0 "#PWR?" H 5450 2550 50  0001 C CNN
F 1 "GND" H 5450 2650 50  0000 C CNN
F 2 "" H 5450 2800 50  0001 C CNN
F 3 "" H 5450 2800 50  0001 C CNN
	1    5450 2800
	1    0    0    -1  
$EndComp
Text HLabel 4600 2400 0    60   Output ~ 0
CL
Text HLabel 4600 2500 0    60   Output ~ 0
DT
Text HLabel 4600 2600 0    60   Output ~ 0
SW
Wire Wire Line
	4600 2400 5550 2400
Wire Wire Line
	5550 2500 4600 2500
Wire Wire Line
	4600 2600 5550 2600
Wire Wire Line
	5550 2700 5450 2700
Wire Wire Line
	5450 2800 5550 2800
Wire Wire Line
	4800 2350 4800 2400
Connection ~ 4800 2400
Wire Wire Line
	5100 2350 5100 2500
Connection ~ 5100 2500
Wire Wire Line
	5400 2350 5400 2600
Connection ~ 5400 2600
$EndSCHEMATC
