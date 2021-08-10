DESTDIR ?= ${HOME}/Connectionless/
SOURCE1 = connectionless_client.cpp IO.cpp
SOURCE2 = connectionless_server.cpp IO.cpp

all: connectionless_server connectionless_client

connectionless_server: ${SOURCE2}
	g++ ${SOURCE2} -g -o $@
connectionless_client: ${SOURCE1}
	g++ ${SOURCE1} -g -o $@
clean:
	${RM} connectionless_server
	${RM} connectionless_client

instal: all
	mkdir -p ${DESTDIR}
	cp connectionless_server ${DESTDIR}
	cp connectionless_client ${DESTDIR}

.PHONY: all clean install
