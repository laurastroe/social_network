# Variables to control Makefile operation

PROG = socialNetwork
CXX = g++
CXXFLAGS = -Wall -g
SOURCE = SocialNetwork.cpp
OBJS = $(SOURCE:.cpp=.o)
all: $(SOURCE) $(PROG)

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS)
$(OBJS) :
	$(CXX) $(CXXFLAGS) -c $(SOURCE)
clean:
	rm -f core $(PROG) $(OBJS)