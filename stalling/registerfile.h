#ifndef REGISTERFILE_H
#define REGISTERFILE_H

class RegisterFile {
	friend class Machine;
public:
	RegisterFile();
	void wbRun();
	void idRun();
private:
	int* _reg_write;
	int* _rs;
	int* _rt;
	int* _rwrite;
	int* _write_val;
	int data0_;
	int data1_;

	int reg[32];
};

RegisterFile::RegisterFile() :
	_reg_write(nullptr),
	_rs(nullptr),
	_rt(nullptr),
	_rwrite(nullptr),
	_write_val(nullptr),
	data0_(0),
	data1_(0)
{
	for (int i = 0; i < 32; ++i) { //初始化，所有reg[i] = 1
		reg[i] = !!i;
	}
}

inline void RegisterFile::wbRun() //WriteBack
{
	if (*_reg_write) {
		reg[*_rwrite] = *_write_val;
	}
	else {
		reg[*_rwrite] = reg[*_rwrite];
	}
}

inline void RegisterFile::idRun() //InstructionDecode
{
	data0_ = reg[*_rs];
	data1_ = reg[*_rt];
}

#endif // !REGISTERFILE_H
