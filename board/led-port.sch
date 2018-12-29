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
Sheet 13 16
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
L R R21
U 1 1 5C27D446
P 5650 3050
AR Path="/5C27D3CA/5C27D446" Ref="R21"  Part="1" 
AR Path="/5C27E615/5C27D446" Ref="R22"  Part="1" 
AR Path="/5C27E75F/5C27D446" Ref="R23"  Part="1" 
AR Path="/5C27E8A9/5C27D446" Ref="R24"  Part="1" 
F 0 "R24" V 5730 3050 50  0000 C CNN
F 1 "270R" V 5550 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5580 3050 50  0001 C CNN
F 3 "" H 5650 3050 50  0001 C CNN
	1    5650 3050
	0    1    1    0   
$EndComp
$Comp
L Conn_01x02 J14
U 1 1 5C27D4C9
P 6000 3150
AR Path="/5C27D3CA/5C27D4C9" Ref="J14"  Part="1" 
AR Path="/5C27E615/5C27D4C9" Ref="J15"  Part="1" 
AR Path="/5C27E75F/5C27D4C9" Ref="J16"  Part="1" 
AR Path="/5C27E8A9/5C27D4C9" Ref="J17"  Part="1" 
F 0 "J17" H 6000 3250 50  0000 C CNN
F 1 "LED" H 6150 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6000 3150 50  0001 C CNN
F 3 "" H 6000 3150 50  0001 C CNN
	1    6000 3150
	1    0    0    1   
$EndComp
$Comp
L GND #PWR055
U 1 1 5C27D50F
P 5800 3150
AR Path="/5C27D3CA/5C27D50F" Ref="#PWR055"  Part="1" 
AR Path="/5C27E615/5C27D50F" Ref="#PWR057"  Part="1" 
AR Path="/5C27E75F/5C27D50F" Ref="#PWR059"  Part="1" 
AR Path="/5C27E8A9/5C27D50F" Ref="#PWR061"  Part="1" 
F 0 "#PWR061" H 5800 2900 50  0001 C CNN
F 1 "GND" H 5800 3000 50  0000 C CNN
F 2 "" H 5800 3150 50  0001 C CNN
F 3 "" H 5800 3150 50  0001 C CNN
	1    5800 3150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR056
U 1 1 5C27E413
P 5500 3050
AR Path="/5C27D3CA/5C27E413" Ref="#PWR056"  Part="1" 
AR Path="/5C27E615/5C27E413" Ref="#PWR058"  Part="1" 
AR Path="/5C27E75F/5C27E413" Ref="#PWR060"  Part="1" 
AR Path="/5C27E8A9/5C27E413" Ref="#PWR062"  Part="1" 
F 0 "#PWR062" H 5500 2900 50  0001 C CNN
F 1 "+5V" H 5500 3190 50  0000 C CNN
F 2 "" H 5500 3050 50  0001 C CNN
F 3 "" H 5500 3050 50  0001 C CNN
	1    5500 3050
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
