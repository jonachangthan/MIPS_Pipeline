#ifndef MACHINE_H
#define MACHINE_H
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<vector>
#include<unordered_map>
#include<iostream>
#include"adder.h"
#include"alu.h"
#include"alucontrolunit.h"
#include"andgate.h"
#include"controlunit.h"
#include"datamemory.h"
#include"exmemregister.h"
#include"forwardingunit.h"
#include"hazarddetectionunit.h"
#include"idexregister.h"
#include"ifidregister.h"
#include"instructionmemory.h"
#include"instructionno.h"
#include"memwbregister.h"
#include"mux.h"
#include"mux3.h"
#include"programmingcounter.h"
#include"registerfile.h"
#include"shiftleft2unit.h"
#include"signextendunit.h"
#include"state.h"


bool isEmpty(std::vector<std::pair<InstructionNo, State>>& pipes);

class Machine {
public:
	Machine();
	void assembler(const char* filename);
	void run();
private:
	void IFstage();
	void IDstage();
	void EXstage();
	void MEMstage();
	void WBstage();
	int runCycle(FILE* fp);
	void outputPipes(std::vector<std::pair<InstructionNo, State>>& pipe, FILE* fp);
	void outputPipe(InstructionNo inst_no, State state, FILE* fp);
	void (Machine::* stageFunction[5])();
	int readInstruction(FILE* file_ptr);
	int getNextInteger(FILE* fptr);
	Adder pc_4_adder;
	Adder pc_immed_adder;
	ALU alu;
	ALUControlUnit alu_controller;
	AndGate andgate;
	ControlUnit controller;
	DataMemory datamemory;
	EXMEMRegister exmem;
	ForwardingUnit forwarding;
	HazardDetectionUnit hazarddetection;
	IDEXRegister idex;
	IFIDRegister ifid;
	InstructionMemory instructmemory;
	MEMWBRegister memwb;
	Mux pc_src;
	Mux controller_src;
	Mux alu_operator1_rt_immed;
	Mux rwrite_src;
	Mux write_src;
	Mux3 alu_operand0_src;
	Mux3 alu_operand1_src;
	ProgrammingCounter programmingcounter;
	RegisterFile registerfile;
	ShiftLeft2Unit shiftleft2unit;
	SignExtendUnit signextendunit;
};

Machine::Machine() : //���u
	stageFunction{ &Machine::IFstage , &Machine::IDstage , &Machine::EXstage, &Machine::MEMstage, &Machine::WBstage }
{
	pc_4_adder._operand0 = &programmingcounter.pc_;
	pc_4_adder._operand1 = new int(4);

	pc_immed_adder._operand0 = &ifid.pc_;
	pc_immed_adder._operand1 = &shiftleft2unit.output_;

	alu._operand0 = &alu_operand0_src.output_;
	alu._operand1 = &alu_operator1_rt_immed.output_;
	alu._operatoion = &alu_controller.operation_;

	alu_controller._aluop = &idex.aluop_;
	alu_controller._funct = &idex.funct_;

	andgate._input0 = &exmem.branch_;
	andgate._input1 = &alu.zero_;

	controller._opcode = &ifid.opcode_;

	datamemory._address = &exmem.alu_result_;
	datamemory._mem_read = &exmem.mem_read_;
	datamemory._mem_write = &exmem.mem_write_;
	datamemory._write_val = &exmem.data1_;

	exmem._alu_result = &alu.result_;
	exmem._branch = &idex.branch_;
	exmem._data1 = &alu_operand1_src.output_;
	exmem._pc = &pc_immed_adder.result_;
	exmem._mem_read = &idex.mem_read_;
	exmem._mem_to_reg = &idex.mem_to_reg_;
	exmem._mem_write = &idex.mem_write_;
	exmem._reg_write = &idex.reg_write_;
	exmem._rwrite = &rwrite_src.output_;
	exmem._zero = &alu.zero_;

	forwarding._exmem_rd = &exmem.rwrite_;
	forwarding._exmem_reg_write = &exmem.reg_write_;
	forwarding._idex_rs = &idex.rs_;
	forwarding._idex_rt = &idex.rt_;
	forwarding._memwb_rd = &memwb.rwrite_;
	forwarding._memwb_reg_write = &memwb.reg_write_;

	hazarddetection._idex_mem_read = &idex.mem_read_;
	hazarddetection._idex_rt = &idex.rt_;
	hazarddetection._ifid_rs = &ifid.rs_;
	hazarddetection._ifid_rt = &ifid.rt_;

	idex._control_signal = &controller_src.output_;
	idex._data0 = &registerfile.data0_;
	idex._data1 = &registerfile.data1_;
	idex._flush = &andgate.output_;
	idex._immed = &signextendunit.output_;
	idex._rd = &ifid.rd_;
	idex._rt = &ifid.rt_;
	idex._rs = &ifid.rs_;

	ifid._instruction = &instructmemory.instruction_;
	ifid._pc = &pc_4_adder.result_;
	ifid._flush = &andgate.output_;
	ifid._stall = &hazarddetection.stall_;

	instructmemory._address = &programmingcounter.pc_;

	memwb._alu_result = &exmem.alu_result_;
	memwb._memory_data = &datamemory.memory_data_;
	memwb._mem_to_reg = &exmem.mem_to_reg_;
	memwb._reg_write = &exmem.reg_write_;
	memwb._rwrite = &exmem.rwrite_;

	pc_src._input0 = &pc_4_adder.result_;
	pc_src._input1 = &exmem.pc_;
	pc_src._select = &andgate.output_;

	controller_src._input0 = &controller.control_signal_;
	controller_src._input1 = new int(0);
	controller_src._select = &hazarddetection.stall_;

	alu_operator1_rt_immed._input0 = &alu_operand1_src.output_;
	alu_operator1_rt_immed._input1 = &idex.immed_;
	alu_operator1_rt_immed._select = &idex.alusrc_;

	rwrite_src._input0 = &idex.rt_;
	rwrite_src._input1 = &idex.rd_;
	rwrite_src._select = &idex.regdst_;

	write_src._input0 = &memwb.alu_result_;
	write_src._input1 = &memwb.memory_data_;
	write_src._select = &memwb.mem_to_reg_;

	alu_operand0_src._input0 = &idex.data0_;
	alu_operand0_src._input1 = &write_src.output_;
	alu_operand0_src._input2 = &exmem.alu_result_;
	alu_operand0_src._select = &forwarding.forwardA_;

	alu_operand1_src._input0 = &idex.data1_;
	alu_operand1_src._input1 = &write_src.output_;
	alu_operand1_src._input2 = &exmem.alu_result_;
	alu_operand1_src._select = &forwarding.forwardB_;

	programmingcounter._nextpc = &pc_src.output_;
	programmingcounter._stall = &hazarddetection.stall_;

	registerfile._reg_write = &memwb.reg_write_;
	registerfile._rs = &ifid.rs_;
	registerfile._rt = &ifid.rt_;
	registerfile._rwrite = &memwb.rwrite_;
	registerfile._write_val = &write_src.output_;

	shiftleft2unit._input = &idex.immed_;

	signextendunit._input = &ifid.immed_;
}

inline void Machine::assembler(const char* filename) //�}��r��Ū���O�A���O������5�ӥ�0�����O(NOP)
{
	FILE* fptr = fopen(filename, "r");
	int* instruction_ptr = (int*)(void*)instructmemory.inst_mem;
	do {
		*instruction_ptr = readInstruction(fptr);
	} while (*instruction_ptr++ != 0);
	*instruction_ptr++ = 0;
	*instruction_ptr++ = 0;
	*instruction_ptr++ = 0;
	*instruction_ptr++ = 0;
	fclose(fptr);
}

inline void Machine::run() //Ū�ɫ�run cycle
{
	FILE* fp = fopen("result.txt", "w+");
	int cycle = runCycle(fp);
	fprintf(fp, "\nIt takes %d cycles.\n\n", cycle); //��X���
	for (int i = 0; i < 32; ++i) {
		fprintf(fp, "$%d  ", i);
	}
	fprintf(fp, "\n");
	for (int i = 0; i < 32; ++i) {
		fprintf(fp, "%d   ", registerfile.reg[i]);
	}
	fprintf(fp, "\n");
	for (int i = 0; i < 32; ++i) {
		fprintf(fp, "W%d  ", i);
	}
	fprintf(fp, "\n");
	for (int i = 0; i < 32; ++i) {
		fprintf(fp, "%d   ", ((int*)(void*)datamemory.mem)[i]);
	}
	fclose(fp);
}

inline void Machine::IFstage() //����IFstate
{
	pc_src.run();
	programmingcounter.run();
	instructmemory.run();
	pc_4_adder.run();
}

inline void Machine::IDstage() //����IDstate
{
	ifid.run();
	hazarddetection.run();
	ifid.run();
	signextendunit.run();
	controller.run();
	controller_src.run();
	registerfile.idRun();
}

inline void Machine::EXstage() //����EXstate
{
	idex.run();
	shiftleft2unit.run();
	pc_immed_adder.run();
	rwrite_src.run();
	forwarding.run();
	alu_operand0_src.run();
	alu_operand1_src.run();
	alu_operator1_rt_immed.run();
	alu_controller.run();
	alu.run();

}

inline void Machine::MEMstage() //����MEMstate
{
	exmem.run();
	andgate.run();
	datamemory.run();
}

inline void Machine::WBstage() //����WBstate
{
	memwb.run();
	write_src.run();
	registerfile.wbRun();
}

inline int Machine::runCycle(FILE* fp)
{
	std::vector<std::pair<InstructionNo, State>> pipe; //�q���������O�H�Τǰt�쪺state
	int count = 1;
	do {
		WBstage();
		MEMstage();
		EXstage();
		IDstage();
		IFstage();

		InstructionNo curr; //�{�b�����O
		unsigned int opcode = *(unsigned int*)&instructmemory.instruction_ >> 26; //��opcode
		if (opcode == 0b100011) {
			curr = InstructionNo::LW;
		}
		else if (opcode == 0b101011) {
			curr = InstructionNo::SW;
		}
		else if (opcode == 0b000100) {
			curr = InstructionNo::BEQ;
		}
		else {
			switch (instructmemory.instruction_ & 0b111111) {
			case 0:
				curr = InstructionNo::NOP;
				break;
			case 0b100000:
				curr = InstructionNo::ADD;
				break;
			case 0b100010:
				curr = InstructionNo::SUB;
				break;
			}
		}
		pipe.push_back({ curr, State::IF }); //��i�@�}�l�����O��state

		fprintf(fp, "Cycle %d\n", count++);
		outputPipes(pipe, fp);
		fprintf(fp, "\n\n");
	} while (isEmpty(pipe));
	return count - 1;
}

inline void Machine::outputPipes(std::vector<std::pair<InstructionNo, State>>& pipe, FILE* fp)
{
	for (auto it = pipe.begin(); it != pipe.end();) { //
		if ((it->second == State::ID && *ifid._flush) || (it->second == State::ID && *ifid._stall) || (it->second == State::EX && *idex._flush)) { //��o�Ǫ��p�o�͡AinstructionNo��NOP
			it->first = InstructionNo::NOP;
		}
		outputPipe(it->first, it->second, fp); //��X���O��state
		it->second.toNext(); //�U�@��stage
		if (it->second == State::END) { //WB�U�@�ӬOEND�A�OEND�Npipe�N�M��it�Ait���s�}�l
			pipe.erase(it);
			it = pipe.begin();
		}
		else { //��LState�h�~��i��
			++it;
		}
	}
}

inline void Machine::outputPipe(InstructionNo inst_no, State state, FILE* fp) //��X���O��state
{
	static  std::unordered_map<InstructionNo, const char*> mp
	{
		{InstructionNo::ADD, "add"},
		{InstructionNo::SUB, "sub"},
		{InstructionNo::LW, "lw"},
		{InstructionNo::SW, "sw"},
		{InstructionNo::BEQ, "beq"},
		{InstructionNo::NOP, "nop"},
	};
	const char* s = mp[inst_no];
	switch (state)
	{
	case State::IF:
		fprintf(fp, "%s: IF\n", s);
		break;
	case State::ID:
		fprintf(fp, "%s: ID\n", s);
		break;
	case State::EX:
		fprintf(fp, "%s: EX %c%c %c%c%c %c%c\n", s, ((int)inst_no > 2 ? 'x' : idex.regdst_ + '0'), idex.alusrc_ + '0', idex.branch_ + '0', idex.mem_read_ + '0', idex.mem_write_ + '0', idex.reg_write_ + '0', ((int)inst_no > 2 ? 'x' : idex.mem_to_reg_ + '0'));
		break;
	case State::MEM:
		fprintf(fp, "%s: MEM %c%c%c %c%c\n", s, exmem.branch_ + '0', exmem.mem_read_ + '0', exmem.mem_write_ + '0', exmem.reg_write_ + '0', ((int)inst_no > 2 ? 'x' : exmem.mem_to_reg_ + '0'));
		break;
	case State::WB:
		fprintf(fp, "%s: WB %c%c\n", s, memwb.reg_write_ + '0', ((int)inst_no > 2 ? 'x' : memwb.mem_to_reg_ + '0'));
		break;
	default:
		break;
	}
}

inline int Machine::readInstruction(FILE* fptr) //Ū����r�ɪ����O
{
	static std::unordered_map<const char*, int>instruction_map
	{
		{ "add", 0b000000'00000'00000'00000'00000'100000 },
		{ "sub", 0b000000'00000'00000'00000'00000'100010 },
		{ "lw",  0b100011'00000'00000'0000000000000000 },
		{ "sw",  0b101011'00000'00000'0000000000000000 },
		{ "beq", 0b000100'00000'00000'0000000000000000 },
	};
	static char readbuf[5];
	if (fscanf(fptr, "%s", readbuf) == EOF) {
		return 0;
	}
	instruction ret;
	ret.code_ = 0;
	for (auto it : instruction_map) {
		if (!strcmp(readbuf, it.first)) {
			ret.code_ = it.second;
			break;
		}
	}
	if (ret.opcode_ == 0b000100) {
		ret.rs_ = this->getNextInteger(fptr);
		ret.rt_ = this->getNextInteger(fptr);
		ret.immed_ = this->getNextInteger(fptr);
	}
	else if (ret.opcode_) {
		ret.rt_ = this->getNextInteger(fptr);
		ret.immed_ = this->getNextInteger(fptr);
		ret.rs_ = this->getNextInteger(fptr);
	}
	else {
		ret.rd_ = this->getNextInteger(fptr);
		ret.rs_ = this->getNextInteger(fptr);
		ret.rt_ = this->getNextInteger(fptr);
	}
	return ret.code_;
}

inline int Machine::getNextInteger(FILE* fptr)  //Ū�����O��������ഫ���Ʀr
{
	int ret = 0;
	bool neg = false;
	char readch = 0;
	while (!isdigit(readch = fgetc(fptr)) && readch != '-');
	if (readch == '-') {
		neg = true;
		readch = fgetc(fptr);
	}
	do {
		ret = ret * 10 + readch - '0';
	} while (isdigit(readch = fgetc(fptr)));
	return neg ? -ret : ret;
}


inline bool isEmpty(std::vector<std::pair<InstructionNo, State>>& pipes)
{
	for (auto p : pipes) {
		if (p.first != InstructionNo::NOP) {
			return true;
		}
	}
	return false;
}
#endif // !MACHINE_H