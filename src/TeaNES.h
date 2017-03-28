#ifndef TEANES_H
#define TEANES_H
namespace PPU {
    extern uint8_t regs[8];
    extern void setFlag(int reg, int bit, uint8_t value);
    extern void tick();
}
namespace CPU {}
#endif