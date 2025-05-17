#ifndef SIGNEXTENDUNIT_H
#define SIGNEXTENDUNIT_H

class SignExtendUnit {
	friend class Machine;
public:
	SignExtendUnit();
	void run();
private:
	int* _input;
	int output_;
};

SignExtendUnit::SignExtendUnit() :
	_input(nullptr),
	output_(0)
{}

inline void SignExtendUnit::run()
{
	output_ = (int)*(short*)_input;
}
#endif // !SIGNEXTENDUNIT_H
