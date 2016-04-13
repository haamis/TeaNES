#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>
#include <cstdint>

#include <bitset>

#define INTERRUPT_CYCLES 512

//using namespace std;

// Declare CPU registers.
uint8_t A = 0;
uint8_t X = 0;
uint8_t Y = 0;
uint8_t flags = 0;

uint8_t stack_pointer = 255;

// Counter for counting down cycles to next interrupt.
int32_t interrupt_counter = INTERRUPT_CYCLES;

uint16_t program_counter;

uint8_t op_code;

unsigned char* memory = new unsigned char[64*1024];

void setFlag(char ch, uint8_t v) {
	switch (ch) {
	case ('n'):		// negative
		flags = flags | v << 7;
		break;
	case ('v'):		// overflow
		flags = flags | v << 6;
		break;
	case ('b'):		// break
		flags = flags | v << 4;
		break;
	case ('d'):		// decimal mode (does nothing on the NES)
		flags = flags | v << 3;
		break;
	case ('i'):		// interrupt disable
		flags = flags | v << 2;
		break;
	case ('z'):		// zero
		flags = flags | v << 1;
		break;
	case ('c'):		// carry
		flags = flags | v << 0;
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

void push(uint8_t reg) {
	memory[0x0100 + stack_pointer--] = reg;
 }

uint8_t pull() {
	return memory[0x0100 + stack_pointer++];
}

void executeOp() {
		op_code = memory[program_counter++];
		switch (op_code) {
		case (0x00):	// BRK
			program_counter += 1;
			push(program_counter);
			setFlag('b', 1);
			push(flags);
			setFlag('i', 1);
			interrupt_counter -= 7;
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
			interrupt_counter -= 2;
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
			A = A & memory[program_counter++];
			interrupt_counter -= 2;
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
			interrupt_counter -= 2;
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
		case (0x84):
			;
			break;
		case (0x85):
			;
			break;
		case (0x86):
			;
			break;
		case (0x88):
			;
			break;
		case (0x8A):
			;
			break;
		case (0x8C):
			;
			break;
		case (0x8D):	// STA $addr (absolute)
			memory[ memory[program_counter] | (memory[program_counter + 1] << 8) ] = A;
			program_counter += 2;
			interrupt_counter -= 4;
			break;
		case (0x8E):
			;
			break;
		case (0x90):
			;
			break;
		case (0x91):
			;
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
			interrupt_counter -= 2;
			break;
		case (0x9D):
			;
			break;
		case (0xA2):	// LDX #value
			X = memory[program_counter++];
			interrupt_counter -= 2;
			break;
		case (0xA9):	// LDA #value
			A = memory[program_counter++];
			interrupt_counter -= 2;
			break;
		case (0xAD):	// LDA $addr (absolute)
			A = memory[ memory[program_counter] | (memory[program_counter + 1] << 8) ];
			program_counter += 2;
			interrupt_counter -= 4;
			break;
		case (0xC8):	// INY
			Y++;
			interrupt_counter -= 2;
			break;
		case (0xD8):	// CLD
			setFlag('d', 0);
			interrupt_counter -= 2;
			break;
		case (0xE8):	// INX
			X++;
			interrupt_counter -= 2;
			break;
		case (0xF0):	// BEQ $addr (relative)
			if (getFlag('z')) {
				
			}
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
	<< ", interrupt_counter: " << std::dec << int(interrupt_counter)
	//<< " $2000: " << std::hex << int(memory[0x2000])
	//<< ", next_op: " << int(program_counter+1)
	<< "\n";
}

int main(int argc, char* argv[]) {


	// TODO: Implement proper rom file header parsing.
	std::ifstream romfile(argv[1], std::ios::in|std::ios::binary|std::ios::ate);
	romfile.seekg(16);
	std::streampos size = 16*1024;
	romfile.read( (char*) memory+0xc000, size);
	romfile.close();
	
	// Set PC to the reset address specified in the rom.
	program_counter = (memory[0xfffd] << 8) + memory[0xfffc];

	for(;;) {
		printState();
		executeOp();
		if(interrupt_counter <= 0) {
			interrupt_counter += INTERRUPT_CYCLES;
			std::cout << "interrupt_counter <=0!" << '\n';
		}
		std::cin.get();
	}
}