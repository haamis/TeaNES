#include <iostream>
#include <fstream>
//#include <iomanip>
//#include <memory>
//#include <cstdint>
//#include <bitset>

#define INTERRUPT_CYCLES 512

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

void setFlag(char ch, uint8_t value) {
	switch (ch) {
	case ('n'):		// negative
		flags = flags & 0b01111111;		// First we clear the bit.
		flags = flags | value << 7;		// Then we set the approriate value.
		break;							// Not the most elegant solution.
	case ('v'):		// overflow
		flags = flags & 0b10111111;
		flags = flags | value << 6;
		break;
	case ('b'):		// break
		flags = flags & 0b11101111;
		flags = flags | value << 4;
		break;
	case ('d'):		// decimal mode (does nothing on the NES)
		flags = flags & 0b11110111;
		flags = flags | value << 3;
		break;
	case ('i'):		// interrupt disable
		flags = flags & 0b11111011;
		flags = flags | value << 2;
		break;
	case ('z'):		// zero
		flags = flags & 0b11111101;
		flags = flags | value << 1;
		break;
	case ('c'):		// carry
		flags = flags & 0b11111110;
		flags = flags | value << 0;
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

/*
uint8_t readMemory() {

}

void writeMemory() {

}
*/

void executeOp() {
		op_code = memory[program_counter++];
		uint16_t target;
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
			setFlag('n', A & 0x80);
			setFlag('z', !A);
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
		case (0x84):	// STY $addr (zero page)
			memory[ 0x00FF & memory[program_counter++] ] = Y;
			interrupt_counter -= 3;
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
			interrupt_counter -= 2;
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
		case (0x91):	// STA (indirect), Y
			memory[ ((0x00FF & memory[program_counter]) | (memory[ (0x00FF & program_counter) + 1] << 8)) + Y ] = A;
			program_counter++;
			interrupt_counter -= 6;
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
		case (0xA0):	// LDY #value
			Y = memory[program_counter++];
			setFlag('n', Y & 0x80);
			setFlag('z', !Y);
			interrupt_counter -= 2;
			break;
		case (0xA2):	// LDX #value
			X = memory[program_counter++];
			setFlag('n', X & 0x80);
			setFlag('z', !X);
			interrupt_counter -= 2;
			break;
		case (0xA9):	// LDA #value
			A = memory[program_counter++];
			setFlag('n', A & 0x80);
			setFlag('z', !A);
			interrupt_counter -= 2;
			break;
		case (0xAD):	// LDA $addr (absolute)
			A = memory[ memory[program_counter] | (memory[program_counter + 1] << 8) ];
			program_counter += 2;
			setFlag('n', A & 0x80);
			setFlag('z', !A);
			interrupt_counter -= 4;
			break;
		case (0xC8):	// INY
			Y++;
			setFlag('n', Y & 0x80);
			setFlag('z', !Y);
			interrupt_counter -= 2;
			break;
		case (0xD0):	// BNE $addr (relative)
			target = program_counter + (int8_t)memory[program_counter];
			program_counter++;
			if (!getFlag('z')) {
				if((program_counter & 0xFF00) != (target & 0xFF00)){ // Check if page boundary if crossed and add a cycle if it is.
					interrupt_counter -= 1;
				}
				interrupt_counter -= 1; // Add an extra cycle if branching.
				program_counter = target;
			}
			interrupt_counter -=2;
			break;
		case (0xD8):	// CLD
			setFlag('d', 0);
			interrupt_counter -= 2;
			break;
		case (0xE8):	// INX
			X++;
			setFlag('n', X & 0x80);
			setFlag('z', !X);
			interrupt_counter -= 2;
			break;
		case (0xF0):	// BEQ $addr (relative)
			target = program_counter + (int8_t)memory[program_counter];
			program_counter++;
			if (getFlag('z')) {
				if((program_counter & 0xFF00) != (target & 0xFF00)){ // Check if page boundary if crossed and add a cycle if it is.
					interrupt_counter -= 1;
				}
				interrupt_counter -= 1; // Add an extra cycle if branching.
				program_counter = target;
			}
			interrupt_counter -=2;
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

int main(int argc, char* argv[]) {

	if(argc < 2) {
		std::cout << "Usage: TeaNES <romfile>\n";
		return 1;
	}
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
			std::cout << "\ninterrupt_counter <=0!";
		}
		std::cin.get();
	}
}