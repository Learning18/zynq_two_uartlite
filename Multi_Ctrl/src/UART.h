/*
 * UART.h
 *
 *  Created on: 2020年6月29日
 *      Author: 16117
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_


#ifdef XPAR_INTC_0_DEVICE_ID
#include "xintc.h"
#include <stdio.h>
#else
#include "xscugic.h"
#include "xil_printf.h"
#endif

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ifndef TESTAPP_GEN
//UARTLITE设备号
#define UARTLITE0_DEVICE_ID	  XPAR_UARTLITE_0_DEVICE_ID   //RS232
#define UARTLITE1_DEVICE_ID    XPAR_UARTLITE_1_DEVICE_ID  //RS422
//UARTLITE中断号
#define UARTLITE0_IRPT_INTR	 XPAR_FABRIC_UARTLITE_0_VEC_ID
#define UARTLITE1_IRPT_INTR	 XPAR_FABRIC_UARTLITE_1_VEC_ID

#ifdef XPAR_INTC_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID
#else
//GIC中断控制器ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#endif /* XPAR_INTC_0_DEVICE_ID */
#endif /* TESTAPP_GEN */

/*
 * The following constant controls the length of the buffers to be sent
 * and received with the UartLite device.
 */
#define TEST_BUFFER_SIZE		10

#define Pi 3.14159265358979323846
/**************************** Type Definitions *******************************/

#ifdef XPAR_INTC_0_DEVICE_ID
#define INTC		XIntc
#define INTC_HANDLER	XIntc_InterruptHandler
#else

#define INTC		XScuGic
#define INTC_HANDLER	XScuGic_InterruptHandler
#endif /* XPAR_INTC_0_DEVICE_ID */


	//调试串口
	#define UART_1_DEVICE_ID    0xE0000000 //UART1
	//RS232串口屏及RS422 UART地址
	#define UART_SCREEN_BASEADDR	XPAR_UARTLITE_0_BASEADDR
	#define UART_RS422_BASEADDR	   	XPAR_UARTLITE_1_BASEADDR

/************************** Constant Definitions *****************************/
/*串口屏数据参数设置*/
//u8 rs232_data_length; //
//u8 rs232_data_data[];
//u8 send_screen_length; //

//u8 rs422_data_length;
/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
extern int  init_RS232_SCREEN();
extern int  init_RS422_Posi();
int UartLiteIntrExample(INTC *IntcInstancePtr,
			XUartLite *UartLiteInstancePtr,
			u16 UartLiteDeviceId,
			u16 UartLiteIntrId);
int RS422_DATA_ILLUSTRATE();
u8 RS232_DATA_ILLUSTRATE();
u8 analy_recv(u8 *recv_data,u8 num);
u8 SEND_DATD_TO_SCREEN(u8 *DATA,u8 Length);
u8 SEND_LEG(double *LEG_LENGTH);
u8 ANALY_PS(u8 *recv_data);
#endif /* SRC_UART_H_ */
