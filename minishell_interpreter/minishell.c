#include "interpreter.h"

int main()
{
	t_AST_Node *test;

	test = interpreter("echo 5 < 3 | export happy=id app tas | cat 3 << file.txt");
}