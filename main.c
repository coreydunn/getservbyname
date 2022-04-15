#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdbool.h>

int main(int argc,char**argv)
{
	struct servent*serv=NULL;
	char*name=NULL;
	bool reverse=false;

	if(argc<2)
	{
		fprintf(stderr,"error: service name not specified\n");
		exit(1);
	}

	for(int i=1;i<argc;++i)
	{
		name=argv[i];

		if(!name||!*name)
		{
			fprintf(stderr,"error: name cannot be empty/null\n");
			continue;
		}

		serv=getservbyname(name,"tcp");

		// Attempt reverse lookup
		if(!serv)
		{
			serv=getservbyport(ntohs(atoi(name)),"tcp");
			if(serv)
				reverse=true;
		}

		// Failed
		if(!serv)
		{
			fprintf(stderr,"error: cannot identify service '%s'\n",name);
			continue;
		}

		if(reverse)
			printf("%s => %s\n",name,serv->s_name);
		else
			printf("%s => %d\n",name,htons(serv->s_port));
	}
}
