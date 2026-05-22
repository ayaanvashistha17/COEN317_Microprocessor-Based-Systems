#include "xparameters.h"
#include "xil_types.h"
#include <iostream>

using namespace std;

int main()
{
    u32* Timer_Ptr = (u32*) XPAR_TMRCTR_0_BASEADDR;
    u32 capture_value;
    u32 new_capture_value;
    u32 delay_start;

    cout << "Part 2: Capture Mode with Debounce" << endl;
    cout << "Press SW5 for first capture..." << endl;

    Timer_Ptr[0] = 0x19;
    Timer_Ptr[1] = 0;

    Timer_Ptr[0] |= (1 << 5);
    Timer_Ptr[0] &= ~(1 << 5);
    Timer_Ptr[0] |= (1 << 7);

    while (Timer_Ptr[1] == 0)
    {
    }

    capture_value = Timer_Ptr[1];
    cout << "First captured value = " << capture_value << endl;

    // debounce delay using counter register
    delay_start = Timer_Ptr[2];
    while ((Timer_Ptr[2] - delay_start) < 250000)
    {
    }

    cout << "Press SW5 again for second capture..." << endl;

    while (Timer_Ptr[1] == capture_value)
    {
    }

    new_capture_value = Timer_Ptr[1];

    cout << "Second captured value = " << new_capture_value << endl;
    cout << "Difference = " << (new_capture_value - capture_value) << " clock cycles" << endl;
    cout << "Elapsed time = "
         << (double)(new_capture_value - capture_value) / 50000000.0
         << " seconds" << endl;

    return 0;
}
