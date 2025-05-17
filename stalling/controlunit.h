#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

class ControlUnit {
	friend class Machine;
public:
	ControlUnit();									//constructor
	void run();											//member function
private:													//data member
	struct bit {
		unsigned int _0 : 1;
		unsigned int _1 : 1;
		unsigned int _2 : 1;
		unsigned int _3 : 1;
		unsigned int _4 : 1;
		unsigned int _5 : 1;
		unsigned int _6 : 1;
		unsigned int _7 : 1;
	};
	int* _stall;
	int* _opcode;
	int control_signal_;
};

ControlUnit::ControlUnit() :			//initialization
	_stall(nullptr),
	_opcode(nullptr),
	control_signal_(0)
{}

inline void ControlUnit::run()		//推出control signal
{
	bit opcode = *(bit*)_opcode;

	if (_stall && *_stall) {			//如果是stall
		control_signal_ = 0;		//signal為0
	}
	else {										//input的opcode對應到每個元件的control 0/1 (Truth Table in P.35)
		control_signal_ = 
			((int)(!opcode._5) << 8) | // RegDst
			((int)(!opcode._5 && !opcode._2) << 7) | // ALUop1
			((int)opcode._2 << 6) | // ALUop0
			((int)opcode._0 << 5) | // ALUSrc
			((int)opcode._2 << 4) | // Branch
			((int)((!opcode._3) && opcode._0) << 3) | // MemRead
			((int)opcode._3 << 2) | // MemWrite
			((int)(!(opcode._3 || opcode._2)) << 1) | // RegWrite
			((int)opcode._0); // MemtoReg
	}
}

#endif // !CONTROLUNIT_H
