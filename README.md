# zynq_two_uartlite
Zynq7020 two uartlite interrupt test, PS side source code.

源代码基于启明星开发板
启明星：
SD0 MIO40-MIO45 CD:MIO10
UART0 E0000000 MIO14-MIO15

两个uartlite配置
RS232：axi_uartlite_0    RX IO_B35_LP10    :G14	 TX   IO_B35_LN10	:A20
RS422:   axi_uartlite_1    RX IO_B35_LP6      :F16	 TX   IO_B35_LN6      :F17

源代码说明见网址：
https://blog.csdn.net/qq_17169835/article/details/107098355?spm=1001.2014.3001.5502
