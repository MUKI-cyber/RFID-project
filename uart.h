void uart0_init(void)
{
    PINSEL0 |= 0x00000005;  // UART0 Tx, Rx on P0.0 and P0.1
    U0LCR = 0x83;           // Enable DLAB, 8-bit, 1 stop bit
    U0DLL = 97;             // 9600 baud @ 15 MHz PCLK
    U0DLM = 0;
    U0LCR = 0x03;           // Disable DLAB
}


char uart0_rx(void)
{
    while (!(U0LSR & 0x01));  // Wait until data is available
    return U0RBR;
}
