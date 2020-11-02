#pragma once

#include <iostream>
using namespace std;

template <class T>
class TStack
{
private:
	T* mas;
	int size;
	int vs;
public:
	TStack();
	TStack(int _size);
	TStack(const TStack& other);
	~TStack();

	bool IsFull();
	bool IsEmpty();

	TStack<T>& operator = (TStack<T>& s);

	void push(T elem);
	T pull();

	void ReSize(int _size);
	int GetSize();
	int GetCount();

	T maximum();
	T elem(int index);
};

template<class T>
TStack<T>::TStack()
{
	size = 1;
	mas = new T[size];
	vs = -1;
}

template<class T>
inline TStack<T>::TStack(int _size)
{
	if (_size < 0) throw logic_error("invalid_argument");
	size = _size;
	mas = new T[size];

	vs = -1;
}

template<class T>
TStack<T>::TStack(const TStack& other)
{
	this->size = other.size;
	this->mas = new T[size];
	this->vs = other.vs;
	for (int i = 0; i < vs+1; i++)
		this->mas[i] = other.mas[i];
}

template<class T>
 TStack<T>::~TStack()
{
	 if (mas != 0)
		 delete[] mas;
}

 template<class T>
 inline bool TStack<T>::IsFull()
 {
	 if (vs + 1 >= size)
		 return true;
	 else return false;
 }

 template<class T>
 inline bool TStack<T>::IsEmpty()
 {
	 if (vs == -1) 
		 return true;
	 else return false;
 }

 template<class T>
 inline TStack<T>& TStack<T>::operator=(TStack<T>& s)
 {
	 if (this == &s)
		 return *this;

	 if (mas != 0)
		 delete[] mas;
	 this->size = s.size;
	 this->mas = new T [size];
	 this->vs = s.vs;
	 for (int i = 0; i < vs + 1; i++)
		 this->mas[i] = s.mas[i];

	 return *this;
 }

 template<class T>
 void TStack<T>::push(T elem)
 {
	 if (this->IsFull()) throw logic_error("out_of_range");
	 vs++;
	 mas[vs] = elem;
	 
 }

 template<class T>
T TStack<T>::pull()
 {
	if (this->IsEmpty()) throw logic_error("out_of_range");
	T result = mas[vs];
	vs--;
	 return result;
 }

template<class T>
inline void TStack<T>::ReSize(int _size)
{
	TStack<T> tmp_stack(_size);
	T tmp_elem;
	for (int i = 0; i < _size; i++)
	{
		if ((!(this->IsEmpty()))&& (!(tmp_stack.IsFull())))
		{
			tmp_elem = this->pull();
			tmp_stack.push(tmp_elem);
		}
	}
	TStack<T> tmp_stack2(_size);
	for (int i = 0; i < _size; i++)
	{
		if ((!(tmp_stack.IsEmpty())) && (!(tmp_stack2.IsFull())))
		{
			tmp_elem = tmp_stack.pull();
			tmp_stack2.push(tmp_elem);
		}
	}
	*this = tmp_stack2;
}

template<class T>
inline int TStack<T>::GetSize()
{
	return size;
}

template<class T>
inline int TStack<T>::GetCount()//кол-во элементов в стэке
{
	return vs+1;
}


template<class T>
inline T TStack<T>::maximum()
{
	if (this->IsEmpty()) throw logic_error("out_of_range");
	T max;
	T tmp;
	TStack <T> temp(*this);
	max = this->pull();
	while (!(this->IsEmpty()))
	{
		tmp = this->pull();
		if (max < tmp)
			max = tmp;
	}

	*this = temp;

	return max;
}

template<class T>
inline T TStack<T>::elem(int index)
{
	if (this->IsEmpty()) throw logic_error("out_of_range");
	if ((index>vs)||(index<0)) throw logic_error("invalid_argument");

	T result;
	TStack <T> temp(*this);

	for (int i = vs; i > index; i--)
	{
		this->pull();
	}

	result = this->pull();

	*this = temp;

	return result;
}


