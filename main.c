#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdbool.h>
#include"str.h"
#include"vec.h"

int main(int argc,char**argv)
{
	struct servent*serv=NULL;
	char*name=NULL;
	bool reverse=false;
	bool verbose=false;
	Vec v=vec_new();

	if(argc<2)
	{
		fprintf(stderr,"error: service name not specified\n");
		exit(1);
	}

	for(int i=1;i<argc;++i)
	{
		name=argv[i];
		vec_push(&v,name);

		if(strcmp(name,"-v")==0)
		{
			verbose=true;
			continue;
		}

		if(!name||!*name)
		{
			fprintf(stderr,"error: name cannot be empty/null\n");
			continue;
		}

		serv=getservbyname(name,"tcp");

		// Lookup by name failed -- attempt reverse lookup
		if(!serv)
		{
			serv=getservbyport(ntohs(atoi(name)),"tcp");
			if(serv)
				reverse=true;
		}

		// Failed to find service
		if(!serv)
		{
			fprintf(stderr,"error: cannot identify service '%s'\n",name);
			continue;
		}

		// Output full info
		if(verbose)
		{
			char**p=serv->s_aliases;

			printf("%s %d %s",serv->s_name,serv->s_port,serv->s_proto);
			printf(" [");
			for(int i=0;p[i];++i)
			{
				printf("%s ",serv->s_aliases[i]);
				if(p[i+1])
					printf(", ");
			}
			printf("]\n");
		}

		// Output basic info
		else
		{
			if(reverse)
				printf("%s %s\n",name,serv->s_name);
			else
				printf("%s %d\n",name,htons(serv->s_port));
		}
	}

	vec_free(&v);
}
