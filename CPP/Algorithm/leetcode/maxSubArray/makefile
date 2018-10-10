#This makefile is generate automatically.
#You can change it free as you want.

DISTARGET = test
SRC = $(wildcard *.cpp)
OBJECT = $(SRC:.cpp=.o)
DEPENDENCE = $(SRC:.cpp=.d)
CC = g++
CFLAGS = -Wall
LFLAGS = 

all : $(DISTARGET)


%.d : %.cpp
	@set -e;rm -f $@;\
	$(CC) -MM $< >$@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' <$@.$$$$ >$@;\
	rm -f $@.$$$$

$(DISTARGET) : $(OBJECT)
	$(CC) $(LFLAGS) -o $@ $^

sinclude $(SRC:.cpp=.d)
%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY:clean
clean:
	@rm -f $(DISTARGET) $(OBJECT) $(DEPENDENCE)

