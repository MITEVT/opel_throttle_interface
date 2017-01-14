#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define TEST_CCAN_BAUD_RATE 500000

#define BUFFER_SIZE 8
#define UART_RX_BUFFER_SIZE 8

// ---------------------------------------------------------
// Static Variableb Declaration

extern volatile uint32_t msTicks;

static uint32_t lastMsg;

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
#else
	#define DEBUG_Print(str)
	#define DEBUG_Write(str, count)
#endif

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
    a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num) {
	/* Determine which CAN message has been received */
	msg_obj.msgobj = msg_obj_num;
	/* Now load up the msg_obj structure with the CAN message */
	LPC_CCAN_API->can_receive(&msg_obj);
	if (msg_obj_num==1) {
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

int main(void) {
	if (Board_SysTick_Init()) {
		while(1);
	}

	Board_LEDs_Init();
	Board_LED_On(LED0);
	Board_ADC_Init();
	lastMsg = msTicks;

	uint16_t tps_data = 0;
	int16_t tps_error = 0;

	Board_UART_Init(9600);

	DEBUG_Print("Started up\n\r");

	RingBuffer_Init(&rx_buffer, _rx_buffer, sizeof(CCAN_MSG_OBJ_T), 8);
	RingBuffer_Flush(&rx_buffer);

	Board_CAN_Init(TEST_CCAN_BAUD_RATE, CAN_rx, CAN_tx, CAN_error);

	msg_obj.msgobj = 1;
	msg_obj.mode_id = 0x301;
	msg_obj.mask = 0x000;
	LPC_CCAN_API->config_rxmsgobj(&msg_obj);

	can_error_flag = false;
	can_error_info = 0;
	
	bool send = false;
	while (1) {
		
		Board_TPS_ADC_Read(&tps_data);		
	
//		itoa(tps_data,tx_buffer_str,10);
//		DEBUG_Print("TPS_DATA:");
//		DEBUG_Print(tx_buffer_str);
//		DEBUG_Print("\r\n");

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
		
		if (send && lastMsg < msTicks-10) {
			lastMsg = msTicks;
			DEBUG_Print("Sending CAN with ID: 0x301\r\n");
			msg_obj.msgobj = 2;
			msg_obj.mode_id = 0x301;
			msg_obj.dlc = 4;
			msg_obj.data[0] = tps_data>>2;
			msg_obj.data[1] = (uint8_t) 0x00;
			msg_obj.data[2] = (uint8_t) tps_error;
			LPC_CCAN_API->can_transmit(&msg_obj);
			Board_UART_PrintNum(msg_obj.data[0],10,true);
			Board_UART_PrintNum(msg_obj.data[1],10,true);
			Board_UART_PrintNum(msg_obj.data[2],10,true);
		}

		uint8_t count;
		count = Chip_UART_Read(LPC_USART, uart_rx_buf, UART_RX_BUFFER_SIZE);
		if (count != 0) {
			switch (uart_rx_buf[0]) {
				case 'a':
					send = true;
					break;
				case 'z':
					send = false;
					break;
				case 'r':
					DEBUG_Print("Sending CAN with ID: 0x301\r\n");
					msg_obj.msgobj = 2;
					msg_obj.mode_id = 0x301;
					msg_obj.dlc = 2;
					msg_obj.data[0] = tps_data;
					msg_obj.data[1] = tps_error;
					LPC_CCAN_API->can_transmit(&msg_obj);
					Board_UART_PrintNum(msg_obj.data[0],10,true);
					Board_UART_PrintNum(msg_obj.data[1],10,true);
					break;
				
				default:
					DEBUG_Print("Invalid Command\r\n");
					break;
			}
		}
	}
}


