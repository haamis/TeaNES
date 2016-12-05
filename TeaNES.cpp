#include <iostream>
#include <fstream>
#include "TeaNES.h"

// Helper function to change a certain bit in an 8-bit register.
uint8_t changeBit (uint8_t byte, int bit, uint8_t value) {
	byte = byte & (0xFF - (2^bit));	// First we clear the bit.
	byte = byte | value << bit;		// Then we set the approriate value.
	return byte;					// Not the most elegant solution.
}

namespace CPU {

	#define INTERRUPT_CYCLES 512

	// Declare CPU registers.
	uint8_t A = 0;
	uint8_t X = 0;
	uint8_t Y = 0;
	uint8_t flags = 0x20;		// Pre-set bit 5 to be 1. The NES cpu does not use this bit and it supposed to be 1 at all times. 
	uint8_t stack_pointer = 255;

	// Counter for counting down cycles to next interrupt.
	int32_t interrupt_counter = INTERRUPT_CYCLES;
	uint16_t program_counter;

	uint8_t op_code;

	unsigned char* memory = new unsigned char[64*1024];

	void setFlag(char ch, uint8_t value) {
		switch (ch) {
		case ('n'):		// negative
			flags = changeBit(flags, 7, value);
			break;
		case ('v'):		// overflow
			flags = changeBit(flags, 6, value);
			break;
		case ('b'):		// break
			flags = changeBit(flags, 4, value);
			break;
		case ('d'):		// decimal mode (does nothing on the NES)
			flags = changeBit(flags, 3, value);
			break;
		case ('i'):		// interrupt disable
			flags = changeBit(flags, 2, value);
			break;
		case ('z'):		// zero
			flags = changeBit(flags, 1, value);
			break;
		case ('c'):		// carry
			flags =changeBit(flags, 0, value);
			break;
		}
	}

	uint8_t getFlag(char ch) {
		switch (ch) {
		case ('n'):		// negative
			return flags >> 7 & 1;
			break;
		case ('v'):		// overflow
			return flags >> 6 & 1;
			break;
		case ('b'):		// break
			return flags >> 4 & 1;
			break;
		case ('d'):		// decimal mode (does nothing on the NES)
			return flags >> 3 & 1;
			break;
		case ('i'):		// interrupt disable
			return flags >> 2 & 1;
			break;
		case ('z'):		// zero
			return flags >> 1 & 1;
			break;
		case ('c'):		// carry
			return flags >> 0 & 1;
			break;
		default:
			return 0;
		}
	}

	void tick() {
		// TODO: Tick PPU 3 times a cycle, APU once per cycle.
		for(int i = 0; i < 3; i++) {
			PPU::tick();
		}
		interrupt_counter--;
	}

	uint8_t readMemory(uint16_t address) {
		if (address == 0x2002) {
			//PPU::setFlag(2, 7, 0);
			return PPU::regs[2];
		}
		tick();
		return memory[address];
	}

	void writeMemory(uint16_t address, uint8_t value) {
		if(address >= 0x2000 && address <= 0x2007){
			PPU::regs[address & 0x7] = value;
			return;
		}
		memory[address] = value;
		tick();
	}

	void push(uint8_t reg) {
		writeMemory(0x0100 + stack_pointer--,reg);
	}

	uint8_t pull() {
		return readMemory(0x0100 + stack_pointer++);
	}

	void executeOp() {
			op_code = readMemory(program_counter++);
			uint16_t target;
			switch (op_code) {
			case (0x00):	// BRK TODO: tick()*3?
				program_counter += 1;
				push(program_counter);
				setFlag('b', 1);
				push(flags);
				setFlag('i', 1);
				tick();
				tick();
				tick();
				break;
			case (0x01):
				break;
			case (0x05):
				;
				break;
			case (0x06):
				;
				break;
			case (0x08):
				;
				break;
			case (0x09):
				;
				break;
			case (0x0A):	// ASL A
				setFlag('c', A & 0x80); // Check if highest bit is set and set carry flag if it is.
				A <<= 1;
				setFlag('n', A & 0x80); // Check highest bit to determine sign.
				setFlag('z', !A);
				tick();
				break;
			case (0x0D):
				;
				break;
			case (0x0E):
				;
				break;
			case (0x10):
				;
				break;
			case (0x11):
				;
				break;
			case (0x15):
				;
				break;
			case (0x16):
				;
				break;
			case (0x18):
				;
				break;
			case (0x19):
				;
				break;
			case (0x1D):
				;
				break;
			case (0x1E):
				;
				break;
			case (0x20):
				;
				break;
			case (0x21):
				;
				break;
			case (0x24):
				;
				break;
			case (0x25):
				;
				break;
			case (0x26):
				;
				break;
			case (0x28):
				;
				break;
			case (0x29):	// AND #value
				A = A & readMemory(program_counter++);
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick();
				break;
			case (0x2A):
				;
				break;
			case (0x2C):
				;
				break;
			case (0x2D):
				;
				break;
			case (0x2E):
				;
				break;
			case (0x30):
				;
				break;
			case (0x31):
				;
				break;
			case (0x35):
				;
				break;
			case (0x36):
				;
				break;
			case (0x38):
				;
				break;
			case (0x39):
				;
				break;
			case (0x3D):
				;
				break;
			case (0x3E):
				;
				break;
			case (0x40):
				;
				break;
			case (0x41):
				;
				break;
			case (0x45):
				;
				break;
			case (0x46):
				;
				break;
			case (0x48):
				;
				break;
			case (0x49):
				;
				break;
			case (0x4A):
				;
				break;
			case (0x4C):
				;
				break;
			case (0x4D):
				;
				break;
			case (0x4E):
				;
				break;
			case (0x50):
				;
				break;
			case (0x51):
				;
				break;
			case (0x55):
				;
				break;
			case (0x56):
				;
				break;
			case (0x58):
				;
				break;
			case (0x59):
				;
				break;
			case (0x5D):
				;
				break;
			case (0x5E):
				;
				break;
			case (0x60):
				;
				break;
			case (0x61):
				;
				break;
			case (0x65):
				;
				break;
			case (0x66):
				;
				break;
			case (0x68):
				;
				break;
			case (0x69):
				;
				break;
			case (0x6A):
				;
				break;
			case (0x6C):
				;
				break;
			case (0x6D):
				;
				break;
			case (0x6E):
				;
				break;
			case (0x70):
				;
				break;
			case (0x71):
				;
				break;
			case (0x75):
				;
				break;
			case (0x76):
				;
				break;
			case (0x78):	// SEI
				setFlag('i', 1);
				tick();
				break;
			case (0x79):
				;
				break;
			case (0x7D):
				;
				break;
			case (0x7E):
				;
				break;
			case (0x81):
				;
				break;
			case (0x84):	// STY $addr (zero page)
				writeMemory( 0x00FF & memory[program_counter++], Y);
				tick();
				break;
			case (0x85):
				;
				break;
			case (0x86):
				;
				break;
			case (0x88):	// DEY
				Y--;
				setFlag('n', Y & 0x80);
				setFlag('z', !Y);
				tick();
				break;
			case (0x8A):
				;
				break;
			case (0x8C):
				;
				break;
			case (0x8D):	// STA $addr (absolute)
				writeMemory( readMemory(program_counter) | (readMemory(program_counter + 1) << 8), A);
				program_counter += 2;
				break;
			case (0x8E):
				;
				break;
			case (0x90):
				;
				break;
			case (0x91):	// STA (indirect), Y
				writeMemory( ((0x00FF & readMemory(program_counter)) | (readMemory( (0x00FF & program_counter) + 1) << 8)) + Y, A);
				program_counter++;
				tick();
				tick();
				break;
			case (0x94):
				;
				break;
			case (0x95):
				;
				break;
			case (0x96):
				;
				break;
			case (0x98):
				;
				break;
			case (0x99):
				;
				break;
			case (0x9A):	// TXS
				stack_pointer = X;
				tick();
				break;
			case (0x9D):
				;
				break;
			case (0xA0):	// LDY #value
				Y = readMemory(program_counter++);
				setFlag('n', Y & 0x80);
				setFlag('z', !Y);
				break;
			case (0xA2):	// LDX #value
				X = readMemory(program_counter++);
				setFlag('n', X & 0x80);
				setFlag('z', !X);
				break;
			case (0xA9):	// LDA #value
				A = readMemory(program_counter++);
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				break;
			case (0xAD):	// LDA $addr (absolute)
				A = readMemory( readMemory(program_counter) | (readMemory(program_counter + 1) << 8) );
				program_counter += 2;
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				break;
			case (0xC8):	// INY
				Y++;
				setFlag('n', Y & 0x80);
				setFlag('z', !Y);
				tick();
				break;
			case (0xD0):	// BNE $addr (relative)
				target = program_counter + (int8_t)readMemory(program_counter);
				if (!getFlag('z')) {
					if((program_counter & 0xFF00) != (target & 0xFF00)){ // Check if page boundary if crossed and add a cycle if it is.
						tick();
					}
					tick();		// Add an extra cycle if branching.
					program_counter = target;
				}
				program_counter++;
				break;
			case (0xD8):	// CLD
				setFlag('d', 0);
				tick();
				break;
			case (0xE8):	// INX
				X++;
				setFlag('n', X & 0x80);
				setFlag('z', !X);
				tick();
				break;
			case (0xF0):	// BEQ $addr (relative)
				target = program_counter + (int8_t)readMemory(program_counter);
				if (getFlag('z')) {
					if((program_counter & 0xFF00) != (target & 0xFF00)){ // Check if page boundary if crossed and add a cycle if it is.
						tick();
					}
					tick();		// Add an extra cycle if branching.
					program_counter = target;
				}
				program_counter++;
				break;
			/*
			case (0x7E):
				;
				break;
			*/
			}
		}

	void printState() {
		std::cout << std::showbase << std::hex 
		<< "op: " << int(op_code) 
		<< ", A: " << int(A)
		<< ", X: " << int(X) 
		<< ", Y: " << int(Y) 
		<< std::dec
		<< " N: " << int(getFlag('n'))
		<< " V: " << int(getFlag('v'))
		<< " B: " << int(getFlag('b'))
		<< " D: " << int(getFlag('d'))
		<< " I: " << int(getFlag('i'))
		<< " Z: " << int(getFlag('z'))
		<< " C: " << int(getFlag('c'))
		<< std::hex
		<< ", SP: " << int(stack_pointer)
		<< ", PC: " << int(program_counter)
		<< ", interrupt_counter: " << std::dec << int(interrupt_counter);
		//<< " $2000: " << std::hex << int(memory[0x2000])
		//<< ", next_op: " << int(program_counter+1)
		//<< "\n";
	}
}

namespace PPU {
	uint8_t regs[8] = {0,0,0,0,0,0,0,0};
	int vblank_counter = 256 * 20;	// 20 scanlines worth of cycles.
	void setFlag(int reg, int bit, uint8_t value) {
		changeBit(regs[reg], bit, value);
		if(reg == 2 && bit == 7) {
			vblank_counter = 256 * 20;
		}
	}
	void tick() {
		vblank_counter--;
		if(vblank_counter < 0){
			changeBit(regs[2], 7, 0);
		}
	}
}

int main(int argc, char* argv[]) {

	if(argc < 2) {
		std::cout << "Usage: TeaNES <romfile>\n";
		return 1;
	}
	// TODO: Implement proper rom file header parsing.
	std::ifstream romfile(argv[1], std::ios::in|std::ios::binary|std::ios::ate);
	romfile.seekg(16);
	std::streampos size = 16*1024;
	romfile.read( (char*) CPU::memory+0xc000, size);
	romfile.close();

	// Initialize RAM like FCEUX does.
	for(int i = 0; i < 0x2000; i++) {
		CPU::memory[i] = (i % 4) < 2 ? 0x00 : 0xFF;
	}
	
	// Set PC to the reset address specified in the rom.
	CPU::program_counter = (CPU::memory[0xfffd] << 8) + CPU::memory[0xfffc];

	for(;;) {
		CPU::printState();
		CPU::executeOp();
		if(CPU::interrupt_counter <= 0) {
			CPU::interrupt_counter += INTERRUPT_CYCLES;
			std::cout << "\ninterrupt_counter <=0!";
		}
		std::cin.get();
	}
}