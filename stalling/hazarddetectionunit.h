#ifndef HAZARDDECTIONUNIT_H
#define HAZARDDECTIONUNIT_H

class HazardDetectionUnit {
	friend class Machine;
public:
	HazardDetectionUnit();
	void run();
private:
	int* _idex_mem_read;
	int* _idex_rt;
	int* _ifid_rs;
	int* _ifid_rt;
	int* _idex_reg_write;
	int* _idex_rd;
	int* _exmem_reg_write;
	int* _exmem_rwrite;
	int stall_;
};

HazardDetectionUnit::HazardDetectionUnit() :
	_idex_mem_read(nullptr),
	_idex_rt(nullptr),
	_ifid_rs(nullptr),
	_ifid_rt(nullptr),
	_idex_reg_write(nullptr),
	_idex_rd(nullptr),
	_exmem_reg_write(nullptr),
	_exmem_rwrite(nullptr),
	stall_(0)
{}

inline void HazardDetectionUnit::run()			//檢測是否有hazard，如果有 => 要stall
{
	stall_ =
		(*_idex_mem_read && ((*_idex_rt == *_ifid_rs) || (*_idex_rt == *_ifid_rt))) ||																					
		(*_idex_reg_write && (*_idex_rd != 0) && ((*_idex_rd == *_ifid_rs) || (*_idex_rd == *_ifid_rt))) ||											
		(*_exmem_reg_write && (*_exmem_rwrite != 0) && ((*_exmem_rwrite == *_ifid_rs) || (*_exmem_rwrite == *_ifid_rt)));
}

#endif // !HAZARDDECTIONUNIT_H
