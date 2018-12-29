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
Sheet 10 16
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
L Conn_01x02 J11
U 1 1 5C2724E0
P 6250 3200
AR Path="/5C274B1F/5C2724E0" Ref="J11"  Part="1" 
AR Path="/5C27248A/5C2724E0" Ref="J6"  Part="1" 
AR Path="/5C273411/5C2724E0" Ref="J7"  Part="1" 
AR Path="/5C273557/5C2724E0" Ref="J8"  Part="1" 
AR Path="/5C2736A9/5C2724E0" Ref="J9"  Part="1" 
AR Path="/5C27393D/5C2724E0" Ref="J10"  Part="1" 
AR Path="/5C274C89/5C2724E0" Ref="J12"  Part="1" 
F 0 "J12" H 6250 3300 50  0000 C CNN
F 1 "Button" H 6450 3150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 6250 3200 50  0001 C CNN
F 3 "" H 6250 3200 50  0001 C CNN
	1    6250 3200
	1    0    0    1   
$EndComp
Text HLabel 5800 3100 0    60   Output ~ 0
BTN
$Comp
L R R16
U 1 1 5C272553
P 5950 2900
AR Path="/5C274B1F/5C272553" Ref="R16"  Part="1" 
AR Path="/5C27248A/5C272553" Ref="R11"  Part="1" 
AR Path="/5C273411/5C272553" Ref="R12"  Part="1" 
AR Path="/5C273557/5C272553" Ref="R13"  Part="1" 
AR Path="/5C2736A9/5C272553" Ref="R14"  Part="1" 
AR Path="/5C27393D/5C272553" Ref="R15"  Part="1" 
AR Path="/5C274C89/5C272553" Ref="R17"  Part="1" 
F 0 "R17" H 6100 2950 50  0000 C CNN
F 1 "10k" H 6100 2850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5880 2900 50  0001 C CNN
F 3 "" H 5950 2900 50  0001 C CNN
	1    5950 2900
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR046
U 1 1 5C27258C
P 5950 2750
AR Path="/5C274B1F/5C27258C" Ref="#PWR046"  Part="1" 
AR Path="/5C27248A/5C27258C" Ref="#PWR036"  Part="1" 
AR Path="/5C273411/5C27258C" Ref="#PWR038"  Part="1" 
AR Path="/5C273557/5C27258C" Ref="#PWR040"  Part="1" 
AR Path="/5C2736A9/5C27258C" Ref="#PWR042"  Part="1" 
AR Path="/5C27393D/5C27258C" Ref="#PWR044"  Part="1" 
AR Path="/5C274C89/5C27258C" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 5950 2600 50  0001 C CNN
F 1 "+3V3" H 5950 2890 50  0000 C CNN
F 2 "" H 5950 2750 50  0001 C CNN
F 3 "" H 5950 2750 50  0001 C CNN
	1    5950 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3100 6050 3100
Wire Wire Line
	5950 3050 5950 3100
Connection ~ 5950 3100
$Comp
L GND #PWR047
U 1 1 5C2725B6
P 5950 3200
AR Path="/5C274B1F/5C2725B6" Ref="#PWR047"  Part="1" 
AR Path="/5C27248A/5C2725B6" Ref="#PWR037"  Part="1" 
AR Path="/5C273411/5C2725B6" Ref="#PWR039"  Part="1" 
AR Path="/5C273557/5C2725B6" Ref="#PWR041"  Part="1" 
AR Path="/5C2736A9/5C2725B6" Ref="#PWR043"  Part="1" 
AR Path="/5C27393D/5C2725B6" Ref="#PWR045"  Part="1" 
AR Path="/5C274C89/5C2725B6" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 5950 2950 50  0001 C CNN
F 1 "GND" H 5950 3050 50  0000 C CNN
F 2 "" H 5950 3200 50  0001 C CNN
F 3 "" H 5950 3200 50  0001 C CNN
	1    5950 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3200 5950 3200
$EndSCHEMATC
