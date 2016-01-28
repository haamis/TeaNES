#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>

//using namespace std;

// Declare CPU registers.
uint8_t a = 0;
uint8_t x = 0;
uint8_t y = 0;
uint8_t flags = 0;
uint8_t stack_pointer = 255;

// Counter for counting down cycles to next interrupt.
int32_t interrupt_counter = 512;

// TODO: Write proper logic for finding initial program counter value (reset vector apparently).
uint16_t program_counter = 0xC000;

uint8_t op_code;

char*  memory = new char[64*1024];

void executeOp() {
		op_code = memory[program_counter++];
		switch (op_code) {
		case (0x00):
			break;
		/*case (0x01):
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
		case (0x0A):
			;
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
	std::cout << std::hex << "op_code: " << int(op_code);
	std::cout << std::hex << ", A: " << int(a) << ", X: " << int(x) << ", Y: " << int(y) <<
	", flags: " << int(flags) << ", SP: " << std::hex << int(stack_pointer) << ", PC: " << 
	int(program_counter) << ", InterruptCounter: " << int(interrupt_counter) << "\n";
}

int main(int argc, char* argv[]) {

	std::ifstream romfile(argv[1], std::ios::in|std::ios::binary|std::ios::ate);
	romfile.seekg(16);
	std::streampos size = 16*1024;
	romfile.read(memory+0xc000, size);
	romfile.close();

	for(;;) {
		printState();
		executeOp();
		std::cin.get();
	}
}


