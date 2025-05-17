#ifndef SHIFTLEFT2UNIT_H
#define SHIFTLEFT2UNIT_H

class ShiftLeft2Unit {
	friend class Machine;
public:
	ShiftLeft2Unit();
	void run();
private:
	int* _input;
	int output_;
};

ShiftLeft2Unit::ShiftLeft2Unit() : //初始化
	_input(nullptr),
	output_(0)
{}

inline void ShiftLeft2Unit::run() //向左移2個bits(乘4)
{
	output_ = *_input * 4;
}

#endif // !SHIFTLEFT2UNIT_H
