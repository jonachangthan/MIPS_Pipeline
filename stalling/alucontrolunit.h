#ifndef ALUCONTROLUNIT_H
#define ALUCONTROLUNIT_H

class ALUControlUnit {
	friend class Machine;
public:
	ALUControlUnit();						//constructor
	void run();										//member function
private:												//data member
	struct bit {
		int _0 : 1;
		int _1 : 1;
		int _2 : 1;
		int _3 : 1;
		int _4 : 1;
		int _5 : 1;
		int _6 : 1;
		int _7 : 1;
	};
	int* _aluop;
	int* _funct;
	int operation_;
};

ALUControlUnit::ALUControlUnit() :			//initialization
	_aluop(nullptr),
	_funct(nullptr),
	operation_(0)
{}

inline void ALUControlUnit::run()
{
	bit aluop = *(bit*)(void*)_aluop, funct = *(bit*)(void*)_funct;

	//K map 求出 ALU要執行的operation
	operation_ =
		0 << 3 | // operation3
		((aluop._0 || (aluop._1 && funct._1)) << 2) | // operation2
		(((!aluop._1) || (!funct._2)) << 1) | // operation1
		(aluop._1 && (funct._0 || funct._3)); // operation0 
}

#endif // !ALUCONTROLUNIT_H
