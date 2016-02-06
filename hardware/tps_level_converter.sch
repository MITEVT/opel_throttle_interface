EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:MITEVT_ANALOG
LIBS:MITEVT_CONTACTORS
LIBS:MITEVT_interface
LIBS:MITEVT_mcontrollers
LIBS:MITEVT_OPTO
LIBS:MITEVT_power
LIBS:MITEVT_REG
LIBS:final_outline-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
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
L R R2
U 1 1 569A93CF
P 5000 3050
F 0 "R2" V 5080 3050 50  0000 C CNN
F 1 "33k" V 5000 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4930 3050 30  0001 C CNN
F 3 "" H 5000 3050 30  0000 C CNN
	1    5000 3050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 569A93F4
P 5000 3650
F 0 "R3" V 5080 3650 50  0000 C CNN
F 1 "47k" V 5000 3650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4930 3650 30  0001 C CNN
F 3 "" H 5000 3650 30  0000 C CNN
	1    5000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3200 5000 3500
Wire Wire Line
	5000 2700 5000 2900
Wire Wire Line
	5000 3800 5000 4000
Wire Wire Line
	5000 3350 5500 3350
Connection ~ 5000 3350
$Comp
L GND #PWR032
U 1 1 569A9471
P 5000 4000
F 0 "#PWR032" H 5000 3750 50  0001 C CNN
F 1 "GND" H 5000 3850 50  0000 C CNN
F 2 "" H 5000 4000 60  0000 C CNN
F 3 "" H 5000 4000 60  0000 C CNN
	1    5000 4000
	1    0    0    -1  
$EndComp
Text HLabel 5500 3350 2    60   Output ~ 0
TPS1_3.3V
Text HLabel 2600 2600 0    60   Input ~ 0
TPS1_5V
$Comp
L R R4
U 1 1 569AA60A
P 5000 5150
F 0 "R4" V 5080 5150 50  0000 C CNN
F 1 "33k" V 5000 5150 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4930 5150 30  0001 C CNN
F 3 "" H 5000 5150 30  0000 C CNN
	1    5000 5150
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 569AA610
P 5000 5750
F 0 "R5" V 5080 5750 50  0000 C CNN
F 1 "47k" V 5000 5750 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4930 5750 30  0001 C CNN
F 3 "" H 5000 5750 30  0000 C CNN
	1    5000 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5300 5000 5600
Wire Wire Line
	5000 4800 5000 5000
Wire Wire Line
	5000 5900 5000 6100
Wire Wire Line
	5000 5450 5500 5450
Connection ~ 5000 5450
$Comp
L GND #PWR033
U 1 1 569AA61B
P 5000 6100
F 0 "#PWR033" H 5000 5850 50  0001 C CNN
F 1 "GND" H 5000 5950 50  0000 C CNN
F 2 "" H 5000 6100 60  0000 C CNN
F 3 "" H 5000 6100 60  0000 C CNN
	1    5000 6100
	1    0    0    -1  
$EndComp
Text HLabel 5500 5450 2    60   Output ~ 0
TPS2_3.3V
Text HLabel 2600 4700 0    60   Input ~ 0
TPS2_5V
$Comp
L LM358N U1
U 1 1 569AA864
P 3800 2700
F 0 "U1" H 3750 2900 60  0000 L CNN
F 1 "LM358N" H 3750 2450 60  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3800 2700 60  0001 C CNN
F 3 "" H 3800 2700 60  0000 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
$Comp
L LM358N U1
U 2 1 569AA8AA
P 3800 4800
F 0 "U1" H 3750 5000 60  0000 L CNN
F 1 "LM358N" H 3750 4550 60  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3800 4800 60  0001 C CNN
F 3 "" H 3800 4800 60  0000 C CNN
	2    3800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2700 4300 3400
Wire Wire Line
	4300 3400 3300 3400
Wire Wire Line
	3300 3400 3300 2800
Wire Wire Line
	4300 4800 4300 5600
Wire Wire Line
	4300 5600 3300 5600
Wire Wire Line
	3300 5600 3300 4900
Wire Wire Line
	2600 4700 3500 4700
Wire Wire Line
	4100 2700 5000 2700
Wire Wire Line
	4100 4800 5000 4800
Wire Wire Line
	3700 3000 3700 3200
$Comp
L GND #PWR034
U 1 1 569AAACB
P 3700 3200
F 0 "#PWR034" H 3700 2950 50  0001 C CNN
F 1 "GND" H 3700 3050 50  0000 C CNN
F 2 "" H 3700 3200 60  0000 C CNN
F 3 "" H 3700 3200 60  0000 C CNN
	1    3700 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 569AAAF1
P 3700 5350
F 0 "#PWR035" H 3700 5100 50  0001 C CNN
F 1 "GND" H 3700 5200 50  0000 C CNN
F 2 "" H 3700 5350 60  0000 C CNN
F 3 "" H 3700 5350 60  0000 C CNN
	1    3700 5350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR036
U 1 1 569AAB4F
P 3700 2200
F 0 "#PWR036" H 3700 2050 50  0001 C CNN
F 1 "+5V" H 3700 2340 50  0000 C CNN
F 2 "" H 3700 2200 60  0000 C CNN
F 3 "" H 3700 2200 60  0000 C CNN
	1    3700 2200
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR037
U 1 1 569AAB75
P 3700 4300
F 0 "#PWR037" H 3700 4150 50  0001 C CNN
F 1 "+5V" H 3700 4440 50  0000 C CNN
F 2 "" H 3700 4300 60  0000 C CNN
F 3 "" H 3700 4300 60  0000 C CNN
	1    3700 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2200 3700 2400
Wire Wire Line
	3700 4300 3700 4500
Wire Wire Line
	3700 5100 3700 5350
Connection ~ 4300 2700
Connection ~ 4300 4800
Wire Wire Line
	2600 2600 3500 2600
Wire Wire Line
	3300 2800 3500 2800
Wire Wire Line
	3300 4900 3500 4900
$EndSCHEMATC
