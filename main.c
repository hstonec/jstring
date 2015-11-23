#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "jstring.h"



int
main(int atgc, char *argv[])
{
	JSTRING *jstr;
	JSTRING *sub;
	jstr = jstr_create("abcdefg");
	
	printf("[%s], length: %ld, capacity: %ld\n", 
	       jstr_cstr(jstr),
		   jstr_length(jstr),
		   jstr->capacity);
	
	sub = jstr_substr(jstr, 0, 7);
	
	jstr_trunc(sub, 7, 4);
	
	printf("%d\n\n", jstr_equals(jstr, sub));
	
	printf("[%s], length: %ld, capacity: %ld\n", 
	       jstr_cstr(sub),
		   jstr_length(sub),
		   sub->capacity);
	
	jstr_insert(jstr, 0, "123");
	
	jstr_append(sub, '!');
	jstr_append(sub, '!');
	jstr_append(sub, '!');
	jstr_append(sub, '!');
	
	printf("[%s], length: %ld, capacity: %ld\n", 
	       jstr_cstr(sub),
		   jstr_length(sub),
		   sub->capacity);
	
	jstr_free(sub);
	jstr_free(jstr);
	
	return 0;
}