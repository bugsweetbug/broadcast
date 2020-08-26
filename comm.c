#include "sock_include.h"
void err(const char *str)
{
	perror(str);
	exit(1);
}