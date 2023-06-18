#pragma once
#include <iostream>
#include <exception>

template <typename T>
class DynamicArray
{
protected:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const DynamicArray<T>& other);
	void moveFrom(DynamicArray<T>&&);

	void resize(size_t);
public:
	DynamicArray();

	DynamicArray(const DynamicArray<T>& other);
	DynamicArray(DynamicArray<T>&& other);

	DynamicArray<T>& operator=(const DynamicArray<T>& other);
	DynamicArray<T>& operator=(DynamicArray<T>&& other);

	void copyFromArray(const T* other, int size);
	void add(const T& obj);
	void remove(const T& obj);
	unsigned count(const T& obj) const; //count of obj
	unsigned count() const; //size of collection
	bool contains(const T& obj) const;
	DynamicArray<T>& keepUniqueElements();
	DynamicArray<T>& sort();
	DynamicArray<T> select(bool (*criteria)(const T& obj)); //set.select([](int i) { return i % 2 == 0; });
	void print() const;
	bool isEqualTo(const DynamicArray<T>& other);

	T& operator[](size_t index);
	T operator[](size_t index) const;
	DynamicArray<T>& operator+=(const DynamicArray<T>& other);

	~DynamicArray();
};

template<typename T>
bool DynamicArray<T>::isEqualTo(const DynamicArray<T>& other)
{
	for (size_t i = 0; i < size; i++)
	{
		if(data[i] != other.data[i])
			return false;
	}

	return true;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::keepUniqueElements()
{
	//sort data
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if (data[j] > data[j + 1]) {
				T temp = data[j + 1];
				data[j + 1] = data[j];
				data[j] = temp;
			}
		}
	}

	T* result = new T[size];
	result[0] = data[0];
	int ind = 1;

	for (size_t i = 1; i < size; i++)
	{
		if (data[i] == data[i - 1])
			continue;

		result[ind++] = data[i];
	}

	T* toCopy = new T[ind];
	for (size_t i = 0; i < ind; i++)
		toCopy[i] = result[i];

	delete[] result;
	delete[] data;
	data = toCopy;
	size = ind;

	return *this;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::select(bool (*criteria)(const T& obj))
{
	DynamicArray<T> result;
	for (size_t i = 0; i < size; i++)
		if (criteria(data[i]))
			result.add(data[i]);

	return result;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::sort()
{
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if (data[j] > data[j + 1]) {
				T temp = data[j + 1];
				data[j + 1] = data[j];
				data[j] = temp;
			}
		}
	}

	return *this;
}

template<typename T>
void DynamicArray<T>::copyFromArray(const T* other, int size)
{
	free();
	this->size = size;
	capacity = size * 2;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
		data[i] = other[i];
}

template<typename T>
void DynamicArray<T>::print() const
{
	for (int i = 0; i < size; ++i)
		std::cout << data[i] << " ";
	std::cout << std::endl;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const DynamicArray<T>& other)
{
	T* result = new T[(size + other.size)];
	for (size_t i = 0; i < size; i++)
		result[i] = this->data[i];


	for (size_t i = 0; i < other.size; i++)
		result[size + i] = other.data[i];

	size += other.size;
	delete[] data;
	data = result;

	return *this;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
T DynamicArray<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
unsigned DynamicArray<T>::count() const
{
	return size;
}

template <typename T>
void DynamicArray<T>::free()
{
	delete[] data;
}

template <typename T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

template <typename T>
void DynamicArray<T>::moveFrom(DynamicArray<T>&& other)
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
void DynamicArray<T>::resize(size_t nCap)
{
	T* newData = new T[nCap];

	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
	capacity = nCap;
}

template <typename T>
DynamicArray<T>::DynamicArray()
{
	size = 0;
	capacity = 8;

	data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
	copyFrom(other);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	free();
}

template <typename T>
void DynamicArray<T>::add(const T& obj)
{
	if (size == capacity)
	{
		resize(2 * size);
	}

	data[size++] = obj;
}

template <typename T>
void DynamicArray<T>::remove(const T& obj)
{
	int elemIndex = -1;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == obj)
		{
			elemIndex = i;
			break;
		}
	}

	if (elemIndex != -1)
	{
		std::swap(data[elemIndex], data[size - 1]);
		size--;
	}
}

template <typename T>
unsigned DynamicArray<T>::count(const T& obj) const
{
	unsigned elementCounter = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == obj)
		{
			++elementCounter;
		}
	}

	return elementCounter;
}

template <typename T>
bool DynamicArray<T>::contains(const T& obj) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == obj)
		{
			return true;
		}
	}
	return false;
}