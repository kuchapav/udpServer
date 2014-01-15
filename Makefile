# compiler
CC = $(CXX)
# CC = clang

# compile-time flags
# CFLAGS = -Wall -g
CFLAGS = -g -std=c++0x
PTHREAD = -pthread

# path to compiled boost library (necessary only if it isn't in compilers include path)
BOOST_PATH = ../boost
BOOST_HEADERS = $(BOOST_PATH)/include
BOOST_LIBS = $(BOOST_PATH)/lib

BOOST_INCLUDE = -I $(BOOST_HEADERS) -L $(BOOST_LIBS)

BOOST_SYSTEM = $(BOOST_LIBS)/libboost_system.a



# match all *.cc files and make *.o files
OBJS = $(patsubst %.cc, %.o, $(wildcard *.cc))

# program name
TARGET = server client


bin: $(TARGET)

tclient: $(OBJS)
	$(CXX) tclient.o $(OBJSC) $(LDFLAGS) -o $@



$(OBJS): %.o: %.cc
	$(CC) -c $< $(CFLAGS) $(BOOST_INCLUDE) -o $@

server: $(OBJS)
	$(CC) $(CFLAGS) server.o position.o $(BOOST_INCLUDE) $(BOOST_SYSTEM) $(PTHREAD) -o $@

client: $(OBJS)
	$(CC) $(CFLAGS) client.o $(BOOST_INCLUDE) $(BOOST_SYSTEM) $(PTHREAD) -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

# serialization:
# 	$(CC) -c serialization.cc $(CFLAGS) -o serialization.o

# position: serialization
# 	$(CC) -c position.cc $(CFLAGS) -o position.o