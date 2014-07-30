#ifndef SYSCTL_H
#define SYSCTL_H

#include <cstdint>

#include "types.h"

namespace hw
{
  namespace sysctl
  {
    struct SysctlRegisters
    {
      const register_t DID0;
      const register_t DID1;
      const pad_t reserved0[10];
      register_t PBORCTL;
      const pad_t reserved1[7];
      const register_t RIS;
      register_t IMC;
      register_t MISC;
      register_t RESC;
      register_t RCC;
      const pad_t reserved2[2];
      register_t GPIOHBCTL;
      register_t RCC2;
      const pad_t reserved3[2];
      register_t MOSCCTL;
      const pad_t reserved4[49];
      register_t DSLPCLKCFG;
      const pad_t reserved5[1];
      const register_t SYSPROP;
      register_t PIOSCCAL;
      const register_t PIOSCSTAT;
      const pad_t reserved6[2];
      const register_t PLLFREQ0;
      const register_t PLLFREQ1;
      const register_t PLLSTAT;
      const pad_t reserved7[7];
      register_t SLPPWRCFG;
      register_t DSLPPWRCFG;
      const pad_t reserved8[9];
      register_t LDOSPCTL;
      const register_t LDOSPCAL;
      register_t LDODPCTL;
      const register_t LDODPCAL;
      const pad_t reserved9[2];
      const register_t SDPMST;
      const pad_t reserved10[76];
      const register_t PPWD;
      const register_t PPTIMER;
      const register_t PPGPIO;
      const register_t PPDMA;
      const pad_t reserved11[1];
      const register_t PPHIB;
      const register_t PPUART;
      const register_t PPSSI;
      const register_t PPI2C;
      const pad_t reserved12[1];
      const register_t PPUSB;
      const pad_t reserved13[2];
      const register_t PPCAN;
      const register_t PPADC;
      const register_t PPACMP;
      const register_t PPPWM;
      const register_t PPQEI;
      const pad_t reserved14[4];
      const register_t PPEEPROM;
      const register_t PPWTIMER;
      const pad_t reserved15[104];
      register_t SRWD;
      register_t SRTIMER;
      register_t SRGPIO;
      register_t SRDMA;
      const pad_t reserved16[1];
      register_t SRHIB;
      register_t SRUART;
      register_t SRSSI;
      register_t SRI2C;
      const pad_t reserved17[1];
      register_t SRUSB;
      const pad_t reserved18[2];
      register_t SRCAN;
      register_t SRADC;
      register_t SRACMP;
      register_t SRPWM;
      register_t SRQEI;
      const pad_t reserved19[4];
      register_t SREEPROM;
      register_t SRWTIMER;
      const pad_t reserved20[40];
      register_t RCGCWD;
      register_t RCGCTIMER;
      register_t RCGCGPIO;
      register_t RCGCDMA;
      const pad_t reserved21[1];
      register_t RCGCHIB;
      register_t RCGCUART;
      register_t RCGCSSI;
      register_t RCGCI2C;
      const pad_t reserved22[1];
      register_t RCGCUSB;
      const pad_t reserved23[2];
      register_t RCGCCAN;
      register_t RCGCADC;
      register_t RCGCACMP;
      register_t RCGCPWM;
      register_t RCGCQEI;
      const pad_t reserved24[4];
      register_t RCGCEEPROM;
      register_t RCGCWTIMER;
      const pad_t reserved25[40];
      register_t SCGCWD;
      register_t SCGCTIMER;
      register_t SCGCGPIO;
      register_t SCGCDMA;
      const pad_t reserved26[1];
      register_t SCGCHIB;
      register_t SCGCUART;
      register_t SCGCSSI;
      register_t SCGCI2C;
      const pad_t reserved27[1];
      register_t SCGCUSB;
      const pad_t reserved28[2];
      register_t SCGCCAN;
      register_t SCGCADC;
      register_t SCGCACMP;
      register_t SCGCPWM;
      register_t SCGCQEI;
      const pad_t reserved29[4];
      register_t SCGCEEPROM;
      register_t SCGCWTIMER;
      const pad_t reserved30[40];
      register_t DCGCWD;
      register_t DCGCTIMER;
      register_t DCGCGPIO;
      register_t DCGCDMA;
      const pad_t reserved31[1];
      register_t DCGCHIB;
      register_t DCGCUART;
      register_t DCGCSSI;
      register_t DCGCI2C;
      const pad_t reserved32[1];
      register_t DCGCUSB;
      const pad_t reserved33[2];
      register_t DCGCCAN;
      register_t DCGCADC;
      register_t DCGCACMP;
      register_t DCGCPWM;
      register_t DCGCQEI;
      const pad_t reserved34[4];
      register_t DCGCEEPROM;
      register_t DCGCWTIMER;
      const pad_t reserved35[104];
      const register_t PRWD;
      const register_t PRTIMER;
      const register_t PRGPIO;
      const register_t PRDMA;
      const pad_t reserved36[1];
      const register_t PRHIB;
      const register_t PRUART;
      const register_t PRSSI;
      const register_t PRI2C;
      const pad_t reserved37[1];
      const register_t PRUSB;
      const pad_t reserved38[2];
      const register_t PRCAN;
      const register_t PRADC;
      const register_t PRACMP;
      const register_t PRPWM;
      const register_t PRQEI;
      const pad_t reserved39[4];
      const register_t PREEPROM;
      const register_t PRWTIMER;
    };

    namespace 
    {
      const std::uint32_t SYSCTL_BASE = 0x400fe000;
    }

    SysctlRegisters *const sysctl = reinterpret_cast<SysctlRegisters*>(SYSCTL_BASE);

    const register_t PORTD = 1 << 3;
    const register_t PORTF = 1 << 5;

    const register_t R0 = 1 << 0;
    const register_t R1 = 1 << 1;
    const register_t R2 = 1 << 2;
    const register_t R3 = 1 << 3;
    const register_t R4 = 1 << 4;
    const register_t R5 = 1 << 5;

    const register_t TIMER0A_16_32_INT_NUM = 1 << 19;
  }
}

#endif
