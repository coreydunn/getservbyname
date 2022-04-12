#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc,char**argv)
{
	struct servent*serv=NULL;
	char*name=NULL;

	if(argc<2)
	{
		fprintf(stderr,"error: service name not specified\n");
		exit(1);
	}
	else
		name=argv[1];

	if(!name)
	{
		fprintf(stderr,"error: name cannot be empty/null\n");
		exit(1);
	}

	serv=getservbyname(name,"tcp");
	if(!serv)
	{
		fprintf(stderr,"error: cannot identify service '%s'\n",name);
		exit(1);
	}

	printf("%s => %d\n",name,htons(serv->s_port));
}
