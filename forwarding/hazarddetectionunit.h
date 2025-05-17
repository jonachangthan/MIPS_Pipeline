#ifndef HAZARDDECTIONUNIT_H
#define HAZARDDECTIONUNIT_H

class HazardDetectionUnit {
	friend class Machine;
public:
	HazardDetectionUnit();
	void run();
private:
	int* _idex_mem_read; // id_ex ªº memory_read signal
	int* _idex_rt;
	int* _ifid_rs;
	int* _ifid_rt;
	int stall_;
};

HazardDetectionUnit::HazardDetectionUnit() :
	_idex_mem_read(nullptr),
	_idex_rt(nullptr),
	_ifid_rs(nullptr),
	_ifid_rt(nullptr),
	stall_(0)
{}

inline void HazardDetectionUnit::run()
{
	stall_ = *_idex_mem_read && ((*_idex_rt == *_ifid_rs) || (*_idex_rt == *_ifid_rt)); //§PÂ_data hazard
}

#endif // !HAZARDDECTIONUNIT_H
