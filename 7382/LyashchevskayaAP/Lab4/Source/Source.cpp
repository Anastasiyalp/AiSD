#include <iostream>
#include <string>
#include <cctype>

using namespace std;

typedef struct Node {								//Структура элемента бинарного дерева
	char root;
	Node *left;
	Node *right;
	Node *parent;								//Для простоты алгоритма был добавлен родитель
} Node;

void print(string, char);							//Печать посл-ти с выделенным элементом при обходе
void checkSymb(string, string);							//Проверка на повторение символов в посл-тях

class BTree {
public:
	BTree() {
		curNode = new Node;
		top = curNode;
		curNode->parent = NULL;
		curNode->left = NULL;
		curNode->right = NULL;
	}
	~BTree() {
		del(top);
	}
	void del(Node *node){							//Последовательное удаление элементов
		if(node->left == NULL && node->right == NULL) delete node;
		if(node->left) del(node->left);
		if(node->right) del(node->right);
	}
	void root(char c) {							//Записывает корень элемента
		curNode->root = c;
		curNode->left = NULL;
		curNode->right = NULL;
	}
	void left() {								//Переход в левое поддерево
		curNode->left = new Node;
		curNode->left->parent = curNode;
		curNode = curNode->left;
	}
	void right() {								//Переход в правое поддерево
		curNode->right = new Node;
		curNode->right->parent = curNode;
		curNode = curNode->right;
	}
	void back() {								//Возврат к родителю
		curNode = curNode->parent;
	}
	bool isPred(char c) {							//Проверка на родство вглубь
		Node *tmp = curNode;
		while (tmp->parent) {
			if(tmp->parent->root == c)
				return 1;
			tmp = tmp->parent;
		}
		return 0;
	}
	char root() {								//Возвращает корень элемента
		return curNode->root;
	}
	void printTree() {                                                      //Печать девева-леса
                Node *tmp = top;
                while(tmp != NULL) {
                        cout << "\x1b[32m▶ \x1b[0m" << tmp->root << endl;
                        rec(tmp->left, 0);                                      //Вводится рекурсивная функция для полноты защиты элементов класса
                        cout << endl;
                        tmp = tmp->right;
                }
        }
	void printBTreeLPK() {							//Печать ЛПК
		cout << "Последоваельность ЛПК: " ;
		LPK(top, 0);							//Вводится рекурсивная функция для полноты защиты элементов класса
		cout << endl;
	}
	void printBTree() {							//Печать бинарного дерева
		string s = "";
		recB(top, 0, s);						//Вводится рекурсивная функция для полноты защиты элементов класса
	}
private:									//обеспечивает приватность всего дерева
	void LPK(Node *node, int deep) {					//Соответствует фие printBTreeLPK
		if(node == NULL) return;
		LPK(node->left, deep+1);
		LPK(node->right, deep+1);
		cout << node->root;
	}
        void recB(Node *node, int deep, string s) {				//Соответствует фие printBTree
		if(node == NULL) return;					//Граница рекурсии
		string c = s;							//Допстрока для разного вывода у левого и правого поддеревьев
		if(!deep)	cout << "▶ ";					//Первый заход
		cout << node->root << endl;
		if(node->right)	cout << s;					//Для правого поддерева, если оно есть
		if(node->left == NULL && node->right != NULL)			//форматный вывод
			cout << "\x1b[34m└▶ \x1b[0m" ;
		if(node->left != NULL && node->right != NULL)
			cout << "\x1b[34m├▶ \x1b[0m" ;
		if(node->left == NULL) s.append("  ");
		else s.append("\x1b[31m│ \x1b[0m");
		recB(node->right, deep + 1, s);					//и дальнейший обход правого поддерева
		if(node->left) cout << c;					//Для левого поддерева, если оно есть
		if(node->left != NULL)
			cout << "\x1b[31m└▶ \x1b[m" ;				//форматный вывод
		recB(node->left, deep + 1, c.append("  "));			//и дальнейший обход левого поддерева
	}
	void rec(Node *node, int deep) {                                        //Соответствует фие printTree
                while(node != NULL) {
                        if(node == NULL) return;
                        cout << ' ';
                        for(int i = 0; i < deep; i++)
                                cout << "\x1b[32m│ \x1b[0m";
                        if(node->right == NULL)
                                cout << "\x1b[32m└▶ \x1b[0m" << node->root << endl;
                        else
                                cout << "\x1b[32m├▶ \x1b[0m" << node->root << endl;
                        rec(node->left, deep + 1);
                        node = node->right;
                }
        }
	Node *curNode;
	Node *top;
};

int main() {

	string KLP, LKP;							//Две строки для посл-тей КЛП и ЛПК соответственно
	cout << "Введите последовательность КЛП:";
	getline(cin, KLP);
	cout << KLP << endl << "Введите последовательность ЛКП:";
	getline(cin, LKP);
	cout << LKP << endl;
										//Проверка соответствия длин посл-тей
	if (KLP.length() != LKP.length()) {cout << "Последовательности разной длины." << endl; exit(1);}
	checkSymb(LKP, KLP);							//Проверка на повторение символов в посл-тях и недопустимых значениях
	if(KLP == "") {cout << "Строки пусты" << endl; exit(1);}
	string::iterator klp = KLP.begin();					//Ставим итераторы для двух посл-тей
	string::iterator lkp = LKP.begin();

	BTree bTree;								//Объявляем дерево

	cout << "Восстановление дерева:" << endl;
	cout << endl << "Шаг 1:" << endl ;
	cout << "\tКЛП: " ; print(KLP, *klp);					//Печать посл-тей с выделением обрабатывания символа
	cout << "\tЛКП: " ; print(LKP, *lkp);
	cout <<"\tКорень дерева - '" << *klp << "'" << endl;			//Корень дерева всегда в начале ЛКП
	int step = 2;								//Тк шаг 1 уже был, начнем со второго
	while (klp != KLP.end()) {						//Дальше все шаги прописаны в коде
		bTree.root(*klp);						//Ну ладно, записываем корень
		
		cout << endl << "Шаг " << step++ << ":" << endl;		//Оформление
		cout << "\tКЛП: " ; print(KLP, *klp);
		cout << "\tЛКП: " ; print(LKP, *lkp);

		cout << "\tПросмотриваем КЛП, пока не встретим '" << *lkp << "' из ЛКП: " << endl;
		while (*(klp++) != *lkp) {
			if (klp == KLP.end()) {cout << "Последовательность завершилась прежде чем было найдено '" << *lkp << "'" << endl; exit(1);}
			bTree.left();						//Проходим в левое поддерево
			bTree.root(*klp);
			cout << "\t\tНа пути встретили '" << *klp << "' и записали как левый корень."  << endl;
		}
		if (klp == KLP.end()) break;					//Все

		cout << endl << "Шаг " << step++ << ":" << endl;
		cout << "\tКЛП: " ; print(KLP, *klp);
		cout << "\tЛКП: " ; print(LKP, *lkp);

		cout << "\tПросмотриваем ЛКП, пока встречаем уже записанные символы." << endl;
		while(bTree.isPred(*(++lkp))) {					//Если нашли предка
			if (klp == KLP.end()) break;
			do bTree.back(); while (bTree.root() != *lkp);		//Идем до него
			cout << "\t\tНа пути встретили повторяющееся '" << *lkp << "', обходим это." << endl;
		}
		if (klp == KLP.end()) break;					//Все

		bTree.right();							//Повернули вправое поддерево и пошли дальше

		cout << endl << "Шаг " << step++ << ":" << endl;
		cout << "\tКЛП: " ; print(KLP, *klp);
		cout << "\tЛКП: " ; print(LKP, *lkp);

		cout << "\tТо, что встретится дальше в КЛП, является правым корнем." << endl;
		if(lkp != KLP.end()) cout << "\tПравый корень - '" << *lkp << "'" << endl;
	};

	cout << endl << "Полученное бинарное дерево (\x1b[31mлево\x1b[0m, \x1b[34mправо\x1b[0m):" << endl;
	bTree.printBTree();							//Печатаем бинарный вариант дерева
	cout << "↓ ↓ ↓ ↓ ↓" << endl;
	cout << "Преобразованное дерево(лес):" << endl;
	bTree.printTree();							//Печатаем дерево(лес)
	bTree.printBTreeLPK();							//Печатаем ЛПК
	return 0;
}

void print(string s, char c) {							//Печать посл-тей с выделенным символом при обходе
	for(int i = 0; i < s.length(); i++)
		if(s[i] == (c)) cout << "(" << s[i] << ")";
		else
		cout << s[i];
	cout << endl;
}
void checkSymb(string LKP, string KLP){						//Проверка на повторение символов в посл-тях
	for (int i = 0; i < LKP.length(); i++) {
		for(int j = i+1; j < LKP.length(); j++)
			if((i != j) && (LKP[i] == LKP[j] || KLP[i] == KLP[j]))
				{cout << "Найдены повторяющиеся символы" << endl; exit(1);}
		if (KLP[i] < 65 || KLP[i] > 122 || LKP[i] < 65 || LKP[i] > 122)
			{cout << "Найден недопустимый символ " << KLP[i] << " или " << LKP[i] << endl; exit(1);}
	}
}
