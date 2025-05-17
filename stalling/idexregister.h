#ifndef IDEXREGISTER_H
#define IDEXREGISTER_H

class IDEXRegister {
	friend class Machine;
public:
	IDEXRegister();
	void run();
private:
	int* _flush;
	int* _control_signal;
	int* _data0;
	int* _data1;
	int* _immed;
	int* _rs;
	int* _rt;
	int* _rd;
	int regdst_;
	int aluop_;
	int alusrc_;
	int branch_;
	int mem_read_;
	int mem_write_;
	int reg_write_;
	int mem_to_reg_;
	int data0_;
	int data1_;
	int immed_;
	int rs_;
	int rt_;
	int rd_;
	int funct_;

};

IDEXRegister::IDEXRegister() :
	_flush(nullptr),
	_control_signal(nullptr),
	_data0(nullptr),
	_data1(nullptr),
	_immed(nullptr),
	_rs(nullptr),
	_rt(nullptr),
	_rd(nullptr),
	regdst_(0),
	aluop_(0),
	alusrc_(0),
	branch_(0),
	mem_read_(0),
	mem_write_(0),
	reg_write_(0),
	mem_to_reg_(0),
	data0_(0),
	data1_(0),
	immed_(0),
	rs_(0),
	rt_(0),
	rd_(0),
	funct_(0)
{}

inline void IDEXRegister::run()
{
	if (*_flush) { //是否branch，是flush
		regdst_ = 0;
		aluop_ = 0;
		alusrc_ = 0;
		branch_ = 0;
		mem_read_ = 0;
		mem_write_ = 0;
		reg_write_ = 0;
		mem_to_reg_ = 0;
		data0_ = 0;
		data1_ = 0;
		immed_ = 0;
		rs_ = 0;
		rt_ = 0;
		rd_ = 0;
		funct_ = 0;
	}
	else { //將所有資料組成完整的instruction
		regdst_ = (*_control_signal & 0b100000000) >> 8;
		aluop_ = (*_control_signal & 0b011000000) >> 6;
		alusrc_ = (*_control_signal & 0b000100000) >> 5;
		branch_ = (*_control_signal & 0b000010000) >> 4;
		mem_read_ = (*_control_signal & 0b000001000) >> 3;
		mem_write_ = (*_control_signal & 0b000000100) >> 2;
		reg_write_ = (*_control_signal & 0b000000010) >> 1;
		mem_to_reg_ = (*_control_signal & 0b000000001);
		data0_ = *_data0;
		data1_ = *_data1;
		immed_ = *_immed;
		rs_ = *_rs;
		rt_ = *_rt;
		rd_ = *_rd;
		funct_ = *_immed & 0b111111;
	}
}

#endif // ! IDEXREGISTER_H