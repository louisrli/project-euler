CC = g++
DEBUG = -g
EULER = -L. -l:./libeuler.so
GMP = -lgmpxx -lgmp
WARN = -Wall -Werror

euler.o: euler.cpp euler.h
	$(CC) -fpic -c euler.cpp -Werror $(WARN)
	$(CC) -shared -o libeuler.so euler.o  $(WARN)

%.o: %.cpp euler.o
	$(CC) $(EULER) -o $@ $< $(WARN) $(DEBUG) $(GMP)

clean: 
	rm -f *.o
