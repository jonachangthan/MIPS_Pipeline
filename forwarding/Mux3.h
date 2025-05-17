#ifndef MUX3_H
#define MUX3_H

class Mux3 {   //3to1¦h¤u¾¹
	friend class Machine;
public:
	Mux3();
	void run();
private:
	int* _input0;
	int* _input1;
	int* _input2;
	int* _select;
	int output_;
};

Mux3::Mux3() :
	_input0(nullptr),
	_input1(nullptr),
	_input2(nullptr),
	_select(nullptr),
	output_(0)
{}

inline void Mux3::run()
{
	switch (*_select)
	{
	case 0:
		output_ = *_input0;
		break;
	case 1:
		output_ = *_input1;
		break;
	case 2:
		output_ = *_input2;
		break;
	}
}

#endif // !MUX3_H
