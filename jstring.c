/*
 * This program provides a String object with 
 * a series of operation functions on it.
 * This idea comes from Java so it is named 
 * JSTRING.
 *
 * To use this String object, you don't need to
 * worry about memory allocation or boundary check.
 * You can append or concatenate arbitrary characters
 * as you want and the String will be expanded 
 * appropriately and automatically.
 */
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jstring.h"

#define MALLOC(ptr, ptrtype, len) \
do { \
	ptr = (ptrtype *)malloc(sizeof(ptrtype) * (len)); \
	if (ptr == NULL) { \
		(void)fprintf(stderr, \
			"create " #ptrtype " *" \
			#ptr " error: malloc() failed\n"); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

#define REALLOC(ptr, ptrtype, len) \
do { \
	ptr = (ptrtype *)realloc(ptr, sizeof(ptrtype) * (len)); \
	if (ptr == NULL) { \
		(void)fprintf(stderr, \
			"change " #ptrtype " *" \
			#ptr " error: realloc() failed\n"); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

JSTRING *jstr_create_from_arr(char *, size_t);
void jstr_realloc(JSTRING *);
void check_index(JSTRING *, size_t);
void check_ptr(void *);

JSTRING *
jstr_create(char *str)
{
	check_ptr(str);

	return jstr_create_from_arr(str, strlen(str));
}

char *
jstr_cstr(JSTRING *jstr)
{
	check_ptr(jstr);
	
	return jstr->str;
}

size_t
jstr_length(JSTRING *jstr)
{
	check_ptr(jstr);
	
	return jstr->length;
}

char
jstr_charat(JSTRING *jstr, size_t index)
{
	check_ptr(jstr);
	check_index(jstr, index);
	
	return jstr->str[index];
}

JSTRING *
jstr_substr(JSTRING *jstr, size_t index, size_t len)
{
	check_ptr(jstr);
	check_index(jstr, index);
	
	if (index + len > jstr->length) {
		(void)fprintf(stderr, 
		      "jstring: length out of range\n");
		exit(EXIT_FAILURE);
	}
	
	return jstr_create_from_arr(jstr->str + index, len);
}

int
jstr_equals(JSTRING *jstr1, JSTRING *jstr2)
{
	check_ptr(jstr1);
	check_ptr(jstr2);
	
	return strcmp(jstr_cstr(jstr1), jstr_cstr(jstr2));
}

void
jstr_concat(JSTRING *jstr, char *str)
{
	check_ptr(jstr);
	check_ptr(str);
	
	jstr->length += strlen(str);
	jstr_realloc(jstr);
		
	(void)strcat(jstr->str, str);
	
}

void
jstr_append(JSTRING *jstr, char c)
{
	check_ptr(jstr);
	
	jstr->length += 1;
	jstr_realloc(jstr);
	
	jstr->str[jstr->length - 1] = c;
	jstr->str[jstr->length] = '\0';
	
}

void
jstr_free(JSTRING *jstr)
{
	check_ptr(jstr);
	
	free(jstr->str);
	jstr->str = NULL;
	jstr->length = 0;
	jstr->capacity = 0;
	free(jstr);
	
}

JSTRING *
jstr_create_from_arr(char *arr, size_t len)
{
	
	JSTRING *jstr;
	
	MALLOC(jstr, JSTRING, 1);
	
	jstr->length = len;
	jstr->capacity = len + 1;
	
	MALLOC(jstr->str, char, jstr->capacity);
	(void)memcpy(jstr->str, arr, sizeof(char) * len);
	
	jstr->str[len] = '\0';
	
	return jstr;
}

void
jstr_realloc(JSTRING *jstr)
{
	
	if (jstr->length >= jstr->capacity) {
		jstr->capacity = jstr->length + 1;
		jstr->capacity *= 2;
		REALLOC(jstr->str, char, jstr->capacity);
	}
	
}

void
check_ptr(void *ptr)
{
	if (ptr == NULL) {
		(void)fprintf(stderr, "jstring: NULL pointer\n");
		exit(EXIT_FAILURE);
	}
}

void
check_index(JSTRING *jstr, size_t index)
{
	if (index >= jstr->length) {
		(void)fprintf(stderr, 
		      "jstring: index [%ld] out of range [0, %ld]\n",
			  index,
			  jstr->length - 1);
		exit(EXIT_FAILURE);
	}
}


