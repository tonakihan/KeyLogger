#include <iostream>


template <class T>
class DinamicArray {

private:
	size_t size;	// ������ �������
	size_t sizeUse; // ���������� ��������������� �����
	T	   *array;

public:
	DinamicArray();
	~DinamicArray();

	void add(T value);	// ��������/������� ������� �� �������
	void delValue(T value); // �������� �� ��������
	void del(int index);
	void clear();
	size_t getSize();	// �������� ������ �������
	size_t getSizeUse();
	int findValue(T value); // ���� ������� � ���������� id, ����� -1.
	
	T& operator[](const int index); // ��������� � �������� ��� ��������
};


template <class T>
DinamicArray<T>::DinamicArray() {
	size = 0;
	sizeUse = 0;
	array = nullptr;
}


template <class T>
DinamicArray<T>::~DinamicArray() {
	if (array != nullptr)
		delete array;
}


template <class T>
void DinamicArray<T>::add(T value) {
	
	if (sizeUse == size) {

		size++;
		T* tempSave = array;

		array = new T[size]();

		if (tempSave != nullptr) {

			for (size_t i = 0; i < size-1; i++) {
				array[i] = tempSave[i];
			}

			delete tempSave;
		}

		array[size-1] = value;
	}

	else {

		for (size_t i = 0; i < size; i++) {
			if (array[i] == T()) {
				array[i] = value;
			}
		}
	}

	sizeUse++;
}


template <class T> // �������������: ������� �������� �������... ��������...
void DinamicArray<T>::delValue(T value) {
	for (size_t i = 0; i < size; i++) {
		if (array[i] == value) {
			array[i] = T();
			break;
		}
	}

	sizeUse--;
}


template <class T>
void DinamicArray<T>::del(int index) { //��� ������. ���������!
	if ((index > -1) && (index < size)) {
		array[index] = T();
		sizeUse--;
	}

	else {
		std::cerr << "������ � ������� DinamicArray::del()";
		return;
	}
}



template <class T>
size_t DinamicArray<T>::getSize() {
	return size;
}


template <class T>
size_t DinamicArray<T>::getSizeUse() {
	return sizeUse;
}


template <class T>
void DinamicArray<T>::clear() {
	if (array != nullptr)
		delete array;
	
	else {

		std::cerr << "������ �������� �������.";
		exit(-1);
	}
}


template <class T>
int DinamicArray<T>::findValue(T value) {

	size_t checkUseEl{};
	int index;

	if (sizeUse == 0) {
		return -1;
	}

	for (index = 0; index < size; index++) {

		if (array[index] != T()) {

			checkUseEl++;

			if (array[index] == value) {
				return index;
			}
			
			if (checkUseEl == sizeUse) { // �������� �����������
				return -1;
			}
		}
	}

	return index-1; //-1 �.�. ����������� � ��������� ++;
}


template <class T>
T& DinamicArray<T>::operator[](const int index) {
	return array[index];
}