#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"
#include "common.h"
#include <stdio.h>

static void list_insert_sorted(queue_t *entry, struct list_head *head)
{
    queue_t *item = NULL;

    if (list_empty(head)) {
        list_add(&entry->list, head);
        return;
    }

    list_for_each_entry (item, head, list) {
        if (atoi(entry->value) < atoi(item->value)) {
            list_add_tail(&entry->list, &item->list);
            return;
        }
    }

    list_add_tail(&entry->list, head);
}

void list_insertsort(struct list_head *head)
{
    struct list_head list_unsorted;
    queue_t *item = NULL, *is = NULL;

    INIT_LIST_HEAD(&list_unsorted);
    list_splice_init(head, &list_unsorted);

    list_for_each_entry_safe (item, is, &list_unsorted, list) {
        list_del(&item->list);
        list_insert_sorted(item, head);
    }
}
