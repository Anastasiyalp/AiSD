#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef struct Node {
	int type;								//Хранит: 1 - символ, 2 - число, 3 - выражение
	struct Node *next;
	char symbol;
	struct Node *expr;
	int digit;
} Node;

void abort_(const char * s, ...);						//Экстренное завершение программы с сообщением
void fill_list(int, Node *, char *);
int find_sec_bracket(char *);
void check_division(Node *);
void print_list(Node *node);
int reduct(int, Node *node);							//Возвращает инфу об аргументе после аргумента-знака

int main() {

	char *str = (char *)malloc(100 * sizeof(char));
	fgets(str, 100, stdin);
	if (!strcmp(str, "\n"))					
		abort_("Expression is empty.");
	printf("Before: %s\n", str);

	printf("Args in expr with levels:\n");
	Node *top = (Node*)malloc(sizeof(Node));
	fill_list(0, top, str);							//Заполняет список, выводя аргументы на своих уровнях

	printf("\nReduction process:\n");
	reduct(0, top);								//Редактирует список, выводя сообщения о каждом сокращении
	printf("\nAfter: ");
	if(top->next->next == NULL) {						//Выражение обнулилось
		printf("0\n");
		return 0;
	}
	if(top->next->next->next != NULL)
		print_list(top);
	else {									//Во внешнем выражении остался один аргумент
		if(top->next->type == 1)
			printf("%c", top->next->symbol);
		if(top->next->type == 2)
			printf("%d", top->next->digit);
		if(top->next->type == 3)
			print_list(top->next->expr);
	}
	check_division(top);							//Проверка деления на ноль
	printf("\n");
	return 0;
}

void abort_(const char * s, ...) {

        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

void fill_list(int deep, Node *node, char *str) {

	int sign = 0;
	int end_expr = find_sec_bracket(str + 1);
	for(int i = 0; i < deep; i++)						//Отступы при глубине рекурсии deep
		printf("%d|\t", i);
	printf("Start of expr.\n");
	for(int i = 1; i < end_expr; i++) {					//Обработка выражения до его закрывающей скобки
		if(isalpha(str[i]) || str[i] == '*' || str[i] == '/' || str[i] == '-' || str[i] == '+') {
			if(!sign || isalpha(str[i])) {				//Если это буква или знак, но не минус перед числом, то
				node->type = 1;					//инициализируем элемент-символ
				node->symbol = str[i];
				for(int i = 0; i < deep; i++)
					printf("%d|\t", i);
				printf("%d| %c\n", deep, str[i]);
				node->next = (Node *)malloc(sizeof(Node));
				node = node->next;				//Указатель перемещается к следующему элементу списка
				if(str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/')
					sign++;					//В следующий раз в этом подвыражении будут только минусы перед числами
				continue;
			}
		}
		if(isdigit(str[i]) || (str[i] == '-' && sign)) {		//Если это число или минус перед ним,то
			node->type = 2;						//инициализируем элемент-число
			node->digit = atoi(str + i);
			while(str[i] == '-')
				i++;
			while(isdigit(str[i + 1]))
				i++;
			for(int i = 0; i < deep; i++)
				printf("%d|\t", i);
			printf("%d| %d\n", deep, node->digit);
			node->next = (Node *)malloc(sizeof(Node));
			node = node->next;
		}
		if(str[i] == '(') {						//Если встретили подвыражение, то
			node->type = 3;						//инициализируем элемент-выраженияе
			node->expr = (Node *)malloc(sizeof(Node));
			fill_list(deep + 1, node->expr, str + i);		//И переходим к его заполнению рекурсивно
			node->next = (Node *)malloc(sizeof(Node));
			node = node->next;
			i += find_sec_bracket(str + i + 1);			//Перемещаем индекс хождения по выражению i
		}
	}
	node->next = NULL;							//Обозначим границу списка
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("End of expr.\n");

}

int find_sec_bracket(char *str) {						//Ищет парную скобку в выражении

	int left_br = 1, right_br = 0;
	int i;
	for (i = 0; left_br != right_br; i++) {
		if (str[i] == '(')
			left_br++;
		if (str[i] == ')')
			right_br++;
	}
	return i;
}

void check_division(Node *node) {						//Проверка деления на ноль

	while(node->next) {
		if (node->type == 1 && node->symbol == '/') {
				node = node->next;
				while(node->next->next) {			//Переходим от аргумента к аргументу
					node = node->next;
					if(node->type == 2 && node->digit == 0)	//Пока не встретим нужный элемент в выражении с делением
							abort_("\nError - deviision by zero!");
				}
		}
		if(node->type == 3)
			check_division(node->expr);
		node = node->next;
	}
}

void print_list(Node *node) {							//Последовательный вывод выражения за выражением

	printf("(");
	while(node->next ) {
		if(node->type == 1)
			printf("%c", node->symbol);
		if(node->type == 2)
			printf("%d", node->digit);
		if(node->type == 3)
			if(node->expr->next)
				print_list(node->expr);
		printf(" ");
		node = node->next;
	}
	printf(")");
}

int reduct(int deep, Node *node) {						//Редактирует содержимое списка

	char sign;
	Node *start_node = node;
	if(node->type == 1)
		sign = node->symbol;
	else
		abort_("\nError - pass mark");					//Если первый элемент не символ, вывод ошибки об этом

	for(int i = 0; i < deep; i++)						//Отступ по глубине
		printf("%d|\t", i);
	printf("Start of expr.\n");
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("%d| %c\n", deep, sign);

	while(node->next) {
		for(int i = 0; i < deep && (node->next->type == 1 || node->next->type == 2); i++)
			printf("%d|\t", i);					//Печатаем отступы если символ или цифра
		if(node->next->type != 3 && node->next->next)
			printf("%d| ", deep);
		if(node->next->type == 1)
			printf("%c ", node->next->symbol);
		if(node->next->type == 2)
			printf("%d ", node->next->digit);

		if(node->next->type == 3) {					//Встретилось подвыражение
			if(reduct(deep + 1, node->next->expr)) {		//Если в нем все сократилось:
				if(sign == '+' || sign == '-') {		//для выражения со знаком "+" или "-"
					node->next = node->next->next;		//перемещаем указатель, стирая элемент пустого подвыражения
				}
				if(sign == '/') {				//для выражения со знаком "/"
					node->next->type = 2;			//элемент-подвыражение становится элементом-числом (0)
					node->next->digit = 0;
				}
				if(sign == '*') {				//для выражения со знаком "*"
					start_node->next->next = NULL;		//Все выражение обнуляется
					break;
				}
			}
			else							//Если же не все сократилось
				if(node->next->expr->next->next->next == NULL) {//и остался один элемент
					if(node->next->expr->next->type == 1) {	//если это символ
						node->next->type = 1;		//поднимаем его на уровень выше 
						node->next->symbol = node->next->expr->next->symbol;
						for(int i = 0; i < deep; i++)
							printf("%d|\t", i);
						printf("%d| level up with %c", deep, node->next->symbol);
					}
					if(node->next->expr->next->type == 2) {	//если это цифра
						node->next->type = 2;		//поднимаем ее на уровень выше
						node->next->digit = node->next->expr->next->digit;
						for(int i = 0; i < deep; i++)
							printf("%d|\t", i);
						printf("%d| level up with %d", deep, node->next->digit);
					}
					if(node->next->expr->next->type == 3) {	//если это другое выражение
						node->next->expr = node->next->expr->next->expr;//поднимаем его на уровень выше
						for(int i = 0; i < deep; i++)
							printf("%d|\t", i);
						printf("%d| level up with expr", deep);
					}
				}
		}

		if(sign == '+' || sign == '-') {				//Если знак текущего выражения "+" или "-"
			if(node->next->type == 2) {				//и встретился элемент-число 0
				if(node->next->digit == 0 && (node->symbol != '-' && (node->next->next->next || node->symbol != '*'))) {
					printf("delete\n");			//и притом он не первый при "-"
					node->next = node->next->next;		//- удаляем его
					continue;
				}
			}
		}
		if((sign == '/' || sign == '*') && node->next->type == 2) {	//Если знак текущего выражения "/" или "*"
				if(node->next->digit == 1 && (node->symbol != '/' && (node->next->next->next  || node->symbol != '*'))) {
					printf("delete\n");			//и встретился элемент-число 1 
					node->next = node->next->next;		//и притом он не первый при делении - удаляем его
					continue;
				}
		}
		if(sign == '*' || node->symbol == '/')				//Если знак текущего выражения "/" или "*"
			if(node->next->type == 2 && node->next->digit == 0) {	//и мы встречаем элемент-число 0
			printf("delete expr\n");				//обнуляем выражение
			start_node->next->type = 2;
			start_node->next->digit = 0;
			start_node->next->next = NULL;
			break;							//заканчиваем его обработку
		}
		if(node->next->type != 0 && node->next->type != 3)
			printf("\n");
		node = node->next;						//переходим к следующему выражению
	}
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("End of expr.\n");

	return (start_node->next->next == NULL);				//Возврат инфы о существовании второго элемента
}
