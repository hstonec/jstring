#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "jstring.h"



int
main(int atgc, char *argv[])
{
	JSTRING *jstr;
	JSTRING *jstr2;
	
	jstr = jstr_create("/hw4/../hw4/../hw4/././");
	
	jstr2 = jstr_create("/hw4/../hw4/../hw4/././");
	
	jstr_free(jstr);
	jstr_free(jstr2);
	
	return 0;
}