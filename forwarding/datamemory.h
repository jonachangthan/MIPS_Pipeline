#ifndef DATAMEMORY_H
#define DATAMEMORY_H

class DataMemory {
	friend class Machine;
public:
	DataMemory();								//constructor
	void run();											//member function
private:													//data members
	int* _address;									//��}
	int* _write_val;									//�g�J����
	int* _mem_read;								//read signal
	int* _mem_write;								//write signal
	int memory_data_;							//Ū�X����

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
	if (*_mem_write) {																				// (sequential) �p�Gwrite control �O1
		*(int*)(mem + *_address) = *_write_val;									//�g�J���
	}
	else {																										//�_�h
		*(int*)(mem + *_address) = *(int*)(mem + *_address);			//��Ƥ���
	}

	if (*_mem_read) {																				// (sequential) �p�Gread control �O1
		memory_data_ = *(int*)(mem + *_address);						//�Nmemory���Ū�X��
	}
	else {																									//�_�h
		memory_data_ = memory_data_;											//data��Ƥ���
	}
}

#endif // !DATAMEMORY_H
