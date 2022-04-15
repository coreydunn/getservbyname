#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"str.h"

typedef struct Vec
{
	Str*b;
	size_t c;
	size_t n;
} Vec;

Vec vec_new(void);
void vec_grow(Vec*s);
void vec_push(Vec*s,char*c);
void vec_free(Vec*s);
void vec_print();
