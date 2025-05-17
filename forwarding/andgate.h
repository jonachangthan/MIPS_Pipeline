#ifndef ANDGATE_H
#define ANDGATE_H

class AndGate {
	friend class Machine;
public:
	AndGate();							//constructor
	void run();								//member function
private:										//data member
	int* _input0;							//operand0
	int* _input1;							//operand1
	int output_;							//result
};

AndGate::AndGate() :				//initialization
	_input0(nullptr),
	_input1(nullptr),
	output_(0)
{}

inline void AndGate::run()			//execute AND
{
	output_ = *_input0 && *_input1;
}

#endif // !ANDGATE_H
