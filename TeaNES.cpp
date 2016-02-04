#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>
#include <cstdint>

#define INTERRUPT_CYCLES 512

//using namespace std;

// Declare CPU registers.
uint8_t a = 0;
uint8_t x = 0;
uint8_t y = 0;

struct flags_t {
	bool n;		// negative
	bool v;		// overflow
	bool b;		// break
	bool d;		// decimal mode
	bool i;		// interrupt disable
	bool z;		// zero
	bool c;		// carry
} flags;
//bool flags[] = {0,0,0,0,0,0,0,0};

uint8_t stack_pointer = 255;

// Counter for counting down cycles to next interrupt.
int32_t interrupt_counter = INTERRUPT_CYCLES;

uint16_t program_counter;

uint8_t op_code;

unsigned char*  memory = new unsigned char[64*1024];

void executeOp() {
		op_code = memory[program_counter++];
		switch (op_code) {
		case (0x00):
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
			a = a << 1;
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
		case (0x29):
			;
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
		case (0x78):
			;
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
		case (0x8D):
			;
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
		case (0x9A):
			;
			break;
		case (0x9D):
			;
			break;
		case (0xE8):	// INX
			x++;
			interrupt_counter -= 2;
			break;
		case (0xC8):	// INY
			y++;
			interrupt_counter -= 2;
			break;
		/*
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;
		case (0x7E):
			;
			break;

		*/
		}
	}

void printState() {
	std::cout << std::showbase << std::hex << "op_code: " << int(op_code) << ", A: " << int(a)
	<< ", X: " << int(x) << ", Y: " << int(y) << ", flags: " << "N: " << flags.n << " V: " << flags.v
	<< " B: " << flags.b << " D: " << flags.d << " I: " << flags.i << " Z: " << flags.z << " C: "
	<< flags.c << ", SP: " << int(stack_pointer) << ", PC: " << int(program_counter) 
	<< ", interrupt_counter: " << std::dec << int(interrupt_counter) << "\n";
}

int main(int argc, char* argv[]) {

	std::ifstream romfile(argv[1], std::ios::in|std::ios::binary|std::ios::ate);
	romfile.seekg(16);
	std::streampos size = 16*1024;
	romfile.read( (char*) memory+0xc000, size);
	romfile.close();
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