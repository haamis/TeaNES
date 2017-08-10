#include <iostream>
#include <fstream>
#include "TeaNES.h"

// Helper function to change a certain bit in an 8-bit register.
uint8_t changeBit (uint8_t byte, int bit, bool value) {
	byte = byte & (0xFF ^ (1 << bit));	// First we clear the bit.
	byte = byte | value << bit;			// Then we set the approriate value.
	return byte;						// Not the most elegant solution.
}

namespace CPU {

#define INTERRUPT_CYCLES 512

	// Declare CPU registers.
	uint8_t A = 0;
	uint8_t X = 0;
	uint8_t Y = 0;
	uint8_t flags = 0x34;			// Set flags to power-up state (from nesdev.com). 
	uint8_t stack_pointer = 0xFD;

	// Counter for counting down cycles to next interrupt.
	int32_t interrupt_counter = INTERRUPT_CYCLES;
	uint16_t program_counter;

	uint8_t op_code;

	uint8_t memory[2 * 1024];

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
			flags = changeBit(flags, 0, value);
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

	void tick(int ticks) {
		for (int i = 0; i < ticks; i++) {
			// TODO: Tick PPU 3 times a cycle, APU once per cycle.
			for (int j = 0; j < 3; j++) {
				PPU::tick();
			}
		}
		interrupt_counter -= ticks;
	}

	uint8_t readMemory(uint16_t address) {
		if (address <= 0x1FFF) {
			return memory[address % 0x800];
		}
		if (address >= 0x2000 && address <= 0x3FFF) {
			if (address == 0x2002) {
				PPU::setFlag(2, 7, 0);
			}
			return PPU::regs[address % 8];
		}
		if (address >= 0x4000 && address <= 0x4017) {
			std::cout << "Unimplemented APU read.";
			return 0x77;
		}
		if (address >= 0x8000 && address <= 0xFFFF) {
			return Cart::PRG_ROM[address % 0x8000];
		}
		
		std::cout << "Unhandled memory read.";
		return 0x77;
	}

	void writeMemory(uint16_t address, uint8_t value) {
		if (address <= 0x1FFF) {
			memory[address % 0x800] = value;
		}
		if (address >= 0x2000 && address <= 0x2007) {
			PPU::regs[address & 0x7] = value;
			return;
		}
		if (address >= 0x4000 && address <= 0x4017) {
			std::cout << "Unimplemented APU write.";
		}
		std::cout << "Unhandled memory write.";
	}

	void push(uint8_t reg) {
		writeMemory(0x0100 + stack_pointer--,reg);
	}

	uint8_t pull() {
		return readMemory(0x0100 + stack_pointer++);
	}

	void executeOp() {
			op_code = readMemory(program_counter++);
			switch (op_code) {

			case (0x00):	// BRK
				if(!getFlag('i')){
					program_counter++;
					push((program_counter >> 8) & 0xFF);
					push(program_counter & 0xFF);
					setFlag('b', 1);
					push(flags);
					setFlag('i', 1);
					program_counter = readMemory(0xFFFE) | (readMemory(0xFFFF) << 8);
					tick(7);
				}
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
				tick(2);
				break;

			case (0x0D):
				;
				break;
			case (0x0E):
				;
				break;

			// TODO: is this even correct?
			case (0x10):	// BPL $addr (relative)
				{
				uint16_t target = program_counter + (int8_t)readMemory(program_counter);
				if (!getFlag('n')) {
					tick(1);		// Add an extra cycle if branching.
					if((program_counter & 0xFF00) != (target & 0xFF00)) { // Check if page boundary is crossed and add a cycle if it is.
						tick(1);
					}
					program_counter = target;
				}
				program_counter++;
				tick(2);
				}
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

			case (0x18):	// CLC
				setFlag('c', 0);
				tick(2);
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

			case (0x20):	// JSR $addr
				push((program_counter >> 8) & 0xff);
				push((program_counter) & 0xff);
				program_counter = readMemory(program_counter) | (readMemory(program_counter + 1) << 8);
				tick(6);
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
				tick(2);
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

			case (0x38):	// SEC
				setFlag('c', 1);
				tick(2);
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

			case (0x4D):	// RTI
				flags = pull();
				program_counter = pull();
				program_counter += (pull() << 8) + 1;
				tick(6);
				break;

			case (0x41):
				;
				break;

			case (0x45):	// EOR $addr (zero page)
				A = readMemory(readMemory(program_counter++) ^ A);
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(3);
				break;

			case (0x46):
				;
				break;

			case (0x48):	// PHA
				push(flags);
				tick(3);
				break;

			case (0x49):	// EOR #value
				A = readMemory(program_counter++) ^ A;
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(2);
				break;

			case (0x4A):
				;
				break;

			case (0x4C):	// JMP $addr1 $addr2 (absolute)
				program_counter = readMemory(program_counter) | (readMemory(program_counter + 1) << 8);
				tick(3);
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

			case (0x60):	// RTS
				program_counter = pull();
				program_counter += (pull() << 8) + 1;
				tick(6);
				break;

			case (0x61):
				;
				break;

			case (0x65):
				;
				break;

			case (0x66):	// ROR $addr (zero page)
				{
					uint8_t temp = readMemory(program_counter);
					setFlag('c', temp & 1);
					temp = temp >> 1;
					temp = temp | 0x80;
					setFlag('n', temp & 0x80);
					setFlag('z', !temp);
					writeMemory(readMemory(program_counter++), temp);
					tick(5);
				}
				break;

			case (0x68):	// PLA
				flags = pull();
				tick(4);
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
				tick(2);
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
				writeMemory(0x00FF & memory[program_counter++], Y);
				tick(3);
				break;

			case (0x85):	// STA $addr (zero page)
				writeMemory(0x00FF & memory[program_counter++], A);
				tick(3);
				break;

			case (0x86):
				;
				break;

			case (0x88):	// DEY
				Y--;
				setFlag('n', Y & 0x80);
				setFlag('z', !Y);
				tick(2);
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
				tick(4);
				break;

			case (0x8E):
				;
				break;

			case (0x90):
				;
				break;
			case (0x91):	// STA (indirect), Y	TODO: FIX THIS
				writeMemory( (readMemory(readMemory(program_counter)) | (readMemory(readMemory(program_counter) + 1) << 8)) + Y, A);
				program_counter++;
				tick(6);
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
				tick(2);
				break;

			case (0x9D):
				;
				break;

			case (0xA0):	// LDY #value
				Y = readMemory(program_counter++);
				setFlag('n', Y & 0x80);
				setFlag('z', !Y);
				tick(2);
				break;

			case (0xA2):	// LDX #value
				X = readMemory(program_counter++);
				setFlag('n', X & 0x80);
				setFlag('z', !X);
				tick(2);
				break;

			case (0xA5):	//LDA $addr (zero page)
				A = readMemory(0x00FF & readMemory(program_counter++));
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(3);
				break;

			case (0xA9):	// LDA #value
				A = readMemory(program_counter++);
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(2);
				break;

			case (0xAA):	// TAX
				X = A;
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(2);
				break;

			case (0xAD):	// LDA $addr (absolute)
				A = readMemory( readMemory(program_counter) | (readMemory(program_counter + 1) << 8) );
				program_counter += 2;
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(4);
				break;

			case (0xAE):	// LDX $addr (absolute)
				X = readMemory( readMemory(program_counter) | (readMemory(program_counter + 1) << 8) );
				program_counter += 2;
				setFlag('n', X & 0x80);
				setFlag('z', !X);
				tick(4);
				break;

			case (0xB1):	// LDA (indirect), Y
				{
				uint8_t operand = readMemory(program_counter);
				uint16_t target = (readMemory(operand) | (readMemory(operand + 1) << 8)) + Y;
				if ((program_counter & 0xFF00) != (target & 0xFF00)) { // Check if page boundary is crossed and add a cycle if it is.
					tick(1);
				}
				A = readMemory(target);
				program_counter++;
				tick(5);
				}
				break;

			case (0xBD):	// LDA $addr,X (absolute,X)
				{
				uint16_t target = (readMemory(program_counter) | (readMemory(program_counter + 1) << 8)) + X;
				if((program_counter & 0xFF00) != (target & 0xFF00)) { // Check if page boundary is crossed and add a cycle if it is.
					tick(1);
				}
				A = readMemory(target);
				program_counter += 2;
				setFlag('n', A & 0x80);
				setFlag('z', !A);
				tick(4);
				}
				break;

			case (0xC6):	// DEC zero page
				{
				uint8_t temp = readMemory(readMemory(program_counter));
				temp--;
				writeMemory(readMemory(program_counter), temp);
				setFlag('n', temp & 0x80);
				setFlag('z', !temp);
				tick(5);
				}
				break;

			case (0xC8):	// INY
				Y++;
				setFlag('n', Y & 0x80);
				setFlag('z', !Y);
				tick(2);
				break;

			case (0xC9):	// CMP #value
				{
				uint8_t temp = readMemory(program_counter++);
				temp = A - temp;
				setFlag('c', A < temp);
				setFlag('n', temp & 0x80);
				setFlag('z', !temp);
				tick(2);
				}
				break;

			case (0xCE):	// DEC $addr (absolute)
				{
				uint8_t temp = readMemory( readMemory(program_counter) | readMemory(program_counter + 1) );
				temp--;
				writeMemory(readMemory(program_counter), temp);
				setFlag('n', temp & 0x80);
				setFlag('z', !temp);
				tick(6);
				}
				break;

			case (0xD0):	// BNE $addr (relative)
				{
				uint16_t target = program_counter + (int8_t)readMemory(program_counter);
				if (!getFlag('z')) {
					tick(1);		// Add an extra cycle if branching.
					if((program_counter & 0xFF00) != (target & 0xFF00)) { // Check if page boundary if crossed and add a cycle if it is.
						tick(1);
					}
					program_counter = target;
				}
				program_counter++;
				tick(2);
				}
				break;

			case (0xD8):	// CLD
				setFlag('d', 0);
				tick(2);
				break;

			case (0xE8):	// INX
				X++;
				setFlag('n', X & 0x80);
				setFlag('z', !X);
				tick(2);
				break;

			case (0xF0):	// BEQ $addr (relative)
				{
				uint16_t target = program_counter + (int8_t)readMemory(program_counter);
				if (getFlag('z')) {
					if((program_counter & 0xFF00) != (target & 0xFF00)) { // Check if page boundary if crossed and add a cycle if it is.
						tick(1);
					}
					tick(1);		// Add an extra cycle if branching.
					program_counter = target;
				}
				program_counter++;
				tick(2);
				}
				break;
			/*
			case (0x7E):
				;
				break;
			*/
			//default:
				//std::cout << "Unsupported op!";
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
	uint8_t regs[8] = {0,0,0b10000000,0,0,0,0,0};
	uint8_t secondary_OAM[4];
	uint8_t OAM[64*4];
	uint8_t scanline_counter = 0;
	unsigned int frame_counter = 0;
	//? uint8_t vblank_counter = 256 * 20;	// 20 scanlines worth of cycles.
	void setFlag(int reg, int bit, uint8_t value) { 
		changeBit(regs[reg], bit, value);
		/*if(reg == 2 && bit == 7) {
			vblank_counter = 256 * 20;
		}*/
	}
	void tick() {
		/*
		vblank_counter--;
		if(vblank_counter < 0){
			changeBit(regs[2], 7, 0);
		}
		*/
	}
}

namespace Cart {
	uint8_t PRG_ROM[32 * 1024];
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
	romfile.read((char*)Cart::PRG_ROM+0x4000, size);
	romfile.close();

	// Initialize RAM like FCEUX does.
	for(int i = 0; i < 0x2000; i++) {
		CPU::memory[i] = (i % 4) < 2 ? 0x00 : 0xFF;
	}
	
	// Set PC to the reset address specified in the rom.
	CPU::program_counter = (Cart::PRG_ROM[0x7ffd] << 8) + Cart::PRG_ROM[0x7ffc];

	for(;;) {
		CPU::printState();
		CPU::executeOp();
		if(CPU::interrupt_counter <= 0) {
			CPU::interrupt_counter += INTERRUPT_CYCLES;
			std::cout << "\ninterrupt_counter <=0!";
		}
		//if(CPU::op_code == 0xC6){
			std::cin.get();
		//}
	}
}
