#include <cstdint>

#include "hw/interrupt.h"

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

#define PORTD_AHB_BASE 0x4005b000
#define PORTF_AHB_BASE 0x4005d000
#define PORTD_GPIODATA (*((volatile std::uint32_t *)(PORTD_AHB_BASE)))
#define PORTF_GPIODATA (*((volatile std::uint32_t *)(PORTF_AHB_BASE)))
#define PORTD_GPIODIR (*((volatile std::uint32_t *)(PORTD_AHB_BASE + 0x400)))
#define PORTF_GPIODIR (*((volatile std::uint32_t *)(PORTF_AHB_BASE + 0x400)))
#define PORTD_GPIODEN (*((volatile std::uint32_t *)(PORTD_AHB_BASE + 0x51c)))
#define PORTF_GPIODEN (*((volatile std::uint32_t *)(PORTF_AHB_BASE + 0x51c)))


// #define PORTF_APB_BASE 0x40025000
// #define PORTF_GPIODATA (*((std::uint32_t *)(PORTF_APB_BASE)))
// #define PORTF_GPIODIR (*((std::uint32_t *)(PORTF_APB_BASE + 0x400)))
// #define PORTF_GPIODEN (*((std::uint32_t *)(PORTF_APB_BASE + 0x51c)))

#define RCGCTIMER (*((volatile std::uint32_t *)(SYSCTL_BASE + 0x604)))
#define R0 0

#define TIMER0_16_32_BASE 0x40030000
#define TIMER0_16_32_GPTMTAMR (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x004)))
#define TIMER0_16_32_GPTMCTL (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x00c)))
#define TIMER0_16_32_GPTMIMR (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x018)))
#define TIMER0_16_32_GPTMTAV (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x050)))
#define TIMER0_16_32_GPTMRIS (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x01c)))
#define TIMER0_16_32_GPTMMIS (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x020)))
#define TIMER0_16_32_GPTMICR (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x024)))
#define TIMER0_16_32_GPTMTAILR (*((volatile std::uint32_t *)(TIMER0_16_32_BASE + 0x028)))

#define TAMR 0
#define TAEN 0
#define TATOIM 0
#define TATOCINT 0


#define TIMER0A_16_32_INT_NUM 19
#define CORE_PERIPH_BASE 0xe000e000
// Treat EN* as 128 bit variable? Bit order?
#define EN0 (*((volatile std::uint32_t *)(CORE_PERIPH_BASE + 0x100)))

namespace hw
{
   using register_type = volatile std::uint32_t;
   using register_pad = std::uint32_t;
   class Timer
   {
   public:
      register_type GPTMCFG;
      register_type GPTMTAMR;
      register_type GPTMTBMR;
      register_type GPTMCTL;
      register_type GPTM_SYNC;
      register_type pad1;
      register_type GPTMIMR;
      const register_type GPTMRIS;
      const register_type GPTMMIS;
      register_type GPTMICR;
      register_type GPTMTAILR;
      register_type GPTMTBILR;
      register_type GPTMTAMATCHR;
      register_type GPTMTBMATCHR;
      register_type GPTMTAPR;
      register_type GPTMTBPR;
      const register_type GPTMTAR;
      const register_type GPTMTBR;
      register_type GPTMTAV;
      register_type GPTMTBV;
      const register_type GPTMRTCPD;
      const register_type GPTMTAPS;
      const register_type GPTMTBPS;
      const register_type GPTMTAPV;
      const register_type GPTMTBPV;
      // long pad
//      const register_type GPTMPP;
   };

   class Gpio
   {
   public:
      register_type GPIODATA[256];
      register_type GPIODIR;
      register_type GPIOIS;
      register_type GPIOIBE;
      register_type GPIOIEV;
      register_type GPIOIM;
      const register_type GPIORIS;
      const register_type GPIOMIS;
      register_type GPIOICR;
      register_type GPIOAFSEL;
      register_pad pad1[55];
      register_type GPIODR2R;
      register_type GPIODR4R;
      register_type GPIODR8R;
      register_type GPIOODR;
      register_type GPIOPUR;
      register_type GPIOPDR;
      register_type GPIOSLR;
      register_type GPIODEN;
      register_type GPIOLOCK;
      register_type GPIOCR;
      register_type GPIOAMSEL;
      register_type GPIOPCTL;
      register_type GPIOADCCTL;
      register_type GPIODMACTL;
      register_pad pad2[678];
      const register_type GPIOPeriphID4;
      const register_type GPIOPeriphID5;
      const register_type GPIOPeriphID6;
      const register_type GPIOPeriphID7;
      const register_type GPIOPeriphID0;
      const register_type GPIOPeriphID1;
      const register_type GPIOPeriphID2;
      const register_type GPIOPeriphID3;
      const register_type GPIOPCellID0;
      const register_type GPIOPCellID1;
      const register_type GPIOPCellID2;
      const register_type GPIOPCellID3;
   };

   struct Gpios
   {
      struct Apb
      {
	 Gpio portA;
	 Gpio portB;
	 Gpio portC;
	 Gpio portD;
	 //pad?
//	 port e f
      };
      struct Ahb
      {
      };
   };
}

int main()
{
   // need to configure sysclk?
   // need to start bus?

   hw::Timer &timer0_16_32 = *reinterpret_cast<hw::Timer *>(TIMER0_16_32_BASE);

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
   PORTF_GPIODEN |= (1 << BIT1);
   PORTD_GPIODEN |= (1 << BIT0);
   
   // Led pin output
   PORTF_GPIODIR |= (1 << BIT1);
   PORTD_GPIODIR |= (1 << BIT0);
   
   // Default 2mA drive

//   t.a.b();
//   A &a_ = t.a;
   //.b();
//   Test test;
//   test.a.b();


   EN0 = (1 << TIMER0A_16_32_INT_NUM);

   //GPTMCL TnEN = 0;
   //GPTMCFG = 0x0;
   TIMER0_16_32_GPTMTAMR |= (0x2 << TAMR);
   TIMER0_16_32_GPTMTAILR = 80000000;
   TIMER0_16_32_GPTMIMR |= (1 << TATOIM);
//   TIMER0_16_32_GPTMCTL |= (1 << TAEN);
   timer0_16_32.GPTMCTL |= (1 << TAEN);
   
   
   while(true)
   {
//      (&PORTF_GPIODATA)[BIT1_MASK] = (1 << BIT1);
//      (&PORTF_GPIODATA)[BIT1_MASK] = (0 << BIT1);
      int a = TIMER0_16_32_GPTMTAV;
      int ris = TIMER0_16_32_GPTMRIS;
      int mis = TIMER0_16_32_GPTMMIS;
      asm("nop");
   }

   return 0;
}

ISR(vector_16_32_bit_timer_0a)
{
   // Clear interrupt flag early so interrupt won't be retriggered by NVIC
   TIMER0_16_32_GPTMICR = (1 << TATOCINT);

   (&PORTF_GPIODATA)[BIT1_MASK] = ~(&PORTF_GPIODATA)[BIT1_MASK];
   (&PORTD_GPIODATA)[BIT0_MASK] = ~(&PORTD_GPIODATA)[BIT0_MASK];
}
