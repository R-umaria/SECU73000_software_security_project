CXX = gcc

# the -g for debugging support
CXXFLAGS = -Wall -g -m32
LDFLAGS = 

SRCS = $(wildcard *.c)
HDRS = $(wildcard *.h)

all: Project

Project: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o project $(LDFLAGS) $(SRCS)

clean:
	rm project *.o 
