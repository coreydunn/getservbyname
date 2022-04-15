#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdbool.h>
#include"str.h"
#include"vec.h"

#define HELPSTR "usage: getservbyname -htuv [SERVICE|PORT]"

int main(int argc,char**argv)
{
	Vec v=vec_new();
	bool reverse=false;
	bool verbose=false;
	bool showhelp=false;
	char*name=NULL;
	char*protocol="tcp";
	struct servent*serv=NULL;

	// Process arguments
	for(int i=1;i<argc;++i)
	{

		// Short options
		if(argv[i][0]=='-')
		{
			for(size_t j=1;argv[i][j];++j)
			{
				switch(argv[i][j])
				{

					case 'h':
						showhelp=true;
						break;

					case 't':
						protocol="tcp";
						break;

					case 'u':
						protocol="udp";
						break;

					case 'v':
						verbose=true;
						break;

					default:
					fprintf(stderr,"error: unrecognized option '%c'\n",argv[i][j]);
						break;

				}
			}
		}

		// Default: treat as service name (or port number)
		else
			vec_push(&v,argv[i]);
	}

	if(argc<2||showhelp)
		printf("%s\n",HELPSTR);

	vec_sort(&v);

	// Process service names
	if(!showhelp)
	{
		for(size_t i=0;i<v.n;++i)
		{
			name=v.b[i].b;

			if(!name||!*name)
			{
				fprintf(stderr,"error: name cannot be empty/null\n");
				continue;
			}

			serv=getservbyname(name,protocol);

			// Lookup by name failed -- attempt reverse lookup
			if(!serv)
			{
				serv=getservbyport(ntohs(atoi(name)),protocol);
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

				printf("%s %d %s",serv->s_name,ntohs(serv->s_port),serv->s_proto);
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
	}

	vec_free(&v);
}
