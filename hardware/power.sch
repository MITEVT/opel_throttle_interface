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
LIBS:opel_throttle_interface-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L MCP1755 U5
U 1 1 55FDA4A3
P 4300 3050
F 0 "U5" H 4950 3050 60  0000 C CNN
F 1 "MCP1755" H 4700 3650 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 4300 3050 60  0001 C CNN
F 3 "" H 4300 3050 60  0000 C CNN
	1    4300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2600 4300 2600
Wire Wire Line
	4200 2600 4200 2800
Wire Wire Line
	4200 2800 4300 2800
Connection ~ 4200 2600
$Comp
L GND #PWR032
U 1 1 55FDA4E7
P 4800 3300
F 0 "#PWR032" H 4800 3050 50  0001 C CNN
F 1 "GND" H 4800 3150 50  0000 C CNN
F 2 "" H 4800 3300 60  0000 C CNN
F 3 "" H 4800 3300 60  0000 C CNN
	1    4800 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3200 4800 3300
Wire Wire Line
	5350 2600 5650 2600
NoConn ~ 5350 2800
Text HLabel 3900 2600 0    60   Input ~ 0
+12V
Text HLabel 5650 2600 2    60   Output ~ 0
+3V3
$Comp
L MCP1755 U?
U 1 1 562C4D37
P 4300 4250
F 0 "U?" H 4950 4250 60  0000 C CNN
F 1 "MCP1755" H 4700 4850 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 4300 4250 60  0001 C CNN
F 3 "" H 4300 4250 60  0000 C CNN
	1    4300 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3800 4200 4000
Wire Wire Line
	4200 4000 4300 4000
Connection ~ 4200 3800
Text HLabel 5600 3800 2    60   Output ~ 0
+5V
Wire Wire Line
	5350 3800 5600 3800
Wire Wire Line
	4000 2600 4000 3800
Connection ~ 4000 2600
Wire Wire Line
	4000 3800 4300 3800
NoConn ~ 5350 4000
$EndSCHEMATC
