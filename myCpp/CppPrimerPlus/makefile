cxx = g++
OBJECT=te
DISTRACT=calculate.cpp caltest.cpp
all:$(OBJECT)
	
$(OBJECT):$(DISTRACT)
	$(cxx) -o $@ $(DISTRACT)
calcu.o:calculate.cpp
	$(cxx) -o -c $@ $<
caltest.o:calculate.cpp
	$(cxx) -o -c $@ $<
clean:
	rm $(OBJECT) te
