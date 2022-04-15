#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Str
{
	char*b;
	size_t c;
} Str;

Str str_new(void);
void str_grow(Str*s);
void str_assign(Str*s,char*c);
void str_free(Str*s);
