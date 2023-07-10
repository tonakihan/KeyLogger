#include <ctime>
#include <iostream>


template <class T>
class List {

private:

	class Node {

	public:
		unsigned int tClock; // result run function Clock()
		Node* pNext;
		Node* pBack;
		T	  data;

		Node(T data = T(), Node* crrNode = nullptr, Node* follNode = nullptr) {

			tClock = clock();
			this->data = data;
			this->pNext = crrNode;
			this->pBack = follNode;
		}
	};


	int  size;
	Node* head;

	void clear();					// Удаление списка полностью 
	bool findElement(T data, Node*& current); // Поиск элемента

public:
	List();
	~List();

	bool findElement(T data);		// Костыль
	void removeAt(T data);			// Удаление элемента по данным кнопки(клавиатуры)
	void append(T data);			// Добавить данные в конец списка
	int GetSize();					// Получить размер списка
	unsigned int GetClock(T data); 	// Получение времени (и удаление после)

	T& operator[](const int index);
};





	// -------------PUBLIC FUNCTION-------------

template <class T>
T& List<T>::operator[](const int index) {

	if ((index > size) && (index < 0)) {
		std::cerr << "Ошибка! List::operator[] принял не существующее значение";
		system("pause");
		exit(1);
	}

	Node* current = head;
	for (int i = 0; i < index - 1; i++) {
		current = current->pNext;
	}
	return current->data;
}


template <class T>
bool List<T>::findElement(T data) {

	Node* ptrFromFind = head;
	return findElement(data, ptrFromFind);
}


template <class T>
unsigned int List<T>::GetClock(T data) {

	Node* current = head;

	if (findElement(data, current)) {

		unsigned int temp = clock() - current->tClock;
		removeAt(data);
		return temp; // время нажатия
	}

	std::cerr << "Ошибка в функции List::GetClock(" << data << ")." << std::endl;
	exit(3);
}


template <class T>
void List<T>::append(T data) {

	if (head == nullptr) {
		head = new Node(data);
		size++;
	}

	else {

		Node* current = head;
		if (!findElement(data, current)) {

			current->pNext = new Node(data, current);
			size++;
		}
	}
}


template <class T>
int List<T>::GetSize() {
	return size;
}


template <class T>
void List<T>::removeAt(T data) {

	Node* current = head;
	if (findElement(data, current)) { // если есть элемент

		Node* toDelete = current;
		Node* previous = current->pBack;
		Node* following = current->pNext;

		if (previous != nullptr)
			previous->pNext = following;
		if (following != nullptr)
			following->pBack = previous;

		delete toDelete;
		size--;

		if (size == 0) {
			head = nullptr;
		}
	}

	else {
		std::cerr << "Ошибка данных для удаления. List::removeAt" << std::endl;
		exit(2);
	}
}


template <class T>
List<T>::List() {

	size = 0;
	head = nullptr;
}


template <class T>
List<T>::~List() {

	clear();
}


// -------------PRIVAT FUNCTION-------------

template <class T>
bool List<T>::findElement(T data, Node*& current) {

	current = head;

	if (size == 0) {
		return false;
	}

	while ((current->pNext != nullptr) && (current->data != data)) {
		current = current->pNext;
	}

	if (data == current->data)
		return true;
	else
		return false; // if data no find in list
}


template <class T>
void List<T>::clear() {

	for (; size; size--) {
		Node* toDelete = head;
		head = head->pNext;
		delete toDelete;
	}
}