#ifndef DATAMEMORY_H
#define DATAMEMORY_H

class DataMemory {
	friend class Machine;
public:
	DataMemory();								//constructor
	void run();											//member function
private:													//data members
	int* _address;									//位址
	int* _write_val;									//寫入的值
	int* _mem_read;								//read signal
	int* _mem_write;								//write signal
	int memory_data_;							//讀出的值

	char mem[1024];								//memory
};

DataMemory::DataMemory() :			//initialization
	_address(nullptr),
	_write_val(nullptr),
	_mem_read(nullptr),
	_mem_write(nullptr),
	memory_data_(0),
	mem{ 0 }
{
	int* ptr = (int*)mem;
	for (int i = 0; i < 32; ++i) {
		*ptr++ = 1;
	}
}

inline void DataMemory::run()
{
	if (*_mem_write) {																				// (sequential) 如果write control 是1
		*(int*)(mem + *_address) = *_write_val;									//寫入資料
	}
	else {																										//否則
		*(int*)(mem + *_address) = *(int*)(mem + *_address);			//資料不變
	}

	if (*_mem_read) {																				// (sequential) 如果read control 是1
		memory_data_ = *(int*)(mem + *_address);						//將memory資料讀出來
	}
	else {																									//否則
		memory_data_ = memory_data_;											//data資料不變
	}
}

#endif // !DATAMEMORY_H
