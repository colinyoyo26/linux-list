#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "list.h"
#include "benchmark.h"

#define MERGE_ANALYSIS                               \
    do {                                             \
        clock_gettime(CLOCK_REALTIME, &start);       \
        list_msort(&testlist);                       \
        clock_gettime(CLOCK_REALTIME, &end);         \
        printf("%lu ", end.tv_nsec - start.tv_nsec); \
    } while (0)
#define QUICK_ANALYSIS                               \
    do {                                             \
        clock_gettime(CLOCK_REALTIME, &start);       \
        list_qsort(&testlist);                       \
        clock_gettime(CLOCK_REALTIME, &end);         \
        printf("%lu ", end.tv_nsec - start.tv_nsec); \
    } while (0)
#define INSERT_ANALYSIS                              \
    do {                                             \
        clock_gettime(CLOCK_REALTIME, &start);       \
        list_insertsort(&testlist);                  \
        clock_gettime(CLOCK_REALTIME, &end);         \
        printf("%lu ", end.tv_nsec - start.tv_nsec); \
    } while (0)


int main(int argc, char **argv)
{
    struct list_head testlist;
    struct listitem *item;
    struct timespec start, end;
    uint16_t values[atoi(argv[1])];
    uint16_t method = atoi(argv[2]);
#ifdef RANDOM
    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));
#elif INCREASE
    increasing_array(values, (uint16_t) ARRAY_SIZE(values));
#endif
    INIT_LIST_HEAD(&testlist);
    assert(list_empty(&testlist));

    for (size_t i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(struct listitem));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }
    assert(!list_empty(&testlist));
    if (!strcmp("mq", argv[2])) {
        MERGE_ANALYSIS;
        QUICK_ANALYSIS;
    }

    if (!strcmp("mt", argv[2])) {
        MERGE_ANALYSIS;
        INSERT_ANALYSIS;
    }

    if (!strcmp("qt", argv[2])) {
        QUICK_ANALYSIS;
        INSERT_ANALYSIS;
    }

    if (!strcmp("all", argv[2])) {
        MERGE_ANALYSIS;
        QUICK_ANALYSIS;
        INSERT_ANALYSIS;
    }
    return 0;
}