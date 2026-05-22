#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"
#include <iostream>

using namespace std;

int main()
{
    volatile u32* Timer_Ptr = (u32*) XPAR_TMRCTR_0_BASEADDR;
    u32 capture_value = 0;
    u32 new_capture_value = 0;

    cout << "==== COEN 317 Lab 3 Part 2: Capture Mode ====" << endl;
    cout << "Press SW5 once to capture the first value..." << endl;

    // Put timer in capture mode with overwrite enabled
    // Manual hint: write 0x19 to TCSR
    *Timer_Ptr = 0x19;

    // Load register = 0
    *(Timer_Ptr + 1) = 0;

    // Transfer TLR0 -> TCR0 using load bit
    *Timer_Ptr = 0x39;   // 0x19 + load bit
    *Timer_Ptr = 0x19;   // clear load bit

    // Start timer
    *Timer_Ptr = 0x99;   // 0x19 + enable bit

    // Wait for first capture into load register
    while (*(Timer_Ptr + 1) == 0)
    {
        // wait
    }

    capture_value = *(Timer_Ptr + 1);
    cout << "First capture value  = " << capture_value << endl;
    cout << "Now press SW5 again for second capture..." << endl;

    while (*(Timer_Ptr + 1) == capture_value)
    {
        // wait
    }

    new_capture_value = *(Timer_Ptr + 1);

    cout << "Second capture value = " << new_capture_value << endl;
    cout << "Difference           = " << (new_capture_value - capture_value)
         << " clock cycles" << endl;

    return 0;
}
