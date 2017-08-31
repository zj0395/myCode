OBJECT = *.o
DISTARGET = test

all: $(DISTARGET)

$(DISTARGET) : crackBinary.o test.o
	g++ -O2 -o  $@ $^

.o.cpp:
	g++ -O2 -c $@

clean:
	rm $(OBJECT) $(DISTARGET)

