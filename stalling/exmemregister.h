#ifndef EXMEMREGISTER_H
#define EXMEMREGISTER_H

class EXMEMRegister {
	friend class Machine;
public:
	EXMEMRegister();
	void run();
private:								//儲存MEM、WB stage所需的資料
	int* _branch;
	int* _mem_read;
	int* _mem_write;
	int* _reg_write;
	int* _mem_to_reg;
	int* _pc;
	int* _zero;
	int* _alu_result;
	int* _data1;
	int* _rwrite;
	int branch_;
	int mem_read_;
	int mem_write_;
	int reg_write_;
	int mem_to_reg_;
	int pc_;
	int zero_;
	int alu_result_;
	int data1_;
	int rwrite_;
};

EXMEMRegister::EXMEMRegister() :
	_branch(nullptr),
	_mem_read(nullptr),
	_mem_write(nullptr),
	_reg_write(nullptr),
	_mem_to_reg(nullptr),
	_pc(nullptr),
	_zero(nullptr),
	_alu_result(nullptr),
	_data1(nullptr),
	_rwrite(nullptr),
	branch_(0), 
	mem_read_(0),
	mem_write_(0),
	reg_write_(0),
	mem_to_reg_(0),
	pc_(0),
	zero_(0),
	alu_result_(0),
	data1_(0),
	rwrite_(0)
{}

inline void EXMEMRegister::run()
{
	branch_ = *_branch;
	mem_read_ = *_mem_read;
	mem_write_ = *_mem_write;
	reg_write_ = *_reg_write;
	mem_to_reg_ = *_mem_to_reg;
	pc_ = *_pc;
	zero_ = *_zero;
	alu_result_ = *_alu_result;
	data1_ = *_data1;
	rwrite_ = *_rwrite;
}

#endif // !EXMEMREGISTER_H
