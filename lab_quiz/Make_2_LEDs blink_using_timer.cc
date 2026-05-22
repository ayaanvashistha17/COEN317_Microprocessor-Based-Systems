
#include "xparameters.h"
#include "xil_types.h"
#include "xgpio.h"
#include "xstatus.h"
#include <iostream>

using namespace std;

#define LED0 0x01
#define LED1 0x02

// 26-bit timing idea from the old quiz example
#define HALF_PERIOD_26BIT 33554432U
#define MASK_26BIT        0x03FFFFFFU

int main()
{
    static XGpio GpioOut;
    volatile u32* Timer_Ptr = (u32*) XPAR_TMRCTR_0_BASEADDR;

    int status;

    cout << "COEN 317 Lab Quiz Application Started" << endl;

    // --------------------------------------------------
    // Step 1: Initialize GPIO output
    // --------------------------------------------------
    status = XGpio_Initialize(&GpioOut, XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID);
    if (status != XST_SUCCESS)
    {
        cout << "GPIO output initialization FAILED" << endl;
        return 1;
    }

    // Channel 1 as output
    XGpio_SetDataDirection(&GpioOut, 1, 0x0);

    // --------------------------------------------------
    // Step 2: Configure timer as up-counter
    // Using direct register method from Lab 3 style
    // TCSR0 = base + 0
    // TLR0  = base + 4 bytes  -> Timer_Ptr + 1
    // TCR0  = base + 8 bytes  -> Timer_Ptr + 2
    // --------------------------------------------------

    *Timer_Ptr = 0x001;      // capture mode, up-counter
    *(Timer_Ptr + 1) = 0;    // load register = 0
    *Timer_Ptr = 0x021;      // load TLR0 into TCR0
    *Timer_Ptr = 0x001;      // clear load bit
    *Timer_Ptr = 0x081;      // enable timer

    cout << "Timer started" << endl;

    // --------------------------------------------------
    // Step 3: Blink 2 LEDs in a clean repeating pattern
    //
    // Pattern:
    // first half-cycle  -> one LED ON
    // second half-cycle -> both OFF
    // next cycle flips to the other LED
    // --------------------------------------------------
    while (1)
    {
        u32 raw_count     = *(Timer_Ptr + 2);
        u32 within_cycle  = raw_count & MASK_26BIT;
        u32 cycle_select  = (raw_count >> 26) & 0x1;

        u32 led_value = 0x00;

        if (within_cycle < HALF_PERIOD_26BIT)
        {
            if (cycle_select == 0)
                led_value = LED0;
            else
                led_value = LED1;
        }
        else
        {
            led_value = 0x00;
        }

        XGpio_DiscreteWrite(&GpioOut, 1, led_value);
    }

    return 0;
}


