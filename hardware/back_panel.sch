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
Sheet 2 6
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
L CONN_02X04 P1
U 1 1 56352AC8
P 2350 1950
F 0 "P1" H 2350 2200 50  0000 C CNN
F 1 "CANCONNECTOR" H 2350 1700 50  0000 C CNN
F 2 "MITEVT_AUTOMOTIVECON:776280-1" H 2350 750 60  0001 C CNN
F 3 "" H 2350 750 60  0000 C CNN
	1    2350 1950
	1    0    0    -1  
$EndComp
$Comp
L R R201
U 1 1 563E3F11
P 2350 1100
F 0 "R201" V 2430 1100 50  0000 C CNN
F 1 "R" V 2350 1100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2280 1100 30  0001 C CNN
F 3 "" H 2350 1100 30  0000 C CNN
	1    2350 1100
	0    -1   -1   0   
$EndComp
Text HLabel 2250 1300 0    60   BiDi ~ 0
CANP
Text HLabel 3400 1800 2    60   BiDi ~ 0
CANH
Text HLabel 1300 1800 0    60   BiDi ~ 0
CANL
Wire Wire Line
	2350 1300 2350 1500
Wire Wire Line
	1800 1900 2100 1900
Wire Wire Line
	1600 2100 2100 2100
Wire Wire Line
	2600 1800 3400 1800
Wire Wire Line
	1300 1800 2100 1800
Wire Wire Line
	3100 2100 2600 2100
Wire Wire Line
	2600 2000 2900 2000
Wire Wire Line
	2600 1900 2750 1900
Wire Wire Line
	2250 1300 2350 1300
Wire Wire Line
	2900 2000 2900 2450
$Comp
L GND #PWR05
U 1 1 5647C17F
P 2900 2450
F 0 "#PWR05" H 2900 2200 50  0001 C CNN
F 1 "GND" H 2900 2300 50  0000 C CNN
F 2 "" H 2900 2450 60  0000 C CNN
F 3 "" H 2900 2450 60  0000 C CNN
	1    2900 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5647C1FB
P 1800 2450
F 0 "#PWR06" H 1800 2200 50  0001 C CNN
F 1 "GND" H 1800 2300 50  0000 C CNN
F 2 "" H 1800 2450 60  0000 C CNN
F 3 "" H 1800 2450 60  0000 C CNN
	1    1800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2450 1800 1900
Wire Wire Line
	2100 2000 1950 2000
Wire Wire Line
	1950 2000 1950 1500
Wire Wire Line
	1950 1500 2750 1500
Wire Wire Line
	2750 1500 2750 1900
Connection ~ 2350 1500
Wire Wire Line
	1600 1100 1600 2100
Wire Wire Line
	3100 1100 3100 2100
Wire Wire Line
	1600 1100 2200 1100
Wire Wire Line
	2500 1100 3100 1100
Connection ~ 3100 1800
Connection ~ 1600 1800
$Comp
L CONN_01X14 P2
U 1 1 56AD09BE
P 5050 1900
F 0 "P2" H 5050 2650 50  0000 C CNN
F 1 "CONN_01X14" V 5150 1900 50  0000 C CNN
F 2 "MITEVT_AUTOMOTIVECON:776267-1" H 5050 1900 60  0001 C CNN
F 3 "" H 5050 1900 60  0000 C CNN
	1    5050 1900
	1    0    0    -1  
$EndComp
NoConn ~ 4850 1850
NoConn ~ 4850 1950
NoConn ~ 4850 2050
NoConn ~ 4850 2150
NoConn ~ 4850 2250
NoConn ~ 4850 2350
NoConn ~ 4850 2450
NoConn ~ 4850 2550
Text HLabel 4850 1350 0    60   Output ~ 0
TPS1_5V
$Comp
L GND #PWR07
U 1 1 56B67E2A
P 4000 1450
F 0 "#PWR07" H 4000 1200 50  0001 C CNN
F 1 "GND" H 4000 1300 50  0000 C CNN
F 2 "" H 4000 1450 50  0000 C CNN
F 3 "" H 4000 1450 50  0000 C CNN
	1    4000 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 56B67E47
P 4000 1750
F 0 "#PWR08" H 4000 1500 50  0001 C CNN
F 1 "GND" H 4000 1600 50  0000 C CNN
F 2 "" H 4000 1750 50  0000 C CNN
F 3 "" H 4000 1750 50  0000 C CNN
	1    4000 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1750 4000 1750
Wire Wire Line
	4000 1450 4850 1450
$Comp
L +5V #PWR09
U 1 1 56B67EA7
P 4200 1550
F 0 "#PWR09" H 4200 1400 50  0001 C CNN
F 1 "+5V" H 4200 1690 50  0000 C CNN
F 2 "" H 4200 1550 50  0000 C CNN
F 3 "" H 4200 1550 50  0000 C CNN
	1    4200 1550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 56B67EC4
P 4200 1250
F 0 "#PWR010" H 4200 1100 50  0001 C CNN
F 1 "+5V" H 4200 1390 50  0000 C CNN
F 2 "" H 4200 1250 50  0000 C CNN
F 3 "" H 4200 1250 50  0000 C CNN
	1    4200 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1250 4200 1250
Wire Wire Line
	4200 1550 4850 1550
Text HLabel 4850 1650 0    60   Output ~ 0
TPS2_5V
$EndSCHEMATC
