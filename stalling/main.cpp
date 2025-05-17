#include"machine.h"
#pragma warning(disable:6262)

int main() {
	Machine m;
	m.assembler("memory.txt");
	m.run();
	return 0;
}