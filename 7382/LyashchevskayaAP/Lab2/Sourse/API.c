#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "API.h"

void print_list(Node *node) {

	if (node->flag_type[1] == 1)
		if (node->sign == '/' && node->two == 0)
			abort_("\nError - deviision by zero!");

	if((node->sign == '+' || node->sign == '-') && node->flag_type[0] == 1)
		if(node->one == 0) {
			if(node->flag_type[1] == 1)
				printf(" %d", node->two);
			else
				print_list(node->right);
			return;
		}

	if((node->sign == '+' || node->sign == '-') && node->flag_type[1] == 1)
		if(node->two == 0) {
			if(node->flag_type[0] == 1)
				printf(" %d", node->one);
			else
				print_list(node->left);
			return;
		}

	if(node->sign == '*' && node->flag_type[0] == 1)
		if(node->one == 1) {
			if(node->flag_type[1] == 1)
				printf(" %d", node->two);
			else
				print_list(node->right);
			return;
		}

	if(node->sign == '*' && node->flag_type[1] == 1)
		if(node->two == 1) {
			if(node->flag_type[0] == 1)
				printf(" %d", node->one);
			else
				print_list(node->left);
			return;
		}
	if(node->sign == '/' && node->flag_type[1] == 1)
		if(node->two == 1) {
			if(node->flag_type[0] == 1)
				printf(" %d", node->one);
			else
				print_list(node->left);
			return;
		}

	printf(" (%c", node->sign);
	if (node->flag_type[0] == 2)
		print_list(node->left);
	else
		printf(" %d", node->one);
	if(node->flag_type[1] == 2)
		print_list(node->right);
	else
		printf(" %d", node->two);
	printf(")");

}

void abort_(const char * s, ...)					//Insert in case of incorrect length string
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

void fill_list(Node * node, char *str) {
	int args[5];
	find_args(str, args);
	fill_node(node, args, str);

}

void fill_node(Node * node, int *args, char *str){
	node->sign = str[args[0]];
	node->left = (Node *)malloc(sizeof(Node));
	node->right = (Node *)malloc(sizeof(Node));
	if (isdigit(str[args[1]])) {
		node->flag_type[0] = 1;
		node->one = 0;
		while (isdigit(str[args[1]]))
			node->one = node->one * 10 + str[args[1]++] - '0';
		if (isdigit(str[args[2]])) {
			node->flag_type[1] = 1;
			node->two = 0;
			while (isdigit(str[args[2]]))
				node->two = node->two * 10 + str[args[2]++] - '0';
		}
		else {
			node->flag_type[1] = 2;
			fill_expr(node->right, args[2], args[3], str);
		}
	}
	else {
		node->flag_type[0] = 2;
		fill_expr(node->left, args[1], args[2], str);

		if (isdigit(str[args[3]])) {
			node->flag_type[1] = 1;
			node->two = 0;
			while (isdigit(str[args[3]]))
				node->two = node->two * 10 + str[args[3]++] - '0';
		}
		else {
			fill_expr(node->right, args[3], args[4], str);
			node->flag_type[1] = 2;
		}
	}
}
void fill_expr(Node *node,int  arg1, int arg2, char *str) {
	int odd = arg2 - arg1 + 1;
	char *new_str = (char *)malloc(sizeof(char) * odd);
	strncpy(new_str, str + arg1, odd);
	printf("Component expr %s\n", new_str);
	fill_list(node, new_str);
}

void find_args(char *str, int *args) {
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			args[0] = i;
			break;
		}

	int limit = 3;
	int add = args[0];
	for (int i = 1; i < limit; i++) {
		args[i] = add + 1;
		while (str[args[i]] == ' ') {
			args[i]++;
		}
		add = args[i];
		if (isdigit(str[args[i]]) && isdigit(str[args[i]+1])) {
			while (isdigit(str[add]))
				add++;
		}
		if (str[args[i]] == '(') {
			i++;
			args[i] = find_sec_bracket(str + args[i-1] + 1) + args[i-1];
			limit++;
			add += args[i] - args[i-1] ;
		}
	}
}

int find_sec_bracket(char *str) {
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
