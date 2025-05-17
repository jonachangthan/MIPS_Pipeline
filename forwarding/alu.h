#ifndef ALU_H
#define ALU_H

class ALU {
	friend class Machine;
public:
	ALU();										//constructor
	void run();								//member function
private:
	int* _operand0;					//運算元0
	int* _operand1;					//運算元1
	int* _operatoion;					//運算方式
	int result_;								//運算結果
	int zero_;								//Zero Flag (如果result為0 =>1 ；反之 => 1)
};

ALU::ALU() :								//initialization
	_operand0(nullptr),
	_operand1(nullptr),
	_operatoion(nullptr),
	result_(0),
	zero_(0)
{}

inline void ALU::run()				//execute operatoion
{
	switch (*_operatoion) {
	case 0b0000: // and
		result_ = *_operand0 & *_operand1;
		break;
	case 0b0001: // or
		result_ = *_operand0 | *_operand1;
		break;
	case 0b0010: // add
		result_ = *_operand0 + *_operand1;
		break;
	case 0b0110: // substruct
		result_ = *_operand0 - *_operand1;
		break;
	case 0b0111: // set-on-less-than
		result_ = *_operand0 < *_operand1;
		break;
	case 0b1100: // nor
		result_ = !(*_operand0 | *_operand1);
		break;
	}
	zero_ = (result_ == 0);		//Zero Flag
}

#endif // !ALU_H
