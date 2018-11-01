#include <iostream>

#define START_SIZE 10
#define COUNT_REMOVE 10

using namespace std;

class Stack{
public:
	Stack() {										//Конструктор выделяет память под данные.
		size = 0;
		data = new int[START_SIZE];
		i_remove = new int[COUNT_REMOVE];
		for(int i = 0; i < COUNT_REMOVE; i++)
			i_remove[i] = 0;
	}
	~Stack() {}										//Деструктор пуст, так как стек подается в функции.

	void push(int val, int remove) {							//Пуш элемента с учетом колена.
		if(is_in_stack(val, remove + 1))						//В случае если в этом колене уже встречался этот потомок, не записывать его
			return;
		resize();									//Увеливаем память, если нужно.
		int i_el = 0;
		for(int i = 0; i < remove; i++)							//Считаем количество элементов до колена remove
			i_el += i_remove[i];
		if(i_el != size) {								//Если элемент не последний,
			for(int i = size; i > i_el; i--)
				data[i] = data[i-1];						//сместим все элементы на одну позицию,
		}										//выделенную под новый элемент.
		data[i_el] = val;								//Запишем новый элемент
		i_remove[remove]++;								//Для колена remove увеличим количество его элементов
		size++;
	}

	int pop() {										//Поп первого элемента со смещением всех элементов влево
		int poped = data[0];
		for(int i = 0; i < size - 1; i++)
			data[i] = data[i+1];
		size--;
		return poped;
	}

	int count_remove(int remove) {return i_remove[remove];}					//Возвращает количество элементов колена

	int isEmpty() {return size;}								//Проверяет стек на пустоту

	int is_in_stack(int el, int remove) {							//Проверяет встречался ли элемент в предыдущих коленах
		int i_el = 0;
		for(int i = 0; i < remove; i++)
			i_el += i_remove[i];
		for(int i = 0; i < i_el; i++)
			if(data[i] == el)
				return 1;
		return 0;
	}

private:
	int *data;										//Указатель под массив имен
	int *i_remove;										//Указатель под массив количества элементов колена по индексу
	int size;										//Размер стека

	void resize() {										//Динамическое увеличение массива data
		if(size % START_SIZE == 0 && size) {
			cout << "+10 to data"<< endl;
			int *pTmp = new int[size + 10];
			for(int i = 0; i < size; i++)
				pTmp[i] = data[i];
			delete[] data;
			data = pTmp;
		}
	}
};


