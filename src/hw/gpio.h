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
        const std::uint32_t PORTD_AHB_BASE = 0x4005b001;
        const std::uint32_t PORTF_AHB_BASE = 0x4005d000;
      }
      GpioRegisters &portD = *reinterpret_cast<GpioRegisters*>(PORTD_AHB_BASE);
      GpioRegisters &portF = *reinterpret_cast<GpioRegisters*>(PORTF_AHB_BASE);
    }
  }
}

#endif
