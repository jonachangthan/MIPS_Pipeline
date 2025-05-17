#ifndef IFIDREGISTER_H
#define IFIDREGISTER_H

union instruction
{
	unsigned int code_;
	struct {
		unsigned int funct_ : 6; // [0:5]
		unsigned int shamt_ : 5; // [6:10]
		unsigned int rd_ : 5;	// [11:15]
		unsigned int rt_ : 5;	// [16:20]
		unsigned int rs_ : 5;	// [21:25]
		unsigned int opcode_ : 6;// [26:31]
	};
	struct {
		unsigned int immed_ : 16;
		unsigned int : 5;
		unsigned int : 5;
		unsigned int : 6;
	};
};

class IFIDRegister {
	friend class Machine;
public:
	IFIDRegister();
	void run();
private:
	int* _stall;
	int* _flush;
	int* _pc;
	int* _instruction;
	int pc_;
	int opcode_;
	int rs_;
	int rt_;
	int rd_;
	int immed_;
};

IFIDRegister::IFIDRegister() :
	_stall(nullptr),
	_flush(nullptr),
	_pc(nullptr),
	_instruction(nullptr),
	pc_(0),
	opcode_(0),
	rs_(0),
	rt_(0),
	rd_(0),
	immed_(0)
{}

inline void IFIDRegister::run()
{
	instruction inst = *(instruction*)_instruction;
	if (_stall && *_stall) { //�O�_data hazard�A�O:reset
		pc_ = 0;
		opcode_ = 0;
		rs_ = 0;
		rt_ = 0;
		rd_ = 0;
		immed_ = 0;
	}
	else { //�N���O����� pc , opcode , rs , rt , rd ,immed
		pc_ = *_pc;
		opcode_ = inst.opcode_;
		rs_ = inst.rs_;
		rt_ = inst.rt_;
		rd_ = inst.rd_;
		immed_ = inst.immed_;
	}

	if (*_flush) { //�O�_branch�A�O:reset
		pc_ = 0;
		opcode_ = 0;
		rs_ = 0;
		rt_ = 0;
		rd_ = 0;
		immed_ = 0;
	}
	else { //�קKlatch
		pc_ = pc_;
		opcode_ = opcode_;
		rs_ = rs_;
		rt_ = rt_;
		rd_ = rd_;
		immed_ = immed_;
	}
}

#endif // !IFIDREGISTER_H
