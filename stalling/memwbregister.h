#ifndef MEMWBREGISTER_H
#define MEMWBREGISTER_H

class MEMWBRegister {
	friend class Machine;
public:
	MEMWBRegister();
	void run();
private:
	int* _reg_write;
	int* _mem_to_reg;
	int* _memory_data;
	int* _alu_result;
	int* _rwrite;
	int reg_write_;
	int mem_to_reg_;
	int memory_data_;
	int alu_result_;
	int rwrite_;
};

MEMWBRegister::MEMWBRegister() :
	_reg_write(nullptr),
	_mem_to_reg(nullptr),
	_memory_data(nullptr),
	_alu_result(nullptr),
	_rwrite(nullptr),
	reg_write_(0),
	mem_to_reg_(0),
	memory_data_(0),
	alu_result_(0),
	rwrite_(0)
{}

inline void MEMWBRegister::run() //MEM to WB
{
	reg_write_ = *_reg_write;
	mem_to_reg_ = *_mem_to_reg;
	memory_data_ = *_memory_data;
	alu_result_ = *_alu_result;
	rwrite_ = *_rwrite;
}

#endif // !MEMWBREGISTER_H
