#include "mysql_query.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char name[128];
	char value[128];
	printf("Pls input tab:");
	scanf(%s,&name);
	printf("value = %s",mysql_query(name,value));
}
