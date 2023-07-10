#include <iostream>


template <class T>
class DinamicArray {

private:
	size_t size;	// Размер массива
	size_t sizeUse; // Количество задействованных ячеек
	T	   *array;

public:
	DinamicArray();
	~DinamicArray();

	void add(T value);	// Добавить/удалить элемент из массива
	void delValue(T value); // Удаление по значению
	void del(int index);
	void clear();
	size_t getSize();	// Получить размер массива
	size_t getSizeUse();
	int findValue(T value); // Ищет элемент и возврашает id, иначе -1.
	
	T& operator[](const int index); // Обращение к элементу без проверки
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


template <class T> // редактировать: создать смещение массива... подумать...
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
void DinamicArray<T>::del(int index) { //Тут ошибки. Проверить!
	if ((index > -1) && (index < size)) {
		array[index] = T();
		sizeUse--;
	}

	else {
		std::cerr << "Ошибка в функции DinamicArray::del()";
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

		std::cerr << "Ошибка удаления массива.";
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
			
			if (checkUseEl == sizeUse) { // Элементы закончились
				return -1;
			}
		}
	}

	return index-1; //-1 т.к. особенность в итераторе ++;
}


template <class T>
T& DinamicArray<T>::operator[](const int index) {
	return array[index];
}