#include "xparameters.h"
#include "xil_types.h"
#include "xgpio.h"
#include "xil_io.h"
#include <iostream>

using namespace std;

int main()
{
    static XGpio GPIOInstance_Ptr;
    volatile u32* Timer_Ptr = (u32*) XPAR_TMRCTR_0_BASEADDR;
    volatile u32* GPIO_Data_Ptr = (u32*) XPAR_AXI_GPIO_FOR_OUTPUT_BASEADDR;

    int xStatus;
    u32 count_function = 0;
    u32 count_pointer  = 0;
    u32 overhead       = 0;

    cout << "==== COEN 317 Lab 3 Part 1: Timer + GPIO ====" << endl;

    // Step 1: GPIO init
    xStatus = XGpio_Initialize(&GPIOInstance_Ptr, XPAR_AXI_GPIO_FOR_OUTPUT_DEVICE_ID);
    if (xStatus != XST_SUCCESS)
    {
        cout << "GPIO initialization FAILED" << endl;
        return 1;
    }

    // Step 2: GPIO direction
    // Channel 1, 0 means output
    XGpio_SetDataDirection(&GPIOInstance_Ptr, 1, 0);

    // --------------------------------------------------
    // Measure overhead of starting/stopping timer itself
    // --------------------------------------------------
    *Timer_Ptr = 0x001;     // capture/generate mode baseline
    *(Timer_Ptr + 1) = 0;   // TLR0 = 0
    *Timer_Ptr = 0x021;     // load TLR0 into TCR0
    *Timer_Ptr = 0x001;     // clear load bit
    *Timer_Ptr = 0x081;     // start timer
    *Timer_Ptr = 0x001;     // stop timer
    overhead = *(Timer_Ptr + 2);

    cout << "Timer start/stop overhead = " << overhead << " clock cycles" << endl;

    // --------------------------------------------------
    // Measure XGpio_DiscreteWrite()
    // --------------------------------------------------
    *Timer_Ptr = 0x001;
    *(Timer_Ptr + 1) = 0;
    *Timer_Ptr = 0x021;
    *Timer_Ptr = 0x001;
    *Timer_Ptr = 0x081;

    XGpio_DiscreteWrite(&GPIOInstance_Ptr, 1, 0xA3);

    *Timer_Ptr = 0x001;
    count_function = *(Timer_Ptr + 2);

    cout << "XGpio_DiscreteWrite() time = " << count_function
         << " clock cycles" << endl;

    // --------------------------------------------------
    // Measure direct pointer write to GPIO data register
    // --------------------------------------------------
    *Timer_Ptr = 0x001;
    *(Timer_Ptr + 1) = 0;
    *Timer_Ptr = 0x021;
    *Timer_Ptr = 0x001;
    *Timer_Ptr = 0x081;

    *GPIO_Data_Ptr = 0x3C;

    *Timer_Ptr = 0x001;
    count_pointer = *(Timer_Ptr + 2);

    cout << "Direct pointer GPIO write time = " << count_pointer
         << " clock cycles" << endl;

    cout << "Approx. function-only cost  = "
         << (count_function > overhead ? count_function - overhead : 0)
         << " clock cycles" << endl;

    cout << "Approx. pointer-only cost   = "
         << (count_pointer > overhead ? count_pointer - overhead : 0)
         << " clock cycles" << endl;

    if (count_function > count_pointer)
        cout << "Conclusion: direct pointer write is faster." << endl;
    else if (count_function < count_pointer)
        cout << "Conclusion: Xilinx function write is faster." << endl;
    else
        cout << "Conclusion: both measured the same in this run." << endl;

    return 0;
}
