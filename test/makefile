CFLAGS:=-Wall -g -pthread -std=c++11
OUTPUT:=-o
test:=cmain
INCLUDE=-I../core

$(addsuffix .out,$(test)) :$(addsuffix .o,$(test)) 
	$(CXX) $(CFLAGS) $^ $(OUTPUT) $@
$(addsuffix .o,$(test)) : $(addsuffix .cpp,$(test))
	$(CXX) $(CFLAGS) -c $^ $(OUTPUT) $@


.PHONY:clean
clean:
	rm *.o
