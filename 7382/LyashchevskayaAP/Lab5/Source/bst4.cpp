
/********************************************************************************
Случайные БДП с рандомизацией 1+2a. Демонстрация.

Демонстрация - визуализация структур данных, алгоритмов, действий. Демонстрация
должна быть подробной и понятной (в том числе сопровождаться пояснениями), чтобы
программу можно было использовать в обучении для объяснения используемой
структуры данных и выполняемых с нею действий.
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>
#include "BStree.h"

//#define USER

using namespace std ;
using namespace binSTree_modul;

typedef unsigned int unInt;

unInt hBT (binSTree b);
unInt sizeBT (binSTree b);
void printLKP (binSTree b);


int main (int argc, char *argv[])
{	srand(time(NULL));
	ifstream infile2 (argv[1]);
	cout << "Построение случайного БДП началось." << endl << endl;
	cout << "Случайные БДП с рандомизацией имеют такую особенность, что добавление очередного элемента может" << endl;
	cout << "производиться как в корень элемента, используя вращения, так и в свое законное место в обычном" << endl;
	cout << "случайном БДП (обход ЛКП в обоих случаях выдает последовательность в алфавитном порядке)." << endl << endl;

	if (!infile2) cout << "Входной файл #2 не открыт!" << endl;
	cout << "Файл получен." << endl;
	base c;
	binSTree b = Create();
	int k = 0;
	while (infile2 >> c)
	{	cout << "Шаг " << ++k << ":" << endl;
		cout << "Получил элемент '" ;
		cout << c;
		cout << "'" << endl;
		randomInsert (b, c);
		printBT(b, 0, "");
		cout << "*************************" << endl << endl;
	}
	cout << "Дерево из файла построено." << endl;
	cout << "Всего прочитано символов: " << k << endl;
	cout << "Высота дерева = " << hBT(b) << endl;
	cout << "Размер (число узлов) дерева = " << sizeBT(b) << endl;
	printBT(b, 0, "");
	cout << endl << "ЛКП: ";
	printLKP (b);
	cout << endl << endl;
#ifdef USER
	cout << "Введите символ, а я решу куда его вставить (завершить: '!'): ";
	while (cin >> c && c != '!'){
		randomInsert (b, c);
		printBT (b, 0, "");
		cout << endl << "ЛКП: ";
		printLKP (b);
		cout << endl;
		cout << "Введите символ, а я решу куда его вставить: ";
	}
#endif
	destroy (b);
	return 0;
}

//---------------------------------------
	unInt hBT (binSTree b)
	{
		if (isNull(b)) return 0;
		else return max (hBT (Left(b)), hBT(Right(b))) + 1;
	}

//---------------------------------------
	unInt sizeBT (binSTree b)
	{
		if (isNull(b)) return 0;
		else return sizeBT (Left(b))+ sizeBT(Right(b)) + 1;
	}

//---------------------------------------
	void printLKP (binSTree b)
	{	if (!isNull(b)) {
			printLKP (Left(b));
			cout << RootBT(b) << '(' << RootCountBT(b)<< ')' ;
			printLKP (Right(b));
		}
	}
