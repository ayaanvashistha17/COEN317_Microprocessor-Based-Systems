#include "xil_exception.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xil_io.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ---------------- AXI CDMA register offsets ----------------
#define CDMA_CR_OFFSET   0x00   // Control Register
#define CDMA_SR_OFFSET   0x04   // Status Register
#define CDMA_SA_OFFSET   0x18   // Source Address
#define CDMA_DA_OFFSET   0x20   // Destination Address
#define CDMA_BTT_OFFSET  0x28   // Bytes To Transfer

// ---------------- Useful bit masks ----------------
#define CDMA_CR_RESET_MASK   0x00000004
#define CDMA_SR_IDLE_MASK    0x00000002

// Keep this small first. Increase later only after basic DMA works.
#define ARRAY_WORDS 1024

static inline u32 cdma_read(u32 base, u32 offset)
{
    return Xil_In32(base + offset);
}

static inline void cdma_write(u32 base, u32 offset, u32 value)
{
    Xil_Out32(base + offset, value);
}

static void print_status(const char* label, u32 status)
{
    cout << label << " = 0x"
         << hex << setw(8) << setfill('0') << status
         << dec << setfill(' ') << endl;
}

int main()
{
    cout << "===== COEN 317 Lab 4 Part 2: AXI CDMA =====" << endl;

    // CDMA register base
    const u32 cdma_base = XPAR_AXI_CDMA_0_BASEADDR;

    // Source/Destination DDR regions from HP0 and HP2
    volatile u32* source_address =
        reinterpret_cast<volatile u32*>(XPAR_PS7_DDR_0_S_AXI_HP0_BASEADDR);

    volatile u32* destination_address =
        reinterpret_cast<volatile u32*>(XPAR_PS7_DDR_0_S_AXI_HP2_BASEADDR);

    const u32 num_words = ARRAY_WORDS;
    const u32 num_bytes = num_words * sizeof(u32);

    // 1) Initialize source and destination arrays
    for (u32 i = 0; i < num_words; ++i)
    {
        source_address[i] = i;
        destination_address[i] = 0xFFFFFFFF;
    }

    cout << "Source array base      : 0x" << hex
         << reinterpret_cast<u32>(source_address) << endl;
    cout << "Destination array base : 0x"
         << reinterpret_cast<u32>(destination_address) << dec << endl;
    cout << "Transfer size          : " << num_words
         << " words (" << num_bytes << " bytes)" << endl;

    cout << "\nBefore DMA:" << endl;
    for (u32 i = 0; i < 8; ++i)
    {
        cout << "src[" << i << "] = " << source_address[i]
             << "    dst[" << i << "] = " << destination_address[i] << endl;
    }

    // 2) Reset the CDMA
    cdma_write(cdma_base, CDMA_CR_OFFSET, CDMA_CR_RESET_MASK);

    // Wait until reset bit clears
    while (cdma_read(cdma_base, CDMA_CR_OFFSET) & CDMA_CR_RESET_MASK)
    {
        // wait
    }

    print_status("Status after reset", cdma_read(cdma_base, CDMA_SR_OFFSET));

    // 3) Poll until device is idle before configuring
    while ((cdma_read(cdma_base, CDMA_SR_OFFSET) & CDMA_SR_IDLE_MASK) == 0)
    {
        // wait
    }

    print_status("Status when idle", cdma_read(cdma_base, CDMA_SR_OFFSET));

    // 4) Configure simple mode with interrupts disabled
    // For this lab, polling is used instead of interrupts
    cdma_write(cdma_base, CDMA_CR_OFFSET, 0x00000000);

    // 5) Program source and destination addresses
    cdma_write(cdma_base, CDMA_SA_OFFSET, reinterpret_cast<u32>(source_address));
    cdma_write(cdma_base, CDMA_DA_OFFSET, reinterpret_cast<u32>(destination_address));

    // 6) Flush cache before DMA starts
    Xil_DCacheFlush();

    // 7) Start transfer by writing the number of bytes to BTT
    cdma_write(cdma_base, CDMA_BTT_OFFSET, num_bytes);

    print_status("Status right after BTT write", cdma_read(cdma_base, CDMA_SR_OFFSET));

    // 8) Poll until idle bit becomes 1 again
    while ((cdma_read(cdma_base, CDMA_SR_OFFSET) & CDMA_SR_IDLE_MASK) == 0)
    {
        // wait for transfer to complete
    }

    print_status("Status after DMA completion", cdma_read(cdma_base, CDMA_SR_OFFSET));

    // Invalidate destination cache lines before CPU reads copied data
    Xil_DCacheInvalidateRange(
        reinterpret_cast<INTPTR>(const_cast<u32*>(reinterpret_cast<const u32*>(destination_address))),
        num_bytes
    );

    // 9) Compare source and destination arrays
    bool success = true;
    int mismatch_index = -1;

    for (u32 i = 0; i < num_words; ++i)
    {
        if (destination_address[i] != source_address[i])
        {
            success = false;
            mismatch_index = static_cast<int>(i);
            break;
        }
    }

    cout << "\nAfter DMA:" << endl;
    for (u32 i = 0; i < 8; ++i)
    {
        cout << "src[" << i << "] = " << source_address[i]
             << "    dst[" << i << "] = " << destination_address[i] << endl;
    }

    if (success)
    {
        cout << "\nDMA transfer SUCCESS: destination matches source." << endl;
    }
    else
    {
        cout << "\nDMA transfer FAILED." << endl;
        cout << "First mismatch at index " << mismatch_index << endl;
        cout << "src[" << mismatch_index << "] = " << source_address[mismatch_index] << endl;
        cout << "dst[" << mismatch_index << "] = " << destination_address[mismatch_index] << endl;
    }

    cout << "End of application." << endl;
    return 0;
}
