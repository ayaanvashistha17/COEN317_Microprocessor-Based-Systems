#include "xparameters.h"
#include "xil_types.h"
#include "xgpio.h"
#include "xstatus.h"
#include <iostream>

using namespace std;

int main()
{
    static XGpio GpioIn;
    static XGpio GpioOut;
    int status;
    u32 switch_value;

    cout << "COEN 317 Lab Quiz Started" << endl;

    // Initialize input GPIO
    status = XGpio_Initialize(&GpioIn, XPAR_AXI_GPIO_FOR_INPUT_DEVICE_ID);
    if (status != XST_SUCCESS)
    {
        cout << "Input GPIO initialization FAILED" << endl;
        return 1;
    }

    // 2-bit input: switches
    XGpio_SetDataDirection(&GpioIn, 1, 0x3);

    // Initialize output GPIO
    status = XGpio_Initialize(&GpioOut, XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID);
    if (status != XST_SUCCESS)
    {
        cout << "Output GPIO initialization FAILED" << endl;
        return 1;
    }

    // output LEDs
    XGpio_SetDataDirection(&GpioOut, 1, 0x0);

    cout << "System running. Toggle the 2 switches." << endl;

    while (1)
    {
        switch_value = XGpio_DiscreteRead(&GpioIn, 1) & 0x3;
        XGpio_DiscreteWrite(&GpioOut, 1, switch_value);
    }

    return 0;
}
