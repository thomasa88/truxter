#ifndef GPIO_H
#define GPIO_H

#include <cstdint>

#include "types.h"

namespace hw
{
  namespace gpio
  {
    struct GpioRegisters
    {
      register_t GPIODATA[256];
      register_t GPIODIR;
      register_t GPIOIS;
      register_t GPIOIBE;
      register_t GPIOIEV;
      register_t GPIOIM;
      const register_t GPIORIS;
      const register_t GPIOMIS;
      register_t GPIOICR;
      register_t GPIOAFSEL;
      const pad_t reserved1[55];
      register_t GPIODR2R;
      register_t GPIODR4R;
      register_t GPIODR8R;
      register_t GPIOODR;
      register_t GPIOPUR;
      register_t GPIOPDR;
      register_t GPIOSLR;
      register_t GPIODEN;
      register_t GPIOLOCK;
      register_t GPIOCR;
      register_t GPIOAMSEL;
      register_t GPIOPCTL;
      register_t GPIOADCCTL;
      register_t GPIODMACTL;
      const pad_t reserved2[678];
      const register_t GPIOPeriphID4;
      const register_t GPIOPeriphID5;
      const register_t GPIOPeriphID6;
      const register_t GPIOPeriphID7;
      const register_t GPIOPeriphID0;
      const register_t GPIOPeriphID1;
      const register_t GPIOPeriphID2;
      const register_t GPIOPeriphID3;
      const register_t GPIOPCellID0;
      const register_t GPIOPCellID1;
      const register_t GPIOPCellID2;
      const register_t GPIOPCellID3;
    };

    namespace ahb
    {
      namespace
      {
        const std::uint32_t PORTB_AHB_BASE = 0x40059000;
        const std::uint32_t PORTD_AHB_BASE = 0x4005b000;
        const std::uint32_t PORTF_AHB_BASE = 0x4005d000;
      }
      GpioRegisters *const portB = reinterpret_cast<GpioRegisters*>(PORTB_AHB_BASE);
      GpioRegisters *const portD = reinterpret_cast<GpioRegisters*>(PORTD_AHB_BASE);
      GpioRegisters *const portF = reinterpret_cast<GpioRegisters*>(PORTF_AHB_BASE);
    }

    namespace apb
    {
       namespace
       {
	  const std::uint32_t PORTB_APB_BASE = 0x40005000;
       }
       GpioRegisters *const portB = reinterpret_cast<GpioRegisters*>(PORTB_APB_BASE);
    }

    const register_t PIN0 = 1 << 0;
    const register_t PIN1 = 1 << 1;
    const register_t PIN2 = 1 << 2;
    const register_t PIN3 = 1 << 3;
    const register_t PIN4 = 1 << 4;
    const register_t PIN5 = 1 << 5;
    const register_t PIN6 = 1 << 6;
    const register_t PIN7 = 1 << 7;

    const std::uint32_t PMC0_OFFSET = 0;
    const std::uint32_t PMC1_OFFSET = 4;
    const register_t PMC0_MASK = 0xf << PMC0_OFFSET;
    const register_t PMC1_MASK = 0xf << PMC1_OFFSET;
    const register_t PB0_U1RX = 1 << PMC0_OFFSET;
    const register_t PB1_U1TX = 1 << PMC1_OFFSET;
  }
}

#endif
