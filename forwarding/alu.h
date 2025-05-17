#ifndef ALU_H
#define ALU_H

class ALU {
	friend class Machine;
public:
	ALU();										//constructor
	void run();								//member function
private:
	int* _operand0;					//�B�⤸0
	int* _operand1;					//�B�⤸1
	int* _operatoion;					//�B��覡
	int result_;								//�B�⵲�G
	int zero_;								//Zero Flag (�p�Gresult��0 =>1 �F�Ϥ� => 1)
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
