/*
 * UART.c
 *
 *  Created on: 2020��6��29��
 *      Author: 16117
 */


/******************************************************************************
*
* Copyright (C) 2002 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/******************************************************************************/
/**
*
* @file xuartlite_intr_example.c
*
* This file contains a design example using the UartLite driver (XUartLite) and
* hardware device using the interrupt mode.
*
* @note
*
* The user must provide a physical loopback such that data which is
* transmitted will be received.
*
* MODIFICATION HISTORY:
* <pre>
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a jhl  02/13/02 First release
* 1.00b rpm  10/01/03 Made XIntc declaration global
* 1.00b sv   06/09/05 Minor changes to comply to Doxygen and coding guidelines
* 2.00a ktn  10/20/09 Updated to use HAL Processor APIs and minor changes
*		      for coding guidelnes.
* 3.2   ms   01/23/17 Added xil_printf statement in main function to
*                     ensure that "Successfully ran" and "Failed" strings
*                     are available in all examples. This is a fix for
*                     CR-965028.
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xparameters_ps.h"
#include "xuartlite.h"
#include "xil_exception.h"
//#include "xintc.h"
#include "xuartlite_l.h"  //uartlite�����ֽں���
#include "UART.h"
#include "math.h"


/*
 * The following constant controls the length of the buffers to be sent
 * and received with the UartLite device.
 */



/************************** Variable Definitions *****************************/

/*
 * The instances to support the device drivers are global such that they
 * are initialized to zero each time the program runs.
 */
#ifndef TESTAPP_GEN
static INTC IntcInstanceUART;	/*�����ж����ñ���ʹ����ͬһ�ж� The instance of the Interrupt Controller */
static XUartLite UartLiteInstRS422;  /* The instance of the UartLite Device */
//������
static XUartLite UartLiteInstRS232;


#endif


/**Inline Function**/

static int UartLiteSetupIntrSystem(INTC *IntcInstancePtr,
				XUartLite *UartLiteInstancePtr,
				u16 UartLiteIntrId);

static void UartLiteDisableIntrSystem(INTC *IntrInstancePtr,
				u16 UartLiteIntrId);

void RS422_intr_handler(void *CallBackRef);
void RS232_intr_handler(void *CallBackRef);
/*************************************************************
 *
 * RS422��ʼ������
 *
*************************************************************/
extern int init_RS422_Posi(){
	int Status;
	//���ڳ�ʼ��
	Status = UartLiteIntrExample(&IntcInstanceUART,
				 &UartLiteInstRS422,
				 UARTLITE1_DEVICE_ID,
				 UARTLITE1_IRPT_INTR);
	if (Status != XST_SUCCESS) {
		xil_printf("RS422 interrupt tapp Example Failed\r\n");
		return XST_FAILURE;
	}

	//�жϳ�ʼ��
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	xil_printf("Successfully ran RS422 interrupt tapp Example\r\n");


	Status = UartLiteSetupIntrSystem(&IntcInstanceUART,
			&UartLiteInstRS422,
			UARTLITE1_IRPT_INTR);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;

}

/*************************************************************
 *
 * RS232���ڳ�ʼ������
 *
*************************************************************/
extern int  init_RS232_SCREEN(){

	int Status;
	//���ڳ�ʼ��
	Status = UartLiteIntrExample(&IntcInstanceUART,
				 &UartLiteInstRS232,
				 UARTLITE0_DEVICE_ID,
				 UARTLITE0_IRPT_INTR);
	if (Status != XST_SUCCESS) {
		xil_printf("RS232 interrupt tapp Example Failed\r\n");
		return XST_FAILURE;
	}

	//�жϳ�ʼ��
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	xil_printf("Successfully ran RS232 interrupt tapp Example\r\n");


	Status = UartLiteSetupIntrSystem(&IntcInstanceUART,
			&UartLiteInstRS232,
			UARTLITE0_IRPT_INTR);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}



/*********************************�жϴ�������*************************************/
void RS422_intr_handler(void *CallBackRef){

    u8 buff,buff1;
    static u8 i=0;
	xil_printf("test success\r\n");

	//����ж�λ
	//��ȡ�ж�ID�Ĵ������жϴ������������ж�
	buff=XUartLite_RecvByte(XPAR_AXI_UARTLITE_1_BASEADDR);
	buff1=buff+1;
	XUartLite_SendByte(XPAR_AXI_UARTLITE_1_BASEADDR,++i);
	XUartLite_SendByte(XPAR_AXI_UARTLITE_1_BASEADDR,buff1);
}



/**********************************�������жϴ���**********************************/
void RS232_intr_handler(void *CallBackRef){
	//����Э�����
   RS232_DATA_ILLUSTRATE();

}

/*****************************���������ݽ���************************************/
u8 RS232_DATA_ILLUSTRATE(){
	static u8 rs232_data_length=0;  //����+����+У�鳤��
    static u8 rs232_state_machine=0; //
    static u8 recv_data[20];
    u8 data_status=0;
	u8 rcvdat=XUartLite_RecvByte(XPAR_AXI_UARTLITE_0_BASEADDR);
	if(rs232_state_machine == 0)       // Э�����״̬��
	{
	      if(rcvdat == 0x5A)       // ���յ�֡ͷ��һ������
	    	  rs232_state_machine = 1;
	      else
	    	  rs232_state_machine = 0;      // ״̬����λ
	}
	else if(rs232_state_machine == 1)
	{
	      if(rcvdat == 0xA5)       // ���յ�֡ͷ�ڶ�������
	    	  rs232_state_machine = 2;
	      else
	    	  rs232_state_machine = 0;      // ״̬����λ
	}
	else if(rs232_state_machine == 2)
	{
		rs232_data_length=rcvdat;//ָ��+����+У�鳤��
	    rs232_state_machine = 3; //ֱ�ӽ�����һ�ֽ�
	}
	else if(rs232_state_machine == 3)
	{
		if((rs232_data_length)!=0){
	      if((rcvdat ==0x82)||(rcvdat ==0x83))   // �ж϶�д�ֽ��Ƿ���ȷ
	    	  rs232_state_machine = 4;
	      else
	    	  rs232_state_machine = 0;
		}
	    else{
	      	 rs232_state_machine = 0;}
	}
	else if(rs232_state_machine == 4)
	{
		//�ر��ж� 5A A5 06 83 10 41 01 00 01  recv_data[]���ռĴ�����ַ������
		recv_data[0]=rcvdat;
		UartLiteDisableIntrSystem(&IntcInstanceUART,UARTLITE0_IRPT_INTR);
		for(int i=1;i<(rs232_data_length-1);i++){
		recv_data[i]=XUartLite_RecvByte(XPAR_AXI_UARTLITE_0_BASEADDR);
		}
	/*	for(int i=0;i<(rs232_data_length-1);i++){
			XUartLite_SendByte(XPAR_AXI_UARTLITE_0_BASEADDR,recv_data[i]);
		}   */

		data_status=analy_recv(recv_data,rs232_data_length-1);//��������Ϊ��������
		if(data_status==1){ //Ϊ��ť������������
			SEND_DATD_TO_SCREEN(red_screen,7); //�����ȡ������λ����Ϣ
		}
		else if(data_status==2){  //����λ�˲���
			ANALY_PS(recv_data);
		}
		//������һ��������ǰ���жϣ����½�����һ������
		UartLiteSetupIntrSystem(&IntcInstanceUART,
					&UartLiteInstRS232,
					UARTLITE0_IRPT_INTR);
		rs232_state_machine = 0;
	}

	return data_status;
}

u8 analy_recv(u8 *recv_data,u8 num)
{

    return MATH_FLAG;
}



/****************************************************************************/
/**
*
* This function does a minimal test on the UartLite device and driver as a
* design example. The purpose of this function is to illustrate how to use
* the XUartLite component.
*
* This function sends data through the UartLite.
*
* This function uses the interrupt driver mode of the UartLite.  The calls to
* the  UartLite driver in the interrupt handlers, should only use the
* non-blocking calls.
*
* @param	IntcInstancePtr is a pointer to the instance of INTC driver.
* @param	UartLiteInstPtr is a pointer to the instance of UartLite driver.
* @param	UartLiteDeviceId is the Device ID of the UartLite Device and
*		is the XPAR_<UARTLITE_instance>_DEVICE_ID value from
*		xparameters.h.
* @param	UartLiteIntrId is the Interrupt ID and is typically
*		XPAR_<INTC_instance>_<UARTLITE_instance>_VEC_ID value from
*		xparameters.h.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
* This function contains an infinite loop such that if interrupts are not
* working it may never return.
*
****************************************************************************/
int UartLiteIntrExample(INTC *IntcInstancePtr,
			XUartLite *UartLiteInstPtr,
			u16 UartLiteDeviceId,
			u16 UartLiteIntrId)
{
	int Status;
	/*
	 * Initialize the UartLite driver so that it's ready to use.
	 */
	Status = XUartLite_Initialize(UartLiteInstPtr, UartLiteDeviceId);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(UartLiteInstPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

/*2020.07.01	while ((TotalSentCount != TEST_BUFFER_SIZE)) {
	}

	UartLiteDisableIntrSystem(IntcInstancePtr, UartLiteIntrId);  */

	return XST_SUCCESS;
}



/****************************************************************************/
/**
*
* This function setups the interrupt system such that interrupts can occur
* for the UartLite. This function is application specific since the actual
* system may or may not have an interrupt controller. The UartLite could be
* directly connected to a processor without an interrupt controller. The
* user should modify this function to fit the application.
*
* @param	IntcInstancePtr is a pointer to the instance of INTC driver.
* @param	UartLiteInstPtr is a pointer to the instance of UartLite driver.
*		XPAR_<UARTLITE_instance>_DEVICE_ID value from xparameters.h.
* @param	UartLiteIntrId is the Interrupt ID and is typically
*		XPAR_<INTC_instance>_<UARTLITE_instance>_VEC_ID
*		value from xparameters.h.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*�жϳ�ʼ��
****************************************************************************/
int UartLiteSetupIntrSystem(INTC *IntcInstancePtr,
				XUartLite *UartLiteInstPtr,
				u16 UartLiteIntrId)
{
	int Status;

#ifdef XPAR_INTC_0_DEVICE_ID

#ifndef TESTAPP_GEN
	/*
	 * Initialize the interrupt controller driver so that it is ready
	 * to use. ��ʼ���жϿ�����
	 */
	Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif

	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the specific
	 * interrupt processing for the device.
	 */
	Status = XIntc_Connect(IntcInstancePtr, UartLiteIntrId,
			(XInterruptHandler)XUartLite_InterruptHandler,
			(void *)UartLiteInstPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

#ifndef TESTAPP_GEN
	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specific real mode so that
	 * the UART can cause interrupts thru the interrupt controller.
	 */
	Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif

	/*
	 * Enable the interrupt for the UartLite.
	 */
	XIntc_Enable(IntcInstancePtr, UartLiteIntrId);
#else

#ifndef TESTAPP_GEN
	XScuGic_Config *IntcConfig;

	/*��ʼ���жϿ�����
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
#endif /* TESTAPP_GEN */
//Sets the interrupt priority and trigger type for the specificd IRQ source.
//2020.7.2	XScuGic_SetPriorityTriggerType(IntcInstancePtr, UartLiteIntrId,
//					0xA0, 0x3);
	switch(UartLiteIntrId){
	case 62U:
		XScuGic_SetPriorityTriggerType(IntcInstancePtr, UartLiteIntrId,
						0xA0, 0x3); break;
	case 61U:
		XScuGic_SetPriorityTriggerType(IntcInstancePtr, UartLiteIntrId,
						0xA1, 0x3);  break;
	default:
		XScuGic_SetPriorityTriggerType(IntcInstancePtr, UartLiteIntrId,
						0xA0, 0x3); break; break;
	}
#endif /* XPAR_INTC_0_DEVICE_ID */


#ifndef TESTAPP_GEN
   //���ò����ж��쳣��������
	/*
	 * Initialize the exception table. ��ʼ���쳣��
	 */
	Xil_ExceptionInit();

	/*ע���жϿ�������������
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler)INTC_HANDLER,
			IntcInstancePtr);

	/*
	 * Enable exceptions.
	 */
	Xil_ExceptionEnable();
/**************************2020.7.1******************/
	/*
	 * Connect the interrupt handler that will be called when an
	 * interrupt occurs for the device.
	 */
	//Ϊ�ж������жϴ�������XUartLite_InterruptHandler
	switch(UartLiteIntrId){
	case 62U:
	Status = XScuGic_Connect(IntcInstancePtr, UartLiteIntrId,
				 (Xil_ExceptionHandler)RS232_intr_handler,/*XUartLite_InterruptHandler,*/
				 UartLiteInstPtr);  break;
	case 61U:
		Status = XScuGic_Connect(IntcInstancePtr, UartLiteIntrId,
					 (Xil_ExceptionHandler)RS422_intr_handler,/*XUartLite_InterruptHandler,*/
					 UartLiteInstPtr);  break;
	default:
	Status = XScuGic_Connect(IntcInstancePtr, UartLiteIntrId,
				 (Xil_ExceptionHandler)RS422_intr_handler,/*XUartLite_InterruptHandler,*/
				 UartLiteInstPtr);  break;
	}
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Enable the interrupt for the Timer device.
	 */
	//ʹ��GIC�еĴ����ж�
	XScuGic_Enable(IntcInstancePtr, UartLiteIntrId);

	/*
	 * Enable the interrupt of the UartLite so that the interrupts
	 * will occur.
	 */
	XUartLite_EnableInterrupt(UartLiteInstPtr);

#endif /* TESTAPP_GEN */

	return XST_SUCCESS;
}


/*****************************************************************************/
/**
*
* This function disables the interrupts that occur for the UartLite.
*
* @param	IntcInstancePtr is a pointer to the instance of the INTC driver.
* @param	UartLiteIntrId is the Interrupt ID and is typically
*		XPAR_<INTC_instance>_<UARTLITE_instance>_VEC_ID
*		value from xparameters.h.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void UartLiteDisableIntrSystem(INTC *IntcInstancePtr,
					  u16 UartLiteIntrId)
{
	/*
	 * Disconnect and disable the interrupt for the UartLite.
	 */
#ifdef XPAR_INTC_0_DEVICE_ID
	XIntc_Disconnect(IntcInstancePtr, UartLiteIntrId);
#else
	XScuGic_Disable(IntcInstancePtr, UartLiteIntrId);
	XScuGic_Disconnect(IntcInstancePtr, UartLiteIntrId);

#endif

}

