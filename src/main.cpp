#include <cstdint>

#include "hw/coreperiph.h"
#include "hw/interrupt.h"
#include "hw/gpio.h"
#include "hw/sysctl.h"
#include "hw/timer.h"

using namespace hw;

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


  while(true)
  {
    asm("nop");
  }

  return 0;
}

ISR(vector_16_32_bit_timer_0a)
{
  // Clear interrupt flag early so interrupt won't be retriggered by NVIC
  timer::timer0_16_32.GPTMICR = timer::TATOCINT;

  gpio::ahb::portD.GPIODATA[gpio::PIN0] = ~gpio::ahb::portD.GPIODATA[gpio::PIN0];
  gpio::ahb::portF.GPIODATA[gpio::PIN1] = ~gpio::ahb::portF.GPIODATA[gpio::PIN1];
}
