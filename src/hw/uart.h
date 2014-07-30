#ifndef UART_H
#define UART_H

#include <cstdint>

#include "types.h"

namespace hw
{
  namespace uart
  {
    struct UartRegisters
    {
      register_t UARTDR;
      register_t UARTRSR_UARTECR;
      const pad_t reserved1[4];
      const register_t UARTFR;
      const pad_t reserved2;
      register_t UARTILPR;
      register_t UARTIBRD;
      register_t UARTFBRD;
      register_t UARTLCRH;
      register_t UARTCTL;
      register_t UARTIFLS;
      register_t UARTIM;
      const register_t UARTRIS;
      const register_t UARTMIS;
      register_t UARTICR;
      register_t UARTDMACTL;
      const pad_t reserved3[22];
      register_t UART9BITADDR;
      register_t UART9BITAMASK;
      const pad_t reserved4[965];
      const register_t UARTPP;
      const pad_t reserved5;
      register_t UARTCC;
      const pad_t reserved6;
      const register_t UARTPeriphID4;
      const register_t UARTPeriphID5;
      const register_t UARTPeriphID6;
      const register_t UARTPeriphID7;
      const register_t UARTPeriphID0;
      const register_t UARTPeriphID1;
      const register_t UARTPeriphID2;
      const register_t UARTPeriphID3;
      const register_t UARTPCellID0;
      const register_t UARTPCellID1;
      const register_t UARTPCellID2;
      const register_t UARTPCellID3;
    };

    namespace
    {
      const std::uint32_t UART1_BASE = 0x4000D000;
    }

    UartRegisters &uart1 = *reinterpret_cast<UartRegisters*>(UART1_BASE);

    const register_t WLEN_8BIT = 0x3 << 5;
    const register_t UARTEN = 1 << 0;
    const register_t BUSY = 1 << 3;
    const register_t RXFE = 1 << 4;
  }
}

#endif
