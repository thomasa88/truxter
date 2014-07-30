#include "sysctl.h"
#include "uart.h"

using namespace hw::uart;

void UartRegisters::enable()
{
	std::uint32_t clock_gating_bit_offset = ((reinterpret_cast<std::uint32_t>(this) >> 12) & 0xff) - 0xc;

	// Clock UART module
	sysctl::sysctl->RCGCUART |= (1 << clock_gating_bit_offset);

	for(int i = 0; i < 3; ++i)
	{
	  asm("nop");
	}

	// baud_rate = 9600 with 16MHz clock
	std::uint32_t div_int = 104;
	std::uint32_t div_frac = 11;
	UARTIBRD = div_int;
	UARTFBRD = div_frac;
	UARTLCRH |= WLEN_8BIT;
	UARTCTL |= UARTEN;
}
