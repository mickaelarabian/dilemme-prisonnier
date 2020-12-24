
SERVERDIR=./server_app/
SERVERDIRSRC=./server_app/src/
SERVERDIRUTILS=./server_app/utils/
DIRPROTOCOL=./protocol/
DIRCONFIG=./config/

TESTSERVERDIRFIXTURES=./server_app/tests/fixtures/
TESTSERVERDIRUNIT=./server_app/tests/unit/
TESTSERVERDIRTESTS=./server_app/tests/

CLIENTDIR=./client_app/
CLIENTDIRCONTROLLER=./client_app/controller/
CLIENTDIRSOCKET=./client_app/socket/
CLIENTDIRVIEWS=./client_app/views/

TESTCLIENTDIRFIXTURES=./client_app/tests/fixtures/
TESTCLIENTDIRUNIT=./client_app/tests/unit/
TESTCLIENTDIRTESTS=./client_app/tests/

CC=gcc
thread=-lpthread
threadInterface=-lpthread `pkg-config --cflags --libs gtk+-3.0` -rdynamic

CD=cd

server:
	${CD} $(DIRCONFIG) && $(CC) -c *.c
	${CD} $(SERVERDIRUTILS) && $(CC) -c utils.c
	${CD} $(SERVERDIRSRC) && $(CC) -c *.c
	${CD} $(SERVERDIR) && $(CC) -c *.c
	${CD} $(DIRPROTOCOL) && $(CC) -c *.c
	$(CC) ${thread} -o $(SERVERDIR)server $(SERVERDIR)*.o $(DIRCONFIG)*.o $(SERVERDIRSRC)*.o $(SERVERDIRUTILS)utils.o $(DIRPROTOCOL)protocol.o

client:
	$(CD) $(CLIENTDIR) && ${CC} -c *.c ${threadInterface}
	$(CD) $(CLIENTDIRVIEWS) && ${CC} -c *.c ${threadInterface}
	$(CD) $(CLIENTDIRSOCKET) && ${CC} -c *.c ${threadInterface}
	$(CD) $(DIRCONFIG) && ${CC} -c *.c ${threadInterface}
	${CD} $(DIRPROTOCOL) && $(CC) -c *.c
	$(CD) $(CLIENTDIRCONTROLLER) && ${CC} -c *.c ${threadInterface}
	$(CC) -o $(CLIENTDIR)client $(CLIENTDIR)*.o $(CLIENTDIR)views/*.o $(CLIENTDIR)socket/*.o $(DIRCONFIG)*.o $(CLIENTDIR)controller/*.o $(DIRPROTOCOL)protocol.o ${threadInterface}

testServer:
	$(CD) $(SERVERDIRUTILS) && $(CC) -c utils.c
	$(CD) $(TESTSERVERDIRUNIT) && $(CC) -c *.c
	$(CD) $(TESTSERVERDIRFIXTURES) && $(CC) -c *.c
	${CD} $(DIRCONFIG) && $(CC) -c *.c
	${CD} $(DIRPROTOCOL) && $(CC) -c *.c
	${CD} $(SERVERDIR) && $(CC) -c srvcxnmanager.c
	${CD} $(SERVERDIRSRC) && $(CC) -c controller.c
	${CD} $(SERVERDIRSRC) && $(CC) -c gameArray.c
	${CD} $(SERVERDIRSRC) && $(CC) -c game.c
	${CD} $(SERVERDIRSRC) && $(CC) -c file.c
	$(CD) $(TESTSERVERDIRTESTS) && $(CC) -c main.test.c
	$(CC) ${thread} -o $(SERVERDIR)testServer $(SERVERDIR)srvcxnmanager.o $(SERVERDIRSRC)controller.o $(SERVERDIRSRC)gameArray.o $(SERVERDIRSRC)game.o $(SERVERDIRSRC)file.o $(DIRPROTOCOL)protocol.o $(DIRCONFIG)*.o $(TESTSERVERDIRUNIT)*.o $(SERVERDIRUTILS)utils.o $(TESTSERVERDIRFIXTURES)*.o $(TESTSERVERDIRTESTS)main.test.o

runUnitServer:
	$(CD) $(SERVERDIR) && ./testServer

testClient:
	$(CD) $(TESTCLIENTDIRUNIT) && $(CC) -c *.c
	$(CD) $(TESTCLIENTDIRFIXTURES) && $(CC) -c *.c
	${CD} $(CLIENTDIRCONTROLLER) && $(CC) -c *.c
	${CD} $(DIRPROTOCOL) && $(CC) -c *.c
	$(CD) $(TESTCLIENTDIRTESTS) && $(CC) -c main.test.c
	${CC} -o $(CLIENTDIR)testClient $(TESTCLIENTDIRTESTS)main.test.o $(TESTCLIENTDIRUNIT)*.o $(TESTCLIENTDIRFIXTURES)*.o $(CLIENTDIRCONTROLLER)*.o $(DIRPROTOCOL)protocol.o

runUnitClient:
	$(CD) $(CLIENTDIR) && ./testClient

all: clean server client

clean:
	rm -f $(SERVERDIR)server && rm -f $(CLIENTDIR)client

runS:
	${CD} $(SERVERDIR) && ./server

runC:
	$(CD) $(CLIENTDIR) && ./client

runI:
	$(CLIENTDIR) && ./program

documentation: ./Doxyfile
	@doxygen ./Doxyfile
	@xdg-open html/files.html
