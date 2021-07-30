DESTDIR ?= ${HOME}/Connectionless/
SOURCE1 = client.cpp IO.cpp
SOURCE2 = connectionless_server.cpp IO.cpp

all: connectionless_server client

connectionless_server: ${SOURCE2}
	g++ ${SOURCE2} -g -o $@
client: ${SOURCE1}
	g++ ${SOURCE1} -g -o $@
clean:
	${RM} connectionless_server
	${RM} client

instal: all
	mkdir -p ${DESTDIR}
	cp connectionless_server ${DESTDIR}
	cp client ${DESTDIR}

.PHONY: all clean install
