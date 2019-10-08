CC = gcc
CFLAGS = -g -O3 -I../include -I../private
OBJ = merge-sort.o quick-sort.o insert-sort.o

all:
	$(CC) $(CFLAGS) -c insert-sort.c
	$(CC) $(CFLAGS) -c quick-sort.c
	$(CC) $(CFLAGS) -c merge-sort.c
	$(CC) $(CFLAGS) $(OBJ) benchmark.c -o benchmark
plotall: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "all"; \
		printf "\n";\
	done > out.txt
	gnuplot ./script/plotall.gp
plotmt: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "mt"; \
		printf "\n";\
	done > out.txt
	gnuplot ./script/plotmt.gp
plotmq: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "mq"; \
		printf "\n";\
	done > out.txt
	gnuplot ./script/plotmq.gp


.PHONY: clean
clean:
	-rm *.o *.png *.txt
