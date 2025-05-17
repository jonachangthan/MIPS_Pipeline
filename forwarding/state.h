#pragma once
#ifndef _STATE_H
#define _STATE_H
#pragma warning(disable:26812)

class State {
	friend class Machine;
public:
	enum Value : char  //pipeline 的stage
	{
		IF,
		ID,
		EX,
		MEM,
		WB,
		END
	};
	State(); 
	State(Value value);
	State(const State& other);
	bool operator == (Value value) const;
	bool operator == (const State& other) const;
	operator int() const;
	char toNext();
private:
	Value value_;
};


State::State() :   //IF為初始state
	value_(State::IF)
{}


inline State::State(Value value) :
	value_(value)
{}

inline State::State(const State& other) :
	value_(other.value_)
{}

inline bool State::operator==(Value value) const
{
	return this->value_ == value;
}

inline bool State::operator==(const State& other) const
{
	return this->value_ == other.value_;
}

inline State::operator int() const
{
	return this->value_;
}

inline char State::toNext() //下一個State
{
	return ++ * (char*)&(this->value_);
}

#endif // !_STATE_H
