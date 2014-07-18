#include <cstdint>

#include "hw/coreperiph.h"
#include "hw/interrupt.h"
#include "hw/gpio.h"
#include "hw/sysctl.h"
#include "hw/timer.h"
#include "hw/uart.h"

using namespace hw;

void enable_uart_1();

int main()
{
  // need to configure sysclk?
  // need to start bus?

  // Enable port clock in run mode
  sysctl::sysctl.RCGCGPIO |= sysctl::R5 | sysctl::R3;

  // Enable AHB (bus)
  sysctl::sysctl.GPIOHBCTL |= sysctl::PORTF | sysctl::PORTD;

  // Enable timer module clock in run mode
  sysctl::sysctl.RCGCTIMER |= sysctl::R0;

  // Need to wait 3 clocks before touching GPIO registers after switching bus
  // Need to wait 3 clocks before touching timer registers after switching bus
  for(int i = 0; i < 10; ++i)
  {
    asm("nop");
  }

  // Digital pin
  gpio::ahb::portF.GPIODEN |= gpio::PIN1;
  gpio::ahb::portD.GPIODEN |= gpio::PIN0;

  // Led pin output
  gpio::ahb::portF.GPIODIR |= gpio::PIN1;
  gpio::ahb::portD.GPIODIR |= gpio::PIN0;

  // Default 2mA drive

  // t.a.b();
  // A &a_ = t.a;
  //.b();
  // Test test;
  // test.a.b();

  coreperiph::EN0 = sysctl::TIMER0A_16_32_INT_NUM;

  // GPTMCL TnEN = 0;
  // GPTMCFG = 0x0;
  timer::timer0_16_32.GPTMTAMR |= timer::TAMR_PERIODIC;
  timer::timer0_16_32.GPTMTAILR = 80000000;
  timer::timer0_16_32.GPTMIMR |= timer::TATOIM;
  // timer::TIMER0_16_32_GPTMCTL |= (1 << TAEN);
  timer::timer0_16_32.GPTMCTL |= timer::TAEN;

  enable_uart_1();
  
    
  while(true)
  {
    if(!(uart::uart1.UARTFR & uart::BUSY) && !(uart::uart1.UARTFR & uart::RXFE))
    {
      uart::uart1.UARTDR = uart::uart1.UARTDR;
    }
    asm("nop");
  }

  return 0;
}

void enable_uart_1()
{
  // UART 1: PB0=U1RX, PB1=U1TX
  // Port B must be clocked and pin directions must be set up correctly

  // Enable clocking for Port B
  sysctl::sysctl.RCGCGPIO |= sysctl::R1;

  // Clock UART module
  sysctl::sysctl.RCGCUART |= sysctl::R1;

  for(int i = 0; i < 10; ++i)
  {
    asm("nop");
  }

  gpio::apb::portB.GPIODEN |= gpio::PIN0 | gpio::PIN1;
  gpio::apb::portB.GPIODIR &= ~(gpio::PIN0);
  gpio::apb::portB.GPIODIR |= gpio::PIN1;

  // baud_rate = 9600;
  std::uint32_t div_int = 104;
  std::uint32_t div_frac = 11;

  uart::uart1.UARTIBRD = div_int;
  uart::uart1.UARTFBRD = div_frac;
  uart::uart1.UARTLCRH |= uart::WLEN_8BIT;

  gpio::apb::portB.GPIOPCTL &= ~(gpio::PMC0_MASK | gpio::PMC1_MASK);
  gpio::apb::portB.GPIOPCTL |= gpio::PB0_U1RX | gpio::PB1_U1TX;
  gpio::apb::portB.GPIOAFSEL |= gpio::PIN1 | gpio::PIN0;

  uart::uart1.UARTCTL |= uart::UARTEN;
}

ISR(vector_16_32_bit_timer_0a)
{
  // Clear interrupt flag early so interrupt won't be retriggered by NVIC
  timer::timer0_16_32.GPTMICR = timer::TATOCINT;

  gpio::ahb::portD.GPIODATA[gpio::PIN0] = ~gpio::ahb::portD.GPIODATA[gpio::PIN0];
  gpio::ahb::portF.GPIODATA[gpio::PIN1] = ~gpio::ahb::portF.GPIODATA[gpio::PIN1];
}
