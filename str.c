#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"str.h"

#define STRDEFLEN 128

Str str_new(void)
{
	Str s=(Str){
		.c=0,
		.b=NULL,
	};

	return s;
}

void str_grow(Str*s)
{
	if(!s)return;
	if(!s->b)
		s->b=malloc(STRDEFLEN);
	else
		s->b=realloc(s->b,s->c+STRDEFLEN);

	if(!s->b)
		s->c=0;
	else
		s->c+=STRDEFLEN;
}

void str_assign(Str*s,char*c)
{
	if(!s)return;
	if(!c)return;
	if(!s->b||s->c<strlen(c)+1)
		str_grow(s);
	if(!s->b||s->c<strlen(c)+1)
		return;
	strcpy(s->b,c);
}

void str_free(Str*s)
{
	if(!s)return;
	if(s->b)
		free(s->b);
	s->c=0;
}
