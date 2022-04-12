CFLAGS=  -Wfatal-errors
LDFLAGS= -s
OBJS=    getservbyname

all: $(OBJS)
getservbyname: main.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
%: %.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	$(RM) $(OBJS)
