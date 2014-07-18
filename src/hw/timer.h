#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

#include "types.h"

namespace hw
{
  namespace timer
  {
    struct TimerRegisters
    {
      register_t GPTMCFG;
      register_t GPTMTAMR;
      register_t GPTMTBMR;
      register_t GPTMCTL;
      register_t GPTM_SYNC;
      pad_t reserved1;
      register_t GPTMIMR;
      const register_t GPTMRIS;
      const register_t GPTMMIS;
      register_t GPTMICR;
      register_t GPTMTAILR;
      register_t GPTMTBILR;
      register_t GPTMTAMATCHR;
      register_t GPTMTBMATCHR;
      register_t GPTMTAPR;
      register_t GPTMTBPR;
      const register_t GPTMTAR;
      const register_t GPTMTBR;
      register_t GPTMTAV;
      register_t GPTMTBV;
      const register_t GPTMRTCPD;
      const register_t GPTMTAPS;
      const register_t GPTMTBPS;
      const register_t GPTMTAPV;
      const register_t GPTMTBPV;
      pad_t reserved2[981];
      const register_t GPTMPP;
    };

    namespace
    {
      const std::uint32_t TIMER0_16_32_BASE = 0x40030000;
    }

    TimerRegisters &timer0_16_32 = *reinterpret_cast<TimerRegisters*>(TIMER0_16_32_BASE);
  }
}

#endif
