CXX = g++

ifndef os
   os = LINUX
endif

ifndef arch
   arch = IA32
endif

CCFLAGS = -Wall -w -D$(os) -I../lib/udt4/src/ -I/usr/local/mysql/include -finline-functions -O3
ifeq ($(arch), IA32)
   CCFLAGS += -DIA32 #-mcpu=pentiumpro -march=pentiumpro -mmmx -msse
endif

ifeq ($(arch), POWERPC)
   CCFLAGS += -mcpu=powerpc
endif

ifeq ($(arch), IA64)
   CCFLAGS += -DIA64
endif

ifeq ($(arch), SPARC)
   CCFLAGS += -DSPARC
endif

LDFLAGS = -L../lib/udt4/src/  -L/usr/local/mysql/lib -lmysqlclient -lz  -ludt -lstdc++ -lpthread -lm

DIR = $(shell pwd)

APP = server

all: $(APP)

%.o: %.cpp
	$(CXX) $(CCFLAGS) $< -c

server: handler.o db_handler.o
	$(CXX) $^ -o $@ $(LDFLAGS)


clean:
	rm -f *.o $(APP)

install:
	export PATH=$(DIR):$$PATH



