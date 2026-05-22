#include "xparameters.h"
#include "xil_types.h"
#include <iostream>

using namespace std;

int main()
{
    u32* ptr = (u32*) XPAR_TMRCTR_0_BASEADDR;

    double period_s, duty_percent, high_time_s;
    const double CLOCK_FREQ = 50000000.0;

    cout << "PWM test" << endl;

    while (1)
    {
        cout << "Enter period in seconds: ";
        cin >> period_s;

        cout << "Enter duty cycle in percent: ";
        cin >> duty_percent;

        high_time_s = period_s * (duty_percent / 100.0);

        u32 tlr0 = (u32)(period_s * CLOCK_FREQ) - 2;
        u32 tlr1 = (u32)(high_time_s * CLOCK_FREQ) - 2;

        // Write base PWM config to TCSR0 and TCSR1
        *ptr = 0x216;          // TCSR0
        *(ptr + 4) = 0x216;    // TCSR1

        // Write load values
        *(ptr + 1) = tlr0;   // TLR0
        *(ptr + 5) = tlr1;   // TLR1

        // Set load bit
        *ptr |= (1 << 5);
        *(ptr + 4) |= (1 << 5);

        // Clear load bit
        *ptr &= ~(1 << 5);
        *(ptr + 4) &= ~(1 << 5);

        // Enable timers
        *ptr |= (1 << 7);
        *(ptr + 4) |= (1 << 7);

        cout << "PWM updated" << endl;
    }

    return 0;
}
