#ifndef FORWARDINGUNIT_H
#define FORWARDINGUNIT_H

class ForwardingUnit {
	friend class Machine;
public:
	ForwardingUnit();
	void run();
private:
	int* _exmem_reg_write;
	int* _exmem_rd;
	int* _idex_rs;
	int* _idex_rt;
	int* _memwb_reg_write;
	int* _memwb_rd;
	int forwardA_;
	int forwardB_;
};

ForwardingUnit::ForwardingUnit() : //初始化
	_exmem_reg_write(nullptr),
	_exmem_rd(nullptr),
	_idex_rs(nullptr),
	_idex_rt(nullptr),
	_memwb_reg_write(nullptr),
	_memwb_rd(nullptr),
	forwardA_(0),
	forwardB_(0)
{
}

inline void ForwardingUnit::run() //判斷是否有data hazard
{
	if (*_exmem_reg_write && (*_exmem_rd != 0) && (*_exmem_rd == *_idex_rs)) {
		forwardA_ = 0b10;
	}
	else if (*_memwb_reg_write && (*_memwb_rd != 0) && (*_memwb_rd == *_idex_rs)) {
		forwardA_ = 0b01;
	}
	else {
		forwardA_ = 0b00;
	}

	if (*_exmem_reg_write && (*_exmem_rd != 0) && (*_exmem_rd == *_idex_rt)) {
		forwardB_ = 0b10;
	}
	else if (*_memwb_reg_write && (*_memwb_rd != 0) && (*_memwb_rd == *_idex_rt)) {
		forwardB_ = 0b01;
	}
	else {
		forwardB_ = 0b00;
	}
}

#endif // !FORWARDINGUNIT_H
