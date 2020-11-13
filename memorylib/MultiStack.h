#pragma once
#include "Stack.h"
#include <iostream>
#include <math.h>

using namespace std;

template <class T>
class TMultiStack
{
private:
	int size;
	int stack_count;
	TStack<T>* stacks;
	void StackRelocation(int index);

public:
	TMultiStack(int _size = 1, int _stack_count = 1);
	TMultiStack(const TMultiStack& other);
	~TMultiStack();

	bool IsFull(int i);
	bool IsEmpty(int i);

	TMultiStack<T>& operator = (TMultiStack<T>& s);

	void push(T elem, int i);
	T pull(int i);

	int stack_with_max_elem();
	void reverse();
};


template<class T>
inline TMultiStack<T>::TMultiStack(int _size, int _stack_count)
{
	if ((_size <= 0)|| (_stack_count <= 0)) throw logic_error("invalid_argument");
	if (_stack_count>_size) throw logic_error("invalid_argument");

	size = _size;
	stack_count = _stack_count;
	
	int count = int (floor ( double(size) / stack_count));
	int* sizes = new int[this->stack_count];
	for (int i = 0; i < (stack_count - 1); i++)
		sizes[i] = count;

	sizes[stack_count - 1] = size - count * (stack_count-1);

	this->stacks = new TStack<T>[stack_count];
	int k = 0;
	for (int i = 0; i < stack_count; i++)
	{
		TStack<T> tmp(sizes[i]);
		stacks[i] = tmp;
	}
	delete[] sizes;
}

template<class T>
TMultiStack<T>::TMultiStack(const TMultiStack& other)
{
	this->size = other.size;
	this->stack_count = other.stack_count;

	stacks = new TStack<T>[stack_count];
	for (int i = 0; i < stack_count; i++)
	{
		stacks[i] = other.stacks[i];
	}
}

template<class T>
 TMultiStack<T>::~TMultiStack()
{
	 if (stacks != 0)
		 delete[] stacks;
	 
	 stack_count = 0;
	 size = 0;
}

 template<class T>
 inline bool TMultiStack<T>::IsFull(int i)
 {
	 if ((i < 0) || (i >= stack_count)) throw logic_error("invalid_argument");
	 
	 return stacks[i].IsFull();
 }

 template<class T>
 inline bool TMultiStack<T>::IsEmpty(int i)
 {
	 if ((i < 0) || (i >= stack_count)) throw logic_error("invalid_argument");

	 return stacks[i].IsEmpty();
 }

 template<class T>
 inline TMultiStack<T>& TMultiStack<T>::operator=(TMultiStack<T>& s)
 {
	 if (this == &s)
		 return *this;

	 if (stacks != 0)
	 {
		 delete[] stacks;
	 }

	 this->size = s.size;
	 this->stack_count = s.stack_count;

	 this->stacks = new TStack<T>[stack_count];
	 for (int i = 0; i < stack_count; i++)
	 {
		 stacks[i] = s.stacks[i];
	 }

	 return *this;
 }

 template<class T>
 void TMultiStack<T>::push(T elem, int i)
 {
	 if ((i < 0) || (i >= stack_count)) throw logic_error("invalid_argument");

	 if (stacks[i].IsFull())
		this->StackRelocation(i);

	 stacks[i].push(elem);
 }

 template<class T>
T TMultiStack<T>::pull(int i)
 {
	if ((i < 0) || (i >= stack_count)) throw logic_error("invalid_argument");
	if (stacks[i].IsEmpty()) throw logic_error("out_of_range");

	T result = stacks[i].pull();
	 return result;
 }

template<class T>
inline int TMultiStack<T>::stack_with_max_elem()
{
	if (stack_count == 0) throw logic_error("out_of_range");
	T tmp;
	T max;
	int rezult;
	for (int i = 0; i < stack_count; i++)
	{
		for (int j = 0; j < stacks[i].GetCount(); j++)
		{
			tmp = this->pull(i);
			if ((i == 0) && (j == 0))
			{
				max = tmp;
				rezult = i;
			}
			else if (tmp > max)
			{
				max = tmp;
				rezult = i;
			}
		}
	}
	return rezult;
}

template<class T>
inline void TMultiStack<T>::reverse()
{
	TMultiStack<T> tmp (this->size, this->stack_count);
	TMultiStack<T> rezult(this->size, this->stack_count);
	int top;
	for (int i = 0; i < stack_count; i++)
	{
		top = stacks[i].GetCount();
		for (int j = 0; j < top; j++)
		{
			tmp.push(this->pull(i), i);
		}
		for (int j = 0; j < top; j++)
		{
			rezult.push(tmp.pull(i), stack_count - i - 1);
		}
	}
	*this = rezult;
}

template<class T>
inline void TMultiStack<T>::StackRelocation(int index)
{
	int free_size = 0;
	for (int i = 0; i < stack_count; i++)
		free_size += stacks[i].GetSize() - stacks[i].GetCount();

	if (free_size == 0) throw logic_error("out_of_range");

	int count = int(floor(double(free_size) / stack_count));
	int* sizes = new int[this->stack_count];
	for (int i = 0; i < stack_count; i++)
		sizes[i] = stacks[i].GetCount() + count;

	sizes[index] = sizes[index] + free_size - count * stack_count;


	for (int i = 0; i < stack_count; i++)
		stacks[i].ReSize(sizes[i]);

	delete[] sizes;
}