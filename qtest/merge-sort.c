#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "common.h"
#include "queue.h"


static void list_merge(struct list_head *left,
                       struct list_head *right,
                       struct list_head *head)
{
    queue_t *Lentry = NULL, *Rentry = NULL;

    while (!list_empty(left) || !list_empty(right)) {
        Lentry = list_first_entry(left, queue_t, list);
        Rentry = list_first_entry(right, queue_t, list);

        if ((!list_empty(left) && atoi(Lentry->value) < atoi(Rentry->value)) ||
            list_empty(right))
            list_move_tail(&Lentry->list, head);
        else
            list_move_tail(&Rentry->list, head);
    }
}
void list_msort(struct list_head *head)
{
    struct list_head list_left, list_right;
    queue_t *item = NULL, *is = NULL;
    size_t i = 0;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_left);
    INIT_LIST_HEAD(&list_right);

    list_for_each_entry_safe (item, is, head, list) {
        if (++i & 1)
            list_move_tail(&item->list, &list_left);
        else
            list_move_tail(&item->list, &list_right);
    }

    list_msort(&list_left);
    list_msort(&list_right);
    list_merge(&list_left, &list_right, head);
}
