EESchema Schematic File Version 4
EELAYER 30 0
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
L Device:Rotary_Encoder_Switch SW1
U 1 1 5C2D43A9
P 5800 2400
F 0 "SW1" H 5800 2660 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 6200 1750 50  0001 C CNN
F 2 "Drake:RotaryEncoder_Bourns_PEC12R-4x20F-Sxxxx" H 5700 2560 50  0001 C CNN
F 3 "" H 5800 2660 50  0001 C CNN
	1    5800 2400
	1    0    0    -1  
$EndComp
$Comp
L Drake:I2C-6P X1
U 1 1 5C2D4514
P 2050 3900
F 0 "X1" H 2050 4400 60  0000 C CNN
F 1 "I2C-6P" H 2050 3550 60  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" H 2200 4050 60  0001 C CNN
F 3 "" H 2200 4050 60  0001 C CNN
	1    2050 3900
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
$Comp
L power:GND #PWR02
U 1 1 5C2D490B
P 4550 5200
F 0 "#PWR02" H 4550 4950 50  0001 C CNN
F 1 "GND" V 4550 5000 50  0000 C CNN
F 2 "" H 4550 5200 50  0001 C CNN
F 3 "" H 4550 5200 50  0001 C CNN
	1    4550 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5C2D4945
P 3650 3400
F 0 "C1" H 3750 3500 50  0000 L CNN
F 1 "100n" H 3750 3300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3688 3250 50  0001 C CNN
F 3 "" H 3650 3400 50  0001 C CNN
	1    3650 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5C2D49B4
P 3900 4200
F 0 "C2" V 3750 4050 50  0000 L CNN
F 1 "100n" V 3750 4200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3938 4050 50  0001 C CNN
F 3 "" H 3900 4200 50  0001 C CNN
	1    3900 4200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5C2D4A9D
P 3750 4200
F 0 "#PWR05" H 3750 3950 50  0001 C CNN
F 1 "GND" V 3750 4000 50  0000 C CNN
F 2 "" H 3750 4200 50  0001 C CNN
F 3 "" H 3750 4200 50  0001 C CNN
	1    3750 4200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5C2D4AEF
P 3650 3550
F 0 "#PWR07" H 3650 3300 50  0001 C CNN
F 1 "GND" V 3650 3350 50  0000 C CNN
F 2 "" H 3650 3550 50  0001 C CNN
F 3 "" H 3650 3550 50  0001 C CNN
	1    3650 3550
	1    0    0    -1  
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
Text Label 5050 4600 0    60   ~ 0
SCL
Text Label 5050 4500 0    60   ~ 0
SDA
Text Label 5050 4400 0    60   ~ 0
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
Text Label 4050 4500 2    60   ~ 0
SWDIO
$Comp
L Drake:SWD X2
U 1 1 5C2D529E
P 2200 5350
F 0 "X2" H 2200 5600 60  0000 C CNN
F 1 "SWD" H 2200 5100 60  0000 C CNN
F 2 "Drake:SWD" H 2200 5350 60  0001 C CNN
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
L Jumper:SolderJumper_3_Open J1
U 1 1 5C2D5CA6
P 7200 4650
F 0 "J1" H 7050 4600 50  0000 C CNN
F 1 "GS3" H 7200 4750 50  0000 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" V 7288 4576 50  0001 C CNN
F 3 "" H 7200 4650 50  0001 C CNN
	1    7200 4650
	0    1    -1   0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open J2
U 1 1 5C2D5D1D
P 6500 4650
F 0 "J2" H 6350 4600 50  0000 C CNN
F 1 "GS3" H 6500 4750 50  0000 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" V 6588 4576 50  0001 C CNN
F 3 "" H 6500 4650 50  0001 C CNN
	1    6500 4650
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5C2D5F54
P 7200 4850
F 0 "#PWR016" H 7200 4600 50  0001 C CNN
F 1 "GND" V 7200 4650 50  0000 C CNN
F 2 "" H 7200 4850 50  0001 C CNN
F 3 "" H 7200 4850 50  0001 C CNN
	1    7200 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5C2D5F7A
P 6500 4850
F 0 "#PWR017" H 6500 4600 50  0001 C CNN
F 1 "GND" V 6500 4650 50  0000 C CNN
F 2 "" H 6500 4850 50  0001 C CNN
F 3 "" H 6500 4850 50  0001 C CNN
	1    6500 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR018
U 1 1 5C2D5FA0
P 7200 4450
F 0 "#PWR018" H 7200 4300 50  0001 C CNN
F 1 "+3V3" V 7200 4650 50  0000 C CNN
F 2 "" H 7200 4450 50  0001 C CNN
F 3 "" H 7200 4450 50  0001 C CNN
	1    7200 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR019
U 1 1 5C2D602B
P 6500 4450
F 0 "#PWR019" H 6500 4300 50  0001 C CNN
F 1 "+3V3" V 6500 4650 50  0000 C CNN
F 2 "" H 6500 4450 50  0001 C CNN
F 3 "" H 6500 4450 50  0001 C CNN
	1    6500 4450
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_SAMD:ATSAMD11C14A-SS U1
U 1 1 60420C78
P 4550 4500
F 0 "U1" H 4700 5300 50  0000 C CNN
F 1 "ATSAMD11C14A-SS" H 5000 5200 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 4550 3450 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42363-SAM-D11_Datasheet.pdf" H 4550 3800 50  0001 C CNN
	1    4550 4500
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 604300B8
P 4550 3800
F 0 "#PWR04" H 4550 3650 50  0001 C CNN
F 1 "+3V3" V 4550 4050 50  0000 C CNN
F 2 "" H 4550 3800 50  0001 C CNN
F 3 "" H 4550 3800 50  0001 C CNN
	1    4550 3800
	1    0    0    -1  
$EndComp
Text Label 6350 4650 2    50   ~ 0
ADDR0
Text Label 7050 4650 2    50   ~ 0
ADDR1
Text Label 6750 2300 0    50   ~ 0
ENCP
Text Label 4850 2300 2    50   ~ 0
ENCA
Text Label 4850 2500 2    50   ~ 0
ENCB
$Comp
L power:+3V3 #PWR03
U 1 1 60443037
P 3650 3250
F 0 "#PWR03" H 3650 3100 50  0001 C CNN
F 1 "+3V3" V 3650 3500 50  0000 C CNN
F 2 "" H 3650 3250 50  0001 C CNN
F 3 "" H 3650 3250 50  0001 C CNN
	1    3650 3250
	1    0    0    -1  
$EndComp
Text Label 4050 4700 2    50   ~ 0
ADDR0
Text Label 4050 4800 2    50   ~ 0
ADDR1
Text Label 4050 4400 2    60   ~ 0
SWCLK
Text Label 5050 4200 0    50   ~ 0
ENCA
Text Label 5050 4300 0    50   ~ 0
ENCB
Text Label 5050 4700 0    50   ~ 0
ENCP
NoConn ~ 5050 4800
$Comp
L Mechanical:MountingHole H1
U 1 1 6044FDFD
P 4400 6050
F 0 "H1" H 4500 6096 50  0000 L CNN
F 1 "MountingHole" H 4500 6005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 4400 6050 50  0001 C CNN
F 3 "~" H 4400 6050 50  0001 C CNN
	1    4400 6050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60450271
P 4400 6250
F 0 "H2" H 4500 6296 50  0000 L CNN
F 1 "MountingHole" H 4500 6205 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 4400 6250 50  0001 C CNN
F 3 "~" H 4400 6250 50  0001 C CNN
	1    4400 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 6046449C
P 5200 2150
F 0 "C3" H 4950 2150 50  0000 L CNN
F 1 "100n" H 4950 2050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5238 2000 50  0001 C CNN
F 3 "" H 5200 2150 50  0001 C CNN
	1    5200 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60464A6A
P 5350 2300
F 0 "R1" V 5100 2400 50  0000 C CNN
F 1 "10k" V 5200 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5280 2300 50  0001 C CNN
F 3 "~" H 5350 2300 50  0001 C CNN
	1    5350 2300
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6046ACDF
P 5350 2500
F 0 "R2" V 5100 2600 50  0000 C CNN
F 1 "10k" V 5200 2600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5280 2500 50  0001 C CNN
F 3 "~" H 5350 2500 50  0001 C CNN
	1    5350 2500
	0    1    -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 6046B409
P 5200 2650
F 0 "C4" H 4950 2650 50  0000 L CNN
F 1 "100n" H 4950 2550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5238 2500 50  0001 C CNN
F 3 "" H 5200 2650 50  0001 C CNN
	1    5200 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6046B8AB
P 6250 2300
F 0 "R3" V 6000 2400 50  0000 C CNN
F 1 "10k" V 6100 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6180 2300 50  0001 C CNN
F 3 "~" H 6250 2300 50  0001 C CNN
	1    6250 2300
	0    -1   1    0   
$EndComp
$Comp
L Device:C C5
U 1 1 6046BF61
P 6400 2150
F 0 "C5" H 6150 2150 50  0000 L CNN
F 1 "100n" H 6150 2050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6438 2000 50  0001 C CNN
F 3 "" H 6400 2150 50  0001 C CNN
	1    6400 2150
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6046D93F
P 5200 2000
F 0 "#PWR06" H 5200 1750 50  0001 C CNN
F 1 "GND" H 5205 1827 50  0000 C CNN
F 2 "" H 5200 2000 50  0001 C CNN
F 3 "" H 5200 2000 50  0001 C CNN
	1    5200 2000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6046DD21
P 5200 2800
F 0 "#PWR08" H 5200 2550 50  0001 C CNN
F 1 "GND" H 5205 2627 50  0000 C CNN
F 2 "" H 5200 2800 50  0001 C CNN
F 3 "" H 5200 2800 50  0001 C CNN
	1    5200 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 6046E104
P 6400 2000
F 0 "#PWR09" H 6400 1750 50  0001 C CNN
F 1 "GND" H 6405 1827 50  0000 C CNN
F 2 "" H 6400 2000 50  0001 C CNN
F 3 "" H 6400 2000 50  0001 C CNN
	1    6400 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 2300 4850 2300
Connection ~ 5200 2300
Wire Wire Line
	5200 2500 4850 2500
Connection ~ 5200 2500
Wire Wire Line
	6400 2300 6750 2300
Connection ~ 6400 2300
$Comp
L power:GND #PWR0101
U 1 1 60473A3F
P 6100 2500
F 0 "#PWR0101" H 6100 2250 50  0001 C CNN
F 1 "GND" V 6105 2372 50  0000 R CNN
F 2 "" H 6100 2500 50  0001 C CNN
F 3 "" H 6100 2500 50  0001 C CNN
	1    6100 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60473F75
P 5200 2400
F 0 "#PWR0102" H 5200 2150 50  0001 C CNN
F 1 "GND" V 5205 2272 50  0000 R CNN
F 2 "" H 5200 2400 50  0001 C CNN
F 3 "" H 5200 2400 50  0001 C CNN
	1    5200 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 2400 5500 2400
$EndSCHEMATC