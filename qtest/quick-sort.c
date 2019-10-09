#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"
#include "common.h"


void list_qsort(struct list_head *head)
{
    struct list_head list_less, list_greater;
    queue_t *pivot;
    queue_t *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, queue_t, list);
    list_del(&pivot->list);

    list_for_each_entry_safe (item, is, head, list) {
        if (atoi(item->value) < atoi(pivot->value))
            list_move_tail(&item->list, &list_less);
        else
            list_move(&item->list, &list_greater);
    }

    list_qsort(&list_less);
    list_qsort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}