#ifndef COREPERIPH_H
#define COREPERIPH_H

#include <cstdint>

#include "types.h"

namespace hw
{
  namespace coreperiph
  {
    namespace
    {
      const std::uint32_t CORE_PERIPH_BASE = 0xe000e000;
    }

    register_t &EN0  = *reinterpret_cast<register_t*>(CORE_PERIPH_BASE + 0x100);
  }
}

#endif
