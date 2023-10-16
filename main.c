#include <stdio.h>
#include "xil_io.h"
#include "xil_printf.h"
#include "xparameters.h"
#include <unistd.h> // Libreria necesaria para sleep

// Añadir para utilizar GPIO
#include "xgpio.h"

int main()
{

	// Valores PWM
    int volatile comparador_1 = 0x0001E848 - 0xC350; // 125000 - 50000 = 75000
    int volatile comparador_2 = 0x0001E848 - 0x15F90; // 125000 - 90000 = 35000
    int volatile comparador_3 = 0x0001E848 - 0x1D4C0; // 125000 - 120000 = 5000
    int volatile comparador_4 = 0x0001E848 - 0x0001E848; // 125000 - 125000 = 0
    int sw;
    int temp;

    XGpio GPIO;

    XGpio_Initialize(&GPIO, XPAR_AXI_GPIO_0_BASEADDR);

    // Notar Adress de el IPCore creado con AXI
    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR,comparador_1);
    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR+4,comparador_2);
    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR+8,comparador_3);
    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR+12,comparador_4);


    while(1){

    	//sw = XGpio_DiscreteRead(&GPIO, 1);

    	sw = Xil_In32(XPAR_AXI_GPIO_0_BASEADDR);


    	//* Write a value to a GPIO register. A 32 bit write is performed. If the
    	//* GPIO core is implemented in a smaller width, only the least significant data
    	//* is written.


    	//XGpio_DiscreteWrite(&GPIO, 2, sw);
    	Xil_Out32(XPAR_AXI_GPIO_0_BASEADDR + 8, sw);
    	temp = comparador_1;
		comparador_1 = comparador_2;
		comparador_2 = comparador_3;
		comparador_3 = comparador_4;
		comparador_4 = temp;
	    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR,comparador_1);
	    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR+4,comparador_2);
	    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR+8,comparador_3);
	    Xil_Out32(XPAR_LED_DRIVER_0_S00_AXI_BASEADDR+12,comparador_4);

        usleep(1000000/10);
    }

// Cierra main
    return 0;
}
