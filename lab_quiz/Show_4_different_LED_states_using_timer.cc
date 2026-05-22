#include "xparameters.h"
#include "xil_types.h"
#include "xgpio.h"
#include "xstatus.h"
#include <iostream>

using namespace std;

// 2-bit LED patterns
#define PATTERN_00 0x00
#define PATTERN_01 0x01
#define PATTERN_10 0x02
#define PATTERN_11 0x03

int main()
{
    static XGpio GpioOut;
    volatile u32* Timer_Ptr = (u32*) XPAR_TMRCTR_0_BASEADDR;

    int status;

    cout << "COEN 317 Lab Quiz Application Started" << endl;

    // Step 1: Initialize GPIO output
    status = XGpio_Initialize(&GpioOut, XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID);
    if (status != XST_SUCCESS)
    {
        cout << "GPIO output initialization FAILED" << endl;
        return 1;
    }

    // Channel 1 as output
    XGpio_SetDataDirection(&GpioOut, 1, 0x0);

    // Step 2: Configure timer as up-counter
    *Timer_Ptr = 0x001;      // capture mode, up-counter
    *(Timer_Ptr + 1) = 0;    // TLR0 = 0
    *Timer_Ptr = 0x021;      // load TLR0 into TCR0
    *Timer_Ptr = 0x001;      // clear load bit
    *Timer_Ptr = 0x081;      // enable timer

    cout << "Timer started" << endl;

    // Step 3: Show 4 patterns: 00, 01, 10, 11
    // Use upper counter bits to divide time into 4 visible states
    while (1)
    {
        u32 raw_count = *(Timer_Ptr + 2);

        // Take 2 slower-changing bits from the timer
        // These decide which of the 4 states to display
        u32 state = (raw_count >> 25) & 0x3;

        u32 led_value;

        switch (state)
        {
            case 0:
                led_value = PATTERN_00;   // 00
                break;
            case 1:
                led_value = PATTERN_01;   // 01
                break;
            case 2:
                led_value = PATTERN_10;   // 10
                break;
            case 3:
                led_value = PATTERN_11;   // 11
                break;
            default:
                led_value = PATTERN_00;
                break;
        }

        XGpio_DiscreteWrite(&GpioOut, 1, led_value);
    }

    return 0;
}
