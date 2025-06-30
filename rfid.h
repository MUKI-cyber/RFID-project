#include <lpc21xx.h>

void read_rfid(char *tag)
{
    int i;

    // Wait for start byte (0x02)
   // while (uart0_rx() != 0x02);

    // Read next 10 bytes (ASCII hex characters)
    for (i = 0; i < 10; i++)
        tag[i] = uart0_rx();

    tag[10] = '\0';  // Null-terminate

    uart0_rx();  // Discard end byte (0x03)
}




