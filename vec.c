#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"vec.h"
#include"str.h"

#define VECDEFLEN 16

Vec vec_new(void)
{
	Vec s=(Vec){
		.c=0,
		.n=0,
		.b=NULL,
	};

	return s;
}

void vec_grow(Vec*s)
{
	if(!s)return;
	if(!s->b)
		s->b=malloc(sizeof(Vec)*VECDEFLEN);
	else
		s->b=realloc(s->b,sizeof(Vec)*(s->c+VECDEFLEN));

	if(!s->b)
		s->c=0;
	else
		s->c+=VECDEFLEN;
}

void vec_push(Vec*s,char*c)
{
	if(!s)return;
	if(!c)return;
	if(!s->b||s->n+1>s->c)
		vec_grow(s);
	if(!s->b||s->n+1>s->c)
		return;
	str_assign(&s->b[s->n++],c);
}

void vec_free(Vec*s)
{
	if(!s)return;
	for(size_t i=0;i<s->c;++i)
		str_free(&s->b[i]);
	s->c=0;
}

void vec_print(Vec*v)
{
	printf("(%lu/%lu): [",v->n,v->c);
	for(size_t i=0;i<v->n;++i)
	{
		printf("'%s'",v->b[i].b);
		if(i<v->n-1)
			printf(", ");
	}
	printf("]\n");
}
