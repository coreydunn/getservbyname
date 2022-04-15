CFLAGS=  -Wfatal-errors
LDFLAGS= -s
OBJS=    main.o str.o vec.o

all: getservbyname
getservbyname: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
%.o: %.c
	$(CC) -c $^ $(CFLAGS)
%: %.o
	$(CC) $^ -o $@ $(LDFLAGS)
%: %.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	$(RM) $(OBJS)
