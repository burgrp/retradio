EESchema Schematic File Version 4
LIBS:encoder-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L device:Rotary_Encoder_Switch SW1
U 1 1 5C2D43A9
P 6000 3650
F 0 "SW1" H 6000 3910 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 6400 3000 50  0001 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E-Switch_Vertical_H20mm" H 5900 3810 50  0001 C CNN
F 3 "" H 6000 3910 50  0001 C CNN
	1    6000 3650
	1    0    0    -1  
$EndComp
$Comp
L device.farm:I2C-6P X1
U 1 1 5C2D4514
P 2050 3900
F 0 "X1" H 2050 4400 60  0000 C CNN
F 1 "I2C-6P" H 2050 3550 60  0000 C CNN
F 2 "Connectors:IDC_Header_Straight_6pins" H 2200 4050 60  0001 C CNN
F 3 "" H 2200 4050 60  0001 C CNN
	1    2050 3900
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F0:STM32F030F4Px U1
U 1 1 5C2D459B
P 4450 4050
F 0 "U1" H 4050 4700 50  0000 L CNN
F 1 "STM32F030F4Px" H 4650 4700 50  0000 L CNN
F 2 "Housings_SSOP:SSOP-20_4.4x6.5mm_Pitch0.65mm" H 4050 3350 50  0001 R CNN
F 3 "" H 4450 4050 50  0001 C CNN
	1    4450 4050
	1    0    0    -1  
$EndComp
Text Label 2400 3850 0    60   ~ 0
SDA
Text Label 2400 3950 0    60   ~ 0
SCL
$Comp
L power:+3V3 #PWR01
U 1 1 5C2D46F6
P 2400 3700
F 0 "#PWR01" H 2400 3550 50  0001 C CNN
F 1 "+3V3" V 2400 3950 50  0000 C CNN
F 2 "" H 2400 3700 50  0001 C CNN
F 3 "" H 2400 3700 50  0001 C CNN
	1    2400 3700
	0    1    1    0   
$EndComp
NoConn ~ 2400 3600
Text Label 2400 3500 0    60   ~ 0
ALERT
Wire Wire Line
	4950 3550 5700 3550
Wire Wire Line
	4950 3650 5400 3650
Wire Wire Line
	5400 3650 5400 3750
Wire Wire Line
	5400 3750 5700 3750
Wire Wire Line
	4950 3750 5350 3750
Wire Wire Line
	5350 3750 5350 3900
Wire Wire Line
	5350 3900 6650 3900
Wire Wire Line
	6650 3900 6650 3550
Wire Wire Line
	6650 3550 6300 3550
NoConn ~ 4950 4050
NoConn ~ 4950 4150
NoConn ~ 3950 4650
NoConn ~ 3950 4450
NoConn ~ 3950 4350
$Comp
L power:GND #PWR02
U 1 1 5C2D490B
P 3950 3750
F 0 "#PWR02" H 3950 3500 50  0001 C CNN
F 1 "GND" V 3950 3550 50  0000 C CNN
F 2 "" H 3950 3750 50  0001 C CNN
F 3 "" H 3950 3750 50  0001 C CNN
	1    3950 3750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5C2D491F
P 4450 4850
F 0 "#PWR03" H 4450 4600 50  0001 C CNN
F 1 "GND" H 4450 4700 50  0000 C CNN
F 2 "" H 4450 4850 50  0001 C CNN
F 3 "" H 4450 4850 50  0001 C CNN
	1    4450 4850
	1    0    0    -1  
$EndComp
$Comp
L device:C C1
U 1 1 5C2D4945
P 3700 3550
F 0 "C1" V 3550 3400 50  0000 L CNN
F 1 "100n" V 3550 3550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3738 3400 50  0001 C CNN
F 3 "" H 3700 3550 50  0001 C CNN
	1    3700 3550
	0    1    1    0   
$EndComp
$Comp
L device:C C2
U 1 1 5C2D49B4
P 4250 3200
F 0 "C2" V 4100 3050 50  0000 L CNN
F 1 "100n" V 4100 3200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4288 3050 50  0001 C CNN
F 3 "" H 4250 3200 50  0001 C CNN
	1    4250 3200
	0    1    1    0   
$EndComp
$Comp
L device:C C3
U 1 1 5C2D49F5
P 4750 3200
F 0 "C3" V 4600 3050 50  0000 L CNN
F 1 "100n" V 4600 3200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4788 3050 50  0001 C CNN
F 3 "" H 4750 3200 50  0001 C CNN
	1    4750 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 3350 4450 3200
Wire Wire Line
	4400 3200 4450 3200
Wire Wire Line
	4550 3200 4550 3350
Connection ~ 4550 3200
Connection ~ 4450 3200
Wire Wire Line
	4500 3200 4500 3100
Connection ~ 4500 3200
$Comp
L power:+3V3 #PWR04
U 1 1 5C2D4A80
P 4500 3100
F 0 "#PWR04" H 4500 2950 50  0001 C CNN
F 1 "+3V3" H 4500 3240 50  0000 C CNN
F 2 "" H 4500 3100 50  0001 C CNN
F 3 "" H 4500 3100 50  0001 C CNN
	1    4500 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5C2D4A9D
P 4100 3200
F 0 "#PWR05" H 4100 2950 50  0001 C CNN
F 1 "GND" V 4100 3000 50  0000 C CNN
F 2 "" H 4100 3200 50  0001 C CNN
F 3 "" H 4100 3200 50  0001 C CNN
	1    4100 3200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5C2D4ABA
P 4900 3200
F 0 "#PWR06" H 4900 2950 50  0001 C CNN
F 1 "GND" V 4900 3000 50  0000 C CNN
F 2 "" H 4900 3200 50  0001 C CNN
F 3 "" H 4900 3200 50  0001 C CNN
	1    4900 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3850 3550 3950 3550
$Comp
L power:GND #PWR07
U 1 1 5C2D4AEF
P 3550 3550
F 0 "#PWR07" H 3550 3300 50  0001 C CNN
F 1 "GND" V 3550 3350 50  0000 C CNN
F 2 "" H 3550 3550 50  0001 C CNN
F 3 "" H 3550 3550 50  0001 C CNN
	1    3550 3550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5C2D4B99
P 6300 3750
F 0 "#PWR08" H 6300 3500 50  0001 C CNN
F 1 "GND" V 6300 3550 50  0000 C CNN
F 2 "" H 6300 3750 50  0001 C CNN
F 3 "" H 6300 3750 50  0001 C CNN
	1    6300 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5C2D4BB6
P 5700 3650
F 0 "#PWR09" H 5700 3400 50  0001 C CNN
F 1 "GND" V 5700 3450 50  0000 C CNN
F 2 "" H 5700 3650 50  0001 C CNN
F 3 "" H 5700 3650 50  0001 C CNN
	1    5700 3650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5C2D4C2F
P 2400 4100
F 0 "#PWR010" H 2400 3850 50  0001 C CNN
F 1 "GND" V 2400 3900 50  0000 C CNN
F 2 "" H 2400 4100 50  0001 C CNN
F 3 "" H 2400 4100 50  0001 C CNN
	1    2400 4100
	0    -1   -1   0   
$EndComp
Text Label 4950 4350 0    60   ~ 0
SCL
Text Label 4950 4450 0    60   ~ 0
SDA
Text Label 4950 4250 0    60   ~ 0
ALERT
$Comp
L power:PWR_FLAG #FLG011
U 1 1 5C2D4FB2
P 2250 4700
F 0 "#FLG011" H 2250 4775 50  0001 C CNN
F 1 "PWR_FLAG" V 2250 5000 50  0000 C CNN
F 2 "" H 2250 4700 50  0001 C CNN
F 3 "" H 2250 4700 50  0001 C CNN
	1    2250 4700
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG012
U 1 1 5C2D4FF2
P 2250 4800
F 0 "#FLG012" H 2250 4875 50  0001 C CNN
F 1 "PWR_FLAG" V 2250 5100 50  0000 C CNN
F 2 "" H 2250 4800 50  0001 C CNN
F 3 "" H 2250 4800 50  0001 C CNN
	1    2250 4800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5C2D500F
P 2250 4800
F 0 "#PWR013" H 2250 4550 50  0001 C CNN
F 1 "GND" V 2250 4600 50  0000 C CNN
F 2 "" H 2250 4800 50  0001 C CNN
F 3 "" H 2250 4800 50  0001 C CNN
	1    2250 4800
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR014
U 1 1 5C2D502C
P 2250 4700
F 0 "#PWR014" H 2250 4550 50  0001 C CNN
F 1 "+3V3" V 2250 4950 50  0000 C CNN
F 2 "" H 2250 4700 50  0001 C CNN
F 3 "" H 2250 4700 50  0001 C CNN
	1    2250 4700
	0    1    1    0   
$EndComp
Text Label 4950 4550 0    60   ~ 0
SWDIO
Text Label 4950 4650 0    60   ~ 0
SWCLK
$Comp
L device.farm:SWD X2
U 1 1 5C2D529E
P 2200 5350
F 0 "X2" H 2200 5600 60  0000 C CNN
F 1 "SWD" H 2200 5100 60  0000 C CNN
F 2 "device.farm:SWD" H 2200 5350 60  0001 C CNN
F 3 "" H 2200 5350 60  0000 C CNN
	1    2200 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5C2D5329
P 2550 5350
F 0 "#PWR015" H 2550 5100 50  0001 C CNN
F 1 "GND" V 2550 5150 50  0000 C CNN
F 2 "" H 2550 5350 50  0001 C CNN
F 3 "" H 2550 5350 50  0001 C CNN
	1    2550 5350
	0    -1   -1   0   
$EndComp
Text Label 2550 5250 0    60   ~ 0
SWDIO
Text Label 2550 5450 0    60   ~ 0
SWCLK
$Comp
L conn:GS3 J1
U 1 1 5C2D5CA6
P 5950 4150
F 0 "J1" H 5600 4150 50  0000 C CNN
F 1 "GS3" H 5750 4150 50  0000 C CNN
F 2 "Connectors:GS3" V 6038 4076 50  0001 C CNN
F 3 "" H 5950 4150 50  0001 C CNN
	1    5950 4150
	-1   0    0    1   
$EndComp
$Comp
L conn:GS3 J2
U 1 1 5C2D5D1D
P 5950 4500
F 0 "J2" H 5600 4500 50  0000 C CNN
F 1 "GS3" H 5750 4500 50  0000 C CNN
F 2 "Connectors:GS3" V 6038 4426 50  0001 C CNN
F 3 "" H 5950 4500 50  0001 C CNN
	1    5950 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 3850 5300 3850
Wire Wire Line
	5300 3850 5300 4150
Wire Wire Line
	5300 4150 5800 4150
Wire Wire Line
	4950 3950 5250 3950
Wire Wire Line
	5250 3950 5250 4500
Wire Wire Line
	5250 4500 5800 4500
$Comp
L power:GND #PWR016
U 1 1 5C2D5F54
P 6100 4600
F 0 "#PWR016" H 6100 4350 50  0001 C CNN
F 1 "GND" V 6100 4400 50  0000 C CNN
F 2 "" H 6100 4600 50  0001 C CNN
F 3 "" H 6100 4600 50  0001 C CNN
	1    6100 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5C2D5F7A
P 6100 4250
F 0 "#PWR017" H 6100 4000 50  0001 C CNN
F 1 "GND" V 6100 4050 50  0000 C CNN
F 2 "" H 6100 4250 50  0001 C CNN
F 3 "" H 6100 4250 50  0001 C CNN
	1    6100 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR018
U 1 1 5C2D5FA0
P 6100 4050
F 0 "#PWR018" H 6100 3900 50  0001 C CNN
F 1 "+3V3" V 6100 4250 50  0000 C CNN
F 2 "" H 6100 4050 50  0001 C CNN
F 3 "" H 6100 4050 50  0001 C CNN
	1    6100 4050
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR019
U 1 1 5C2D602B
P 6100 4400
F 0 "#PWR019" H 6100 4250 50  0001 C CNN
F 1 "+3V3" V 6100 4600 50  0000 C CNN
F 2 "" H 6100 4400 50  0001 C CNN
F 3 "" H 6100 4400 50  0001 C CNN
	1    6100 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 3200 4600 3200
Wire Wire Line
	4450 3200 4500 3200
Wire Wire Line
	4500 3200 4550 3200
$EndSCHEMATC