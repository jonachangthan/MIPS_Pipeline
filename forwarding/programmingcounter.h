#ifndef PROGRAMMINGCOUNTER_H
#define PROGRAMMINGCOUNTER_H

class ProgrammingCounter {
	friend class Machine;
public:
	ProgrammingCounter();
	void run();
private:
	int* _stall;
	int* _nextpc;
	int pc_;
};

ProgrammingCounter::ProgrammingCounter() : //��l��
	_stall(nullptr),
	_nextpc(nullptr),
	pc_(0)
{}

inline void ProgrammingCounter::run() //PC�O�_�~�����
{
	if (*_stall) {
		pc_ = pc_;
	}
	else {
		pc_ = *_nextpc;
	}
}

#endif // !PROGRAMMINGCOUNTER_H
