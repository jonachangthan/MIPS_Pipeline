#ifndef MUX_H
#define MUX_H

class Mux { //2to1¦h¤u¾¹
	friend class Machine;
public:
	Mux();
	void run();
private:
	int* _select;
	int* _input0;
	int* _input1;
	int output_;
};

Mux::Mux() :
	_select(nullptr),
	_input0(nullptr),
	_input1(nullptr),
	output_(0)
{}

inline void Mux::run()
{
	if (*_select) {
		output_ = *_input1;
	}
	else {
		output_ = *_input0;
	}
}
#endif // !MUX_H
