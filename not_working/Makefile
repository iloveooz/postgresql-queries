SRC=query.cxx
PROG=query

all:
	c++ ${SRC} -o ${PROG} `pkg-config --libs --cflags libpqxx`
clean:
	rm -f *.o ${PROG}
