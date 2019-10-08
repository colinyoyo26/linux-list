CC = gcc
CFLAGS = -g -O3 -I../include -I../private
OBJ = merge-sort.o quick-sort.o insert-sort.o
OPT ?= "all"

all:
	$(CC) $(CFLAGS) -c insert-sort.c
	$(CC) $(CFLAGS) -c quick-sort.c
	$(CC) $(CFLAGS) -c merge-sort.c
	$(CC) $(CFLAGS) $(OBJ) benchmark.c -o benchmark
plotall: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i $(OPT); \
		printf "\n";\
	done > out.txt
	gnuplot -e "filename = '$(OPT).png'; ;\
	name1 = 'merge-sort'; ;\
	name2 = 'quick-sort'; ;\
	name3 = 'insertion-soert'" ./script/plot.gp
plotmt: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "mt"; \
		printf "\n";\
	done > out.txt
	gnuplot -e "filename = 'mtcmp.png';\
	name1 = 'merge-sort';\
	name2 = 'insertion-sort'" ./script/plot.gp
plotmq: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "mq"; \
		printf "\n";\
	done > out.txt
	gnuplot -e "filename = 'mqcmp.png';\
	name1 = 'merge-sort';\
	name2 = 'quick-sort'" ./script/plot.gp


.PHONY: clean
clean:
	-rm *.o *.png *.txt benchmark
