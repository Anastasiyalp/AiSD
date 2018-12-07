#include <iostream>
#include <cstdlib>
#include <string>
#include "BStree.h"
using namespace std ;

namespace binSTree_modul
{

//-------------------------------------
	binSTree Create()
	{	return NULL;
	}
//-------------------------------------
	bool isNull(binSTree b)
	{	return (!b);
	}
//-------------------------------------
	base RootBT (binSTree b)			// для непустого бин.дерева
	{	if (!b) { cerr << "Error: RootBT(null) \n"; exit(1); }
		else return b->info;
	}
//-------------------------------------
	unsigned int RootCountBT (binSTree b)		// для непустого бин.дерева
	{	if (!b) { cerr << "Error: RootBT(null) \n"; exit(1); }
		else return b->count;
	}
//-------------------------------------
	binSTree Left (binSTree b)			// для непустого бин.дерева
	{	if (!b) { cerr << "Error: Left(null) \n"; exit(1); }
		else return b ->lt;
	}
//-------------------------------------
	binSTree Right (binSTree b)			// для непустого бин.дерева
	{	if (!b) { cerr << "Error: Right(null) \n"; exit(1); }
		else return b->rt;
	}
//-------------------------------------
	void destroy (binSTree &b)
	{	if (b)
		{	destroy (b->lt);
			destroy (b->rt);
			delete b;
			b = NULL;
		}
	}

//-------------------------------------
//вращения-----------------------------
	void rotateR (binSTree &t)
	//b - не пусто
	{	binSTree x;
		cout << "Поддерево с вершиной '" << t->info << "' до поворота:"  << endl;
		printBT(t, 0, "");
		cout << "*********rotateR*********" << endl;
		cout << "Корнем становится корень левого поддерева." << endl;
		cout << "Предыдущий корень перемещается на место корня правого поддерева главного корня." << endl;
		cout << "А смещенный на предыдщем этапе корень перемещается на место левого корня предыдущего корня." << endl;
		cout << "*********rotateR*********" << endl;

		x = t->lt;
		t->lt = x->rt;
		x->rt = t;
		t = x;
		if(t->lt) {
			t->lt->number = t->lt->count;
			if(t->lt->lt) t->lt->number += t->lt->lt->number;
			if(t->lt->rt) t->lt->number += t->lt->rt->number;
		}
		t->number = t->count;
		if(t->lt) t->number += t->lt->number;
		if(t->rt) t->number += t->rt->number;

		cout << "После:"  << endl;
		printBT(t, 0, "");
		cout << endl;
	}
//------------------------------
	void rotateL (binSTree &t)
	//b - не пусто
	{	binSTree x;
		cout << "Поддерево с вершиной '" << t->info << "' до поворота:"  << endl;
		printBT(t, 0, "");
		cout << "*********rotateL*********" << endl;
		cout << "Корнем становится корень правого поддерева." << endl;
		cout << "Предыдущий корень перемещается на место корня левого поддерева главного корня." << endl;
		cout << "А смещенный на предыдщем этапе корень перемещается на место правого корня предыдущего корня." << endl;
		cout << "*********rotateL*********" << endl;

		x = t->rt;
		t->rt = x->lt;
		x->lt = t;
		t = x;

		if(t->rt) {
			t->rt->number = t->rt->count;
			if(t->rt->lt) t->rt->number += t->rt->lt->number;
			if(t->rt->rt) t->rt->number += t->rt->rt->number;
		}
		t->number = t->count;
		if(t->lt) t->number += t->lt->number;
		if(t->rt) t->number += t->rt->number;

		cout << "После:"  << endl;
		printBT(t, 0, "");
		cout << endl;
	}
// вставка в корень------------
	void insInRoot (binSTree &b, base x)
	{	if (b == NULL) {
			b = new node;
			if ( b != NULL)	{
				b ->info = x;
				b ->count = 1;
				b ->number = 1;
			}
			else {cerr << "1 Memory not enough\n"; exit(1);}
		} else
		if (x < b->info){insInRoot (b->lt, x); rotateR (b);}
		else if (x > b->info){insInRoot (b->rt, x); rotateL (b);}
		else {b->count++; b->number++;}
	}
// печать текущего бинарного дерева
	void printBT(binSTree &node, int deep, string s)
	{       if(node == NULL) return;
	                string c = s;
	        if(!deep)       cout << "▶ ";
	                cout << RootBT(node) << " \x1b[90m(" << node->number << ")\x1b[0m" << endl;
	        if(node->rt) cout << s;
	        if(!node->lt && node->rt)
	                cout << "\x1b[34m└▶ \x1b[0m" ;
	        if(node->lt && node->rt)
	                cout << "\x1b[34m├▶ \x1b[0m" ;
	        if(node->lt) printBT(node->rt, deep + 1, s.append("\x1b[31m│ \x1b[0m"));
	        else printBT(node->rt, deep + 1, s.append("\x1b[31m \x1b[0m"));
	        if(node->lt) cout << c;
	        if(node->lt)
	                cout << "\x1b[31m└▶ \x1b[m" ;
	        printBT(node->lt, deep + 1, c.append("  "));
	}
// рандомная вставка
	void randomInsert(binSTree &b, base x)
	{	if(b == NULL) {
			cout << "Я решил, всталю в согласно БДП!" << endl;
			b = new node;
			if(b != NULL) {
				b->info = x;
				b->count = 1;
				b->number = 1;
				return;
			}
			else { cerr << "1 Memory not enough" << endl; exit(1);}
		}
		if(rand()%(b->number + 1) == 0)
		{	cout << endl << "Я решил, вставлю в корень, на место '" << b->info << "'!" << endl;
			cout << "Для этого вставлю элемент в БДП,";
			cout << " а затем буду перемещать его при помощи вращений к корню." << endl;
			insInRoot(b, x);
			cout << "Вставка в корень закончена, дерево имеет вид:" << endl;
			return;
		}
		else if(x < b->info)
		{	cout << "'" << x << "' < '" << b->info << "'" << endl;
                        cout << "Переход \x1b[31m<-\x1b[0m" << endl;
			randomInsert(b->lt, x);
		}
		else if(x == b->info)
		{	b->count ++;
			cout << "Элемент в дереве уже был, я просто увеличил счетчик для этого элемента." << endl;
		}
		else
		{	randomInsert(b->rt, x);
			cout << "'" << x << "' > '" << b->info << "'" << endl;
                        cout << "Переход \x1b[34m->\x1b[0m" << endl;
		}
		b->number++;
	}
}
// end of namespace
