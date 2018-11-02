#include <iostream>
#include <fstream>
#include <string>

#include "Stack.cpp"

//#define USER
#define TEST

using namespace std;

int index_person(string, string *, int);							//Функция нахождения индекса имени
void find_child(int, int, int **, Stack*, int);							//Функция нахождения детей и записи в стек
void print_stack(int, Stack*, string *, ofstream &);							//Функция печати поколений из стека

int main(int argc, char * argv[]) {

	ofstream fout;										//Открываем файл на запись результата
	fout.open("Result.txt");
	
	ifstream file (argv[1]);								//В первый раз открываем файл с именами
	string tmp;										//для нахождения количества имен persons
	int persons;
	for(persons = 0;; persons++) {
		file >> tmp;
		if(file.eof()) break;
	}
	file.close();										//end.

	ifstream file1 (argv[1]);								//Во второй раз открываем тот же файл
	string *names = new string[persons];							//для записи имен в массив строк names.
	cout << "Индекс - имя:" << endl;
	for(int i = 0; i < persons; i++) {
		file1 >> names[i];
		cout << i << ' ' << names[i] << endl;
	}
	file1.close();										//end.

	ifstream file2 (argv[2]);								//Открываем файл с матрицей родства
	int **concts = new int *[persons];							//и записываем ее в двумерный массив concts.
	for(int i = 0 ; i < persons; i++)
		concts[i] = new int[persons];

	cout << endl << "Таблица смежности:" << endl << "\x1b[4m"<< " |";
	for(int i = 0; i < persons; i++)
		cout << " " << i;
	cout << "\x1b[0m" << endl;
	for(int i = 0; i < persons; i++) {
		cout << i << "| " ;
		for(int j = 0; j < persons; j++) {
			file2 >> concts[i][j];
			if(file2.eof() && j != persons) {					//Обработка ошибки нехватки данных из откртого файла
				cout << endl << "Ошибка: недостаточно данных для таблицы родства" << endl;
				exit(1);
			}
			cout << concts[i][j] << ' ';
		}
		cout << endl;
	}
	file2.close();										//end.
	cout << endl;

	string name;
#ifdef USER
	cout << "Введите имя: ";								//Запрос имени name для предоставления потомков.
	cin >> name;
#endif
#ifdef TEST
	name = names[0];
#endif

	Stack *stack = new Stack;

	find_child(0, index_person(name, names, persons), concts, stack, persons);		//Найдем и запишем рекурсивно детей для nameю

	print_stack(0, stack, names, fout);								//Выведем список потомков.
	fout.close();
	for(int i = 0; i < persons; i++)							//Освобождение памяти под concts.
		free(concts[i]);
	free(concts);
	return 0;
}

int index_person(string name, string *names, int persons) {					//Функция определяющая индекс имени.
	for(int i = 0; i < persons; i++)
		if(name == names[i])	return i;
	cout << "Ошибка: Имени нет в списке" << endl;						//Вывод ошибки в случае неправильного имени.
	exit(1);
}

void find_child(int remove,int i_name, int **concts, Stack *stack, int persons) {		//Функция нахождения детей по индексу имени.
	stack->push(i_name, remove);								//Пуш в стек индекса найденного имени
	for(int i = 0; i < persons; i++){							//с учетом колена потомка.
		if(concts[i][i_name]) {								//Для найденного имени
			if(concts[i_name][i]) {
				cout << "Ошибка: ребенок не может быть отцом его родителя" << endl;
				exit(1);
			}
			if(stack->is_in_stack(i, remove)) {
				cout << "Ошибка: замкнутая цепь родства" << endl;
				exit(1);
			}
			find_child(remove + 1, i, concts, stack, persons);			//поиск детей для детей name.
		}
	}
}

void print_stack(int remove, Stack *stack, string *names, ofstream &fout) {					//Функция печати стека.
	if(remove)	fout << "Потомки "<< remove << "-го поколения: ";
	else		fout << "Потомки для ";
	for(int i = 0; i < stack->count_remove(remove); i++)					//По количеству потомков текущего колена remove
		fout << names[stack->pop()] << ' ';						//вывод имени по индексу полученному из стека.
	fout << endl;
	if(stack->isEmpty())									//Если стек не пуст
		print_stack(remove+1, stack, names, fout);						//идем печатать следующее колено.
}

