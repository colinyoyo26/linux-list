CC = gcc
CFLAGS = -g -O3 -I../include -I../private
OBJ = merge-sort.o quick-sort.o insert-sort.o
OPT ?= RANDOM

all:
	$(CC) $(CFLAGS) -c insert-sort.c
	$(CC) $(CFLAGS) -c quick-sort.c
	$(CC) $(CFLAGS) -c merge-sort.c
	$(CC) $(CFLAGS) -D$(OPT) $(OBJ) benchmark.c -o benchmark
plotall: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "all"; \
		printf "\n";\
	done > out.txt
	gnuplot -e "filename = 'all.png'; ;\
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

plotqt: all
	for i in `seq 1 100 3000`; do \
		printf "%d " $$i;\
		./benchmark $$i "qt"; \
		printf "\n";\
	done > out.txt
	gnuplot -e "filename = 'qtcmp.png';\
	name1 = 'quick-sort';\
	name2 = 'insertion-sort'" ./script/plot.gp


.PHONY: clean
clean:
	-rm *.o *.png *.txt benchmark
