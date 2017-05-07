// $NAME <$ID@uakron.edu>

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "test.hpp"


template<typename T>
class vector
{
private:
	T* start;
	int size;

public:
	vector() { start = nullptr; size = 0; }
	~vector() { delete start; }
	int push_back(T frame);
	T pop();
	T operator[](int sub);

};

template <class T>
int vector::push_back(T frame)
{
	if (start == nullptr)
	{
		size++;
		start = new T;
		T[0] = frame;
		return size;
	}
	int n_size = size + 1;
	T* n_start = new T[n_size];
	for (int i = 0; i < size; i++)
	{
		n_start[i] = start[i];
	}
	n_start[size] = frame;
	delete start;
	start = n_start;
	size = n_size;
	return size;
}

template <class T>
T vector::pop()
{
	if (size == 0)
	{
		exit(0);
	}
	T ret = start[size - 1];
	int n_size = size - 1;
	T* n_start = new T[n_size];
	for (int i = 0; i < n_size; i++)
	{
		n_start[i] = start[i];
	}
	delete start;
	start = n_start;
	size = n_size;
	return ret;
}

template <class T>
T vector::operator[](int sub) const
{
	if (size == 0)
		exit(0);
	if (sub >= size)
		return start[size - 1];

	return start[sub];
}

template <class T>
T& vector::operator[](int sub)
{
	if (size == 0)
		exit(0);
	if (sub >= size)
		return start[size - 1];

	return start[sub];
}
#endif
