#ifndef ADDER_H
#define ADDER_H
#include"machine.h"
class Adder {
	friend class Machine;
public:
	Adder(); //constructor
	void run(); //member function
private:
	int* _operand0; //�Q�[��
	int* _operand1; //�[��
	int result_; //�p�⵲�G
};

Adder::Adder() : //initialization
	_operand0(nullptr),
	_operand1(nullptr),
	result_(0)
{}

inline void Adder::run() //execute adding
{
	result_ = *_operand0 + *_operand1;
}

#endif // !ADDER_H
