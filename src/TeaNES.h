#ifndef TEANES_H
#define TEANES_H

namespace CPU {
	extern bool interrupt_pending;
	extern bool interrupt_is_NMI;
}
namespace PPU {
    extern uint8_t regs[8];
	extern void setFlag(uint8_t reg, int bit, uint8_t value);
    extern void tick(int ticks);
}
namespace Cart {
	extern uint8_t PRG_ROM[32 * 1024];
}
#endif