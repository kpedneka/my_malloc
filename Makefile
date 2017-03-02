cc = gcc
cf = -Wall -Werror

all: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12

test1: test1.o mymalloc.o
	$(cc) $(cf) -o test1 mymalloc.o test1.o

test1.o: test1.c mymalloc.h
	$(cc) $(cf) -c -g test1.c

test2: test2.o mymalloc.o
	$(cc) $(cf) -o test2 mymalloc.o test2.o

test2.o: test2.c mymalloc.h
	$(cc) $(cf) -c -g test2.c

test3: test3.o mymalloc.o
	$(cc) $(cf) -o test3 mymalloc.o test3.o

test3.o: test3.c mymalloc.h
	$(cc) $(cf) -c -g test3.c

test4: test4.o mymalloc.o
	$(cc) $(cf) -o test4 mymalloc.o test4.o

test4.o: test4.c mymalloc.h
	$(cc) $(cf) -c -g test4.c

test5: test5.o mymalloc.o
	$(cc) $(cf) -o test5 mymalloc.o test5.o

test5.o: test5.c mymalloc.h
	$(cc) $(cf) -c -g test5.c

test6: test6.o mymalloc.o
	$(cc) $(cf) -o test6 mymalloc.o test6.o

test6.o: test6.c mymalloc.h
	$(cc) $(cf) -c -g test6.c

test7: test7.o mymalloc.o
	$(cc) $(cf) -o test7 mymalloc.o test7.o

test7.o: test7.c mymalloc.h
	$(cc) $(cf) -c -g test7.c

test8: test8.o mymalloc.o
	$(cc) $(cf) -o test8 mymalloc.o test8.o

test8.o: test8.c mymalloc.h
	$(cc) $(cf) -c -g test8.c

test9: test9.o mymalloc.o
	$(cc) $(cf) -o test9 mymalloc.o test9.o

test9.o: test9.c mymalloc.h
	$(cc) $(cf) -c -g test9.c

test10: test10.o mymalloc.o
	$(cc) $(cf) -o test10 mymalloc.o test10.o

test10.o: test10.c mymalloc.h
	$(cc) $(cf) -c -g test10.c

test11: test11.o mymalloc.o
	$(cc) $(cf) -o test11 mymalloc.o test11.o

test11.o: test11.c mymalloc.h
	$(cc) $(cf) -c -g test11.c

test12: test12.o mymalloc.o
	$(cc) $(cf) -o test12 mymalloc.o test12.o

test12.o: test12.c mymalloc.h
	$(cc) $(cf) -c -g test12.c


mymalloc.o: mymalloc.c mymalloc.h
	$(cc) $(cf) -g -c mymalloc.c

clean:
	rm -f test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12
	rm -f *~
	rm -f *.o