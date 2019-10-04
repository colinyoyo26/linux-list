#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "common.h"

static void list_merge(struct list_head *left,
                       struct list_head *right,
                       struct list_head *head)
{
    struct listitem *Lentry = NULL, *Rentry = NULL;

    while (!list_empty(left) || !list_empty(right)) {
        Lentry = list_first_entry(left, struct listitem, list);
        Rentry = list_first_entry(right, struct listitem, list);

        if (!list_empty(left) && cmpint(&Lentry->i, &Rentry->i) < 0 ||
            list_empty(right))
            list_move_tail(&Lentry->list, head);
        else
            list_move_tail(&Rentry->list, head);
    }
}
static void list_msort(struct list_head *head)
{
    struct list_head list_left, list_right, *tmp;
    struct listitem *item = NULL, *is = NULL;
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

int main(int argc, char *argv[])
{
    struct list_head testlist;
    struct listitem *item;
    uint16_t values[atoi(argv[1])];

    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));
    INIT_LIST_HEAD(&testlist);
    assert(list_empty(&testlist));

    for (size_t i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(struct listitem));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }

    assert(!list_empty(&testlist));

    qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);
    list_msort(&testlist);

    /* check if the result is correct */
    struct listitem *is = NULL, *item2 = NULL;
    size_t j = 0;

    list_for_each_entry_safe (item, is, &testlist, list) {
        assert(item->i == values[j]);
        list_del(&item->list);
        free(item);
        j++;
    }
    return 0;
}
