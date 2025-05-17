#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

class InstructionMemory {
	friend class Machine;
public:
	InstructionMemory();
	void run();
private:
	int* _address;
	int instruction_;
	char inst_mem[65536];
};

InstructionMemory::InstructionMemory() : 
	_address(nullptr),
	instruction_(0),
	inst_mem{ 0 }
{}

inline void InstructionMemory::run() 
{
	instruction_ = *(int*)(void*)(inst_mem + *_address); //¨Ì·Óaddress§ì¨úinstruction
}

#endif // !INSTRUCTIONMEMORY_H
