

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define TEST_CCAN_BAUD_RATE 500000

#define LED_PORT 2
#define LED_PIN 10

#define BUFFER_SIZE 8
#define UART_RX_BUFFER_SIZE 8

//const uint32_t OscRateIn = 12000000;


// extern volatile uint32_t msTicks;

uint16_t tx_buffer_str[16];

CCAN_MSG_OBJ_T msg_obj;
STATIC RINGBUFF_T rx_buffer;
CCAN_MSG_OBJ_T _rx_buffer[8];
static bool can_error_flag;
static bool can_error_info;

static char str[100];
static char uart_rx_buf[UART_RX_BUFFER_SIZE];

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
	#define DEBUG_Print(str) Chip_UART_SendBlocking(LPC_USART, str, strlen(str))
	#define DEBUG_Write(str, count) Chip_UART_SendBlocking(LPC_USART, str, count)
	#define DEBUG_LED_Indicator(trigger) (trigger > 0x0200) ? LED_On() : LED_Off()
#else
	#define DEBUG_Print(str)
	#define DEBUG_Write(str, count) 
	#define DEBUG_LED_Indicator(trigger)
#endif

/*****************************************************************************
 * Private functions
 ****************************************************************************/


/*
void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg)
{
	uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
	pClk = Chip_Clock_GetMainClockRate();

	clk_per_bit = pClk / baud_rate;

	for (div = 0; div <= 15; div++) {
		for (quanta = 1; quanta <= 32; quanta++) {
			for (segs = 3; segs <= 17; segs++) {
				if (clk_per_bit == (segs * quanta * (div + 1))) {
					segs -= 3;
					seg1 = segs / 2;
					seg2 = segs - seg1;
					can_sjw = seg1 > 3 ? 3 : seg1;
					can_api_timing_cfg[0] = div;
					can_api_timing_cfg[1] =
						((quanta - 1) & 0x3F) | (can_sjw & 0x03) << 6 | (seg1 & 0x0F) << 8 | (seg2 & 0x07) << 12;
					return;
				}
			}
		}
	}
}
*/

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
    a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num) {
	// LED_On();
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;
	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if (msg_obj_num == 1) {
		RingBuffer_Insert(&rx_buffer, &msg_obj);
	}
}

/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
    a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num) {
	msg_obj_num = msg_obj_num;
}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
    an error has occurred on the CAN bus */
void CAN_error(uint32_t error_info) {
	can_error_info = error_info;
	can_error_flag = true;
}



__INLINE static void Delay(uint32_t dlyTicks) {
        uint32_t curTicks = msTicks;
        while ((msTicks - curTicks) < dlyTicks);
}

__INLINE static void GPIO_Config(void) {
        Chip_GPIO_Init(LPC_GPIO);

}

__INLINE static void LED_Config(void) {
        Chip_GPIO_WriteDirBit(LPC_GPIO, LED_PORT, LED_PIN, true);

}

__INLINE static void LED_On(void) {
        Chip_GPIO_SetPinState(LPC_GPIO, LED_PORT, LED_PIN, true);
}

__INLINE static void LED_Off(void) {
        Chip_GPIO_SetPinState(LPC_GPIO, LED_PORT, LED_PIN, false);
}

//static ADC_CLOCK_SETUP_T adc_setup;

int main(void)
{
	if (Board_SysTick_Init()) {
		while(1);
	}
	/*
	SystemCoreClockUpdate();

	if (SysTick_Config (SystemCoreClock / 1000)) {
		//Error
		while(1);
	}
	
	Board_LED_Init();
	*/
	/*
	GPIO_Config();
	LED_Config();
	*/

	Board_LEDs_Init();
	Board_ADC_Init();

	//GPIO_Config();
	//LED_Config();
	//Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_11, FUNC2);
	//Chip_ADC_Init(LPC_ADC, &adc_setup);
	//Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);
	//Chip_ADC_EnableChannel(LPC_ADC, ADC_CH1, ENABLE);
	/*
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_11, FUNC2);

    Chip_ADC_Init(LPC_ADC, &adc_setup);
    Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);
    */

    uint16_t tps_1_data = 0;
    uint16_t tps_2_data = 0;
    uint16_t tps_error = 0;
    uint16_t tps_data = 0;

	//---------------
	//UART
    Board_UART_Init(9600);
    /*
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, (IOCON_FUNC1 | IOCON_MODE_INACT)); // RXD 
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, (IOCON_FUNC1 | IOCON_MODE_INACT)); // TXD 

	Chip_UART_Init(LPC_USART);
	Chip_UART_SetBaud(LPC_USART, 9600);
	Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS));
	Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(LPC_USART);
	*/
	//---------------

	DEBUG_Print("Started up\n\r");

	//---------------
	//Ring Buffer

	RingBuffer_Init(&rx_buffer, _rx_buffer, sizeof(CCAN_MSG_OBJ_T), 8);
	RingBuffer_Flush(&rx_buffer);

	//---------------

	Board_CAN_Init(TEST_CCAN_BAUD_RATE, CAN_rx, CAN_tx, CAN_error);
	/*
	uint32_t CanApiClkInitTable[2];
	// Publish CAN Callback Functions //
	CCAN_CALLBACKS_T callbacks = {
		CAN_rx,
		CAN_tx,
		CAN_error,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	};
	CAN_baudrateCalculate(TEST_CCAN_BAUD_RATE, CanApiClkInitTable);

	LPC_CCAN_API->init_can(&CanApiClkInitTable[0], TRUE);
	// Configure the CAN callback functions //
	LPC_CCAN_API->config_calb(&callbacks);
	// Enable the CAN Interrupt //
	NVIC_EnableIRQ(CAN_IRQn);
	*/

	// typedef struct CCAN_MSG_OBJ {
	// 	uint32_t  mode_id;
	// 	uint32_t  mask;
	// 	uint8_t   data[8];
	// 	uint8_t   dlc;
	// 	uint8_t   msgobj;
	// } CCAN_MSG_OBJ_T;

	/*
	MESSAGE_NAME=TI_PACKET ID=0x800 FREQ=100HZ
    DATA_NAME=ACC_VAL POSITION=0:7
        0x00-0xFF ACC_VAL
    DATA_NAME=BRAKE_VAL POSITION=8:15
        0x00-0xFF BRAKE_VAL
    DATA_NAME=REGEN_VAL POSITION=16:23
        0x00-0xFF REGEN_VAL
     DATA_NAME=FLAGS POSITION=23:31
        0x00-0xFF FLAGS
	*/

	/* Configure message object 1 to only ID 0x800 */
	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0x301;
	msg_obj.mask = 0x7FF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	
	can_error_flag = false;
	can_error_info = 0;

	while (1) {

		Board_TPS_1_ADC_Read(&tps_1_data); // 0-5V mapped to approx. 0-920
		//Board_TPS_2_ADC_Read(&tps_2_data);
		/* Start A/D conversion */
		

		tps_data = (tps_1_data+tps_2_data)/2; // estimate of actual reading
		tps_error = (tps_1_data-tps_2_data); // if greater than 92, set error flag

		bool tps_bad_reading = abs(tps_error) > 92;
		/*
		// Start A/D conversion 
        Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

        // Waiting for A/D conversion complete 
        while (!Chip_ADC_ReadStatus(LPC_ADC, ADC_CH0, ADC_DR_DONE_STAT)) {}
        // Read ADC value 
        Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &tps_1_data);
    	*/
		itoa(tps_data,tx_buffer_str,10);
		/*
                if (tps_1_data > 0x0200) {
                        LED_On();
                } else {
                        LED_Off();
                }
        */
        DEBUG_LED_Indicator(tps_1_data);
		DEBUG_Print(tx_buffer_str);
		DEBUG_Print("\r\n");

		if (!RingBuffer_IsEmpty(&rx_buffer)) {
			CCAN_MSG_OBJ_T temp_msg;
			RingBuffer_Pop(&rx_buffer, &temp_msg);
			DEBUG_Print("Received Message ID: 0x");
			itoa(temp_msg.mode_id, str, 16);
			DEBUG_Print(str);
			DEBUG_Print("\r\n");
		}	

		if (can_error_flag) {
			can_error_flag = false;
			DEBUG_Print("CAN Error: 0b");
			itoa(can_error_info, str, 2);
			DEBUG_Print(str);
			DEBUG_Print("\r\n");
		}

		uint8_t count;
		if ((count = Chip_UART_Read(LPC_USART, uart_rx_buf, UART_RX_BUFFER_SIZE)) != 0) {
			switch (uart_rx_buf[0]) {
				case 'a':
					DEBUG_Print("Sending CAN with ID: 0x600\r\n");
					msg_obj.msgobj = 2;
					msg_obj.dlc = 1;
					msg_obj.data[0] = 0xAA;
					LPC_CCAN_API->can_transmit(&msg_obj);
					break;
				case 'p':
					DEBUG_Print("Sending CAN with ID: 0x301\r\n");
					msg_obj.msgobj = 2;
					msg_obj.mode_id = 0x301;
					msg_obj.dlc = 4;
					msg_obj.data[0] = (uint8_t) (tps_data & 0x00FF);
					msg_obj.data[1] = (uint8_t) ((tps_data)>>8);
					msg_obj.data[2] = (uint8_t) ((tps_bad_reading) ? 1 : 0);
					LPC_CCAN_API->can_transmit(&msg_obj);
					Board_UART_PrintNum(msg_obj.data[0], 10, true);
					Board_UART_PrintNum(msg_obj.data[1], 10, true);
					Board_UART_PrintNum(msg_obj.data[2], 10, true);
					break;
				default:
					DEBUG_Print("Invalid Command\r\n");
					break;
			}
		}
	}
}
