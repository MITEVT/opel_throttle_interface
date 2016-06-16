#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define TEST_CCAN_BAUD_RATE 500000

#define LED_PORT 2
#define LED_PIN 5

#define BUFFER_SIZE 8
#define UART_RX_BUFFER_SIZE 8


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

//	Board_LEDs_Init();
	GPIO_Config();
	LED_Config();
//	LED_On();
	Board_ADC_Init();

    	uint16_t tps_1_data = 0;
    	uint16_t tps_2_data = 0;
    	int16_t tps_error = 0;
    	uint16_t tps_data = 0;

	//---------------
	//UART
    	Board_UART_Init(9600);

	//---------------
	
	DEBUG_Print("Started up\n\r");

	//---------------
	//Ring Buffer

	RingBuffer_Init(&rx_buffer, _rx_buffer, sizeof(CCAN_MSG_OBJ_T), 8);
	RingBuffer_Flush(&rx_buffer);

	//---------------

	Board_CAN_Init(TEST_CCAN_BAUD_RATE, CAN_rx, CAN_tx, CAN_error);
	
	/*
	MESSAGE_NAME=TI_PACKET ID=0x301 FREQ=100HZ
    DATA_NAME=ACC_VAL POSITION=0:7
        0x00-0xFF ACC_VAL
    DATA_NAME=BRAKE_VAL POSITION=8:15
        0x00-0xFF BRAKE_VAL
    DATA_NAME=FLAGS POSITION=16:23
        0x00-0xFF FLAGS
	*/

	/* Configure message object 1 to only ID 0x301 */
	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0x301;
	msg_obj.mask = 0x7FF;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	
	can_error_flag = false;
	can_error_info = 0;
	
	bool send = false;

	while (1) {

		Board_TPS_1_ADC_Read(&tps_1_data); // 0-5V mapped to approx. 0-920
		Board_TPS_2_ADC_Read(&tps_2_data);		

		tps_data = (tps_1_data+tps_2_data)/2; // estimate of actual reading
		tps_error = (tps_1_data-tps_2_data); // if greater than 92, set error flag

		bool tps_bad_reading = abs(tps_error) > 92;
		
		if (tps_bad_reading) {
			LED_On();
		}
//		itoa(tps_1_data,tx_buffer_str,10);
//		DEBUG_Print(tx_buffer_str);
//		DEBUG_Print("\r\n");
//		itoa(tps_2_data,tx_buffer_str,10);
//		DEBUG_Print(tx_buffer_str);
//		DEBUG_Print("\r\n");

//		DEBUG_LED_Indicator(tps_error);
//		itoa(tps_data,tx_buffer_str,10);
//		DEBUG_Print("TPS_DATA:");
//		DEBUG_Print(tx_buffer_str);
//		DEBUG_Print("\t");
//		DEBUG_Print("TPS_ERROR:");
//		itoa(abs(tps_error),tx_buffer_str,10);
//		DEBUG_Print(tx_buffer_str);
//		DEBUG_Print("\r\n");

		if (send) {
			DEBUG_Print("Sending CAN with ID: 0x301\r\n");
			msg_obj.msgobj = 2;
			msg_obj.mode_id = 0x301;
			msg_obj.dlc = 4;
			msg_obj.data[0] =  (uint8_t) (tps_data & 0x00FF);  
			msg_obj.data[1] = (uint8_t) ((tps_data)>>8); //divide by 2^8
			msg_obj.data[2] = (uint8_t) ((tps_bad_reading) ? 1 : 0);
			LPC_CCAN_API->can_transmit(&msg_obj);
			Board_UART_PrintNum(msg_obj.data[0], 10, true);
			Board_UART_PrintNum(msg_obj.data[1], 10, true);
			Board_UART_PrintNum(msg_obj.data[2], 10, true);		
		}

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
					DEBUG_Print("Sending CAN with ID: 0x301\r\n");
					msg_obj.msgobj = 2;
					msg_obj.mode_id = 0x301;
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
					msg_obj.data[1] = (uint8_t) ((tps_data)>>8); //divide by 2^8
					msg_obj.data[2] = (uint8_t) ((tps_bad_reading) ? 1 : 0);
					LPC_CCAN_API->can_transmit(&msg_obj);
					Board_UART_PrintNum(msg_obj.data[0], 10, true);
					Board_UART_PrintNum(msg_obj.data[1], 10, true);
					Board_UART_PrintNum(msg_obj.data[2], 10, true);
					break;
				case 'c':
					DEBUG_Print("Sending CAN with ID: 0x301\r\n");
					msg_obj.msgobj = 2;
					msg_obj.mode_id = 0x301;
					msg_obj.dlc = 3;
					msg_obj.data[0] = 0x05;
					msg_obj.data[1] = 0x00;
					msg_obj.data[2] = 0x00;
					LPC_CCAN_API->can_transmit(&msg_obj);
					Board_UART_PrintNum(msg_obj.data[0],10,true);
					Board_UART_PrintNum(msg_obj.data[1],10,true);
					Board_UART_PrintNum(msg_obj.data[2],10,true);
					break;
				case 'b':
					DEBUG_Print("Sending CAN with ID: 0x301\r\n");
					msg_obj.msgobj = 2;
					msg_obj.mode_id = 0x301;
					msg_obj.dlc = 3;
					msg_obj.data[0] = 0x00;
					msg_obj.data[1] = 0x05;
					msg_obj.data[2] = 0x00;
					LPC_CCAN_API->can_transmit(&msg_obj);
					Board_UART_PrintNum(msg_obj.data[0],10,true);
					Board_UART_PrintNum(msg_obj.data[1],10,true);
					Board_UART_PrintNum(msg_obj.data[2],10,true);
					break;
				case 'e':
					DEBUG_Print("Sending CAN with ID: 0x301\r\n");
					msg_obj.msgobj = 2;
					msg_obj.mode_id = 0x301;
					msg_obj.dlc = 3;
					msg_obj.data[0] = 0x04;
					msg_obj.data[1] = 0x10;
					msg_obj.data[2] = 0x01;
					LPC_CCAN_API->can_transmit(&msg_obj);
					Board_UART_PrintNum(msg_obj.data[0],10,true);
					Board_UART_PrintNum(msg_obj.data[1],10,true);
					Board_UART_PrintNum(msg_obj.data[2],10,true);
					break;
				case 't':
					send = true;
					break;
				case 'f':
					send = false;
				default:
					DEBUG_Print("Invalid Command\r\n");
					break;
			}
		}
	}
}
