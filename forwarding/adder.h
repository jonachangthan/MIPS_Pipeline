#ifndef ADDER_H
#define ADDER_H
#include"machine.h"
class Adder {
	friend class Machine;
public:
	Adder(); //constructor
	void run(); //member function
private:
	int* _operand0; //被加數
	int* _operand1; //加數
	int result_; //計算結果
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
