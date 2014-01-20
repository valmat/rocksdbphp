CPP             = g++
RM              = rm -f
CPP_FLAGS       = -Wall -c -I. -I./rocksdb -O2 -std=c++11 -fPIC

PREFIX			= /usr
#Edit these lines to correspond with your own directories
LIBRARY_DIR		= ${PREFIX}/lib/php5/20121212
ROCKSLIB= -lrocksdb -lpthread -lrt -lsnappy -lgflags -lz -lbz2
PHP_CONFIG_DIR	= /etc/php5/cli/conf.d

LD              = g++
LD_FLAGS        = -Wall -std=c++11 -fPIC -shared -O2

RESULT          = rocksdbphp.so

PHPINIFILE	= rocksdbphp.ini

SOURCES		= $(wildcard *.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -L. -lphpcpp ${ROCKSLIB}

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

${OBJECTS}: 
		${CPP} ${CPP_FLAGS} -o rocksdbphp.o rocksdbphp.cpp

install:
		cp -f ${RESULT} ${LIBRARY_DIR}
		cp -f ${PHPINIFILE}	${PHP_CONFIG_DIR}
