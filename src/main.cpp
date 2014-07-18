#include <cstdint>

#include "hw/interrupt.h"
#include "hw/gpio.h"
#include "hw/timer.h"

#define SYSCTL_BASE 0x400fe000

// This shifting works if working with 32-bit pointers
#define BIT0_MASK (1 << 0)
#define BIT1_MASK (1 << 1)
#define BIT0 0
#define BIT1 1

#define PORTD 3
#define PORTF 5
#define R3 3
#define R5 5
#define GPIOHBCTL (*((volatile std::uint32_t *)(SYSCTL_BASE + 0x6c)))
#define RCGCGPIO (*((volatile std::uint32_t *)(SYSCTL_BASE + 0x608)))

#define RCGCTIMER (*((volatile std::uint32_t *)(SYSCTL_BASE + 0x604)))
#define R0 0

#define TAMR 0
#define TAEN 0
#define TATOIM 0
#define TATOCINT 0

#define TIMER0A_16_32_INT_NUM 19
#define CORE_PERIPH_BASE 0xe000e000
// Treat EN* as 128 bit variable? Bit order?
#define EN0 (*((volatile std::uint32_t *)(CORE_PERIPH_BASE + 0x100)))

int main()
{
  // need to configure sysclk?
  // need to start bus?


  // Enable port clock in run mode
  RCGCGPIO |= (1 << R5) | (1 << R3);

  // Enable AHB (bus)
  GPIOHBCTL |= (1 << PORTF) | (1 << PORTD);

  // Enable timer module clock in run mode
  RCGCTIMER |= (1 << R0);

  // Need to wait 3 clocks before touching GPIO registers after switching bus
  // Need to wait 3 clocks before touching timer registers after switching bus
  for(int i = 0; i < 10; ++i)
  {
    asm("nop");
  }

  // Digital pin
  hw::gpio::apb::portF.GPIODEN |= (1 << BIT1);
  hw::gpio::apb::portD.GPIODEN |= (1 << BIT0);

  // Led pin output
  hw::gpio::apb::portF.GPIODIR |= (1 << BIT1);
  hw::gpio::apb::portD.GPIODIR |= (1 << BIT0);

  // Default 2mA drive

  // t.a.b();
  // A &a_ = t.a;
  //.b();
  // Test test;
  // test.a.b();


  EN0 = (1 << TIMER0A_16_32_INT_NUM);

  // GPTMCL TnEN = 0;
  // GPTMCFG = 0x0;
  hw::timer::timer0_16_32.GPTMTAMR |= (0x2 << TAMR);
  hw::timer::timer0_16_32.GPTMTAILR = 80000000;
  hw::timer::timer0_16_32.GPTMIMR |= (1 << TATOIM);
  // hw::timer::TIMER0_16_32_GPTMCTL |= (1 << TAEN);
  hw::timer::timer0_16_32.GPTMCTL |= (1 << TAEN);


  while(true)
  {
    // (&PORTF_GPIODATA)[BIT1_MASK] = (1 << BIT1);
    // (&PORTF_GPIODATA)[BIT1_MASK] = (0 << BIT1);
    int a = hw::timer::timer0_16_32.GPTMTAV;
    int ris = hw::timer::timer0_16_32.GPTMRIS;
    int mis = hw::timer::timer0_16_32.GPTMMIS;
    asm("nop");
  }

  return 0;
}

ISR(vector_16_32_bit_timer_0a)
{
  // Clear interrupt flag early so interrupt won't be retriggered by NVIC
  hw::timer::timer0_16_32.GPTMICR = (1 << TATOCINT);

  hw::gpio::apb::portD.GPIODATA[BIT0_MASK] = ~hw::gpio::apb::portD.GPIODATA[BIT0_MASK];
  hw::gpio::apb::portF.GPIODATA[BIT1_MASK] = ~hw::gpio::apb::portF.GPIODATA[BIT1_MASK];
}
