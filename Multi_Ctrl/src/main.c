/*
 * main.c
 *
 *  Created on: 2020��6��29��
 *      Author: 16117
 */

/*
 * main.c
 *
 *  Created on: 2020��6��25��
 *      Author: WongRong
 */
#include <stdio.h>

#include "xparameters.h"
#include "xuartlite.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xuartps_hw.h"
#include "UART.h"

#define Pi 3.14159265358979323846



int main(){


    init_RS232_SCREEN();
    init_RS422_Posi();

	while(1);

return 0;
}

