#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "list.h"
#include "benchmark.h"

#define ANALYSIS(name)                               \
    do {                                             \
        clock_gettime(CLOCK_REALTIME, &start);       \
        list_##name##sort(&name##_list);             \
        clock_gettime(CLOCK_REALTIME, &end);         \
        printf("%lu ", end.tv_nsec - start.tv_nsec); \
    } while (0)


int main(int argc, char **argv)
{
    struct list_head m_list, q_list, insert_list;
    struct listitem *item1, *item2, *item3;
    struct timespec start, end;
    uint16_t values[atoi(argv[1])];
    uint16_t method = atoi(argv[2]);
#ifdef RANDOM
    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));
#elif INCREASE
    increasing_array(values, (uint16_t) ARRAY_SIZE(values));
#endif
    INIT_LIST_HEAD(&m_list);
    INIT_LIST_HEAD(&q_list);
    INIT_LIST_HEAD(&insert_list);
    assert(list_empty(&m_list) && list_empty(&q_list) &&
           list_empty(&insert_list));

    for (size_t i = 0; i < ARRAY_SIZE(values); i++) {
        item1 = (struct listitem *) malloc(sizeof(struct listitem));
        item2 = (struct listitem *) malloc(sizeof(struct listitem));
        item3 = (struct listitem *) malloc(sizeof(struct listitem));
        assert(item1 && item2 && item3);
        item1->i = item2->i = item3->i = values[i];
        list_add_tail(&item1->list, &m_list);
        list_add_tail(&item2->list, &q_list);
        list_add_tail(&item3->list, &insert_list);
    }
    assert(!list_empty(&m_list) && !list_empty(&q_list) &&
           !list_empty(&insert_list));
    if (!strcmp("mq", argv[2])) {
        ANALYSIS(m);
        ANALYSIS(q);
    }

    if (!strcmp("mt", argv[2])) {
        ANALYSIS(m);
        ANALYSIS(insert);
    }

    if (!strcmp("qt", argv[2])) {
        ANALYSIS(q);
        ANALYSIS(insert);
    }

    if (!strcmp("all", argv[2])) {
        ANALYSIS(m);
        ANALYSIS(q);
        ANALYSIS(insert);
    }
    return 0;
}