#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "API.h"

int main() {

	char *str = (char *)malloc(100 * sizeof(char));
	fgets(str, 100, stdin);
	if (!strcmp(str, "\n"))
		abort_("Expression is empty.");

	printf("In first expr look like this %s", str);

	List list;
	Node top;
	list.top = &top;
	fill_list(list.top, str);
	printf("Abridged expression lools like this:");
	print_list(list.top);
	printf("\n");
	return 0;
}
