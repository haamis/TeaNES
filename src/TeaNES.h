#ifndef TEANES_H
#define TEANES_H

namespace CPU {}
namespace PPU {
    extern uint8_t regs[8];
    extern void setFlag(int reg, int bit, uint8_t value);
    extern void tick();
}
namespace Cart {
	extern uint8_t PRG_ROM[32 * 1024];
}
#endif