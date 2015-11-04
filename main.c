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
	
	sub = jstr_substr(jstr, 6, 0);
	
	
	
	printf("[%s], length: %ld, capacity: %ld\n", 
	       jstr_cstr(sub),
		   jstr_length(sub),
		   sub->capacity);
	
	jstr_concat(sub, jstr_cstr(jstr));
	
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