/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
size_t size = 0;
/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (!q) {
        free(q);
        return NULL;
    }

    INIT_LIST_HEAD(&q->list);
    size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    while (q_remove_head(q, NULL, 0))
        ;
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    queue_t *newh;
    char *str;
    /* What should you do if the q is NULL? */
    if (!q)
        return false;

    newh = malloc(sizeof(queue_t));
    str = malloc(strlen(s) * sizeof(char) + 1);

    if (!newh || !str) {
        free(str);
        free(newh);
        return false;
    }

    newh->value = str;
    strcpy(newh->value, s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    list_add(&newh->list, &q->list);
    size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    queue_t *newh;
    char *str;

    if (!q || !s)
        return false;

    newh = malloc(sizeof(queue_t));
    str = malloc(strlen(s) * sizeof(char) + 1);

    if (!newh || !str) {
        free(str);
        free(newh);
        return false;
    }

    newh->value = str;
    strcpy(newh->value, s);

    list_add_tail(&newh->list, &q->list);
    size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || list_empty(&q->list))
        return false;

    queue_t *first = list_first_entry(&q->list, queue_t, list);

    if (bufsize > 0) {
        memset(sp, '\0', bufsize);
        strncpy(sp, first->value, bufsize - 1);
    }

    list_del(&first->list);
    free(first->value);
    free(first);
    size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return !q ? 0 : size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || size < 2)
        return;

    struct list_head *prev, *node, *safe;
    list_for_each_safe (node, safe, &q->list) {
        prev = node->prev;
        node->prev = node->next;
        node->next = prev;
    }
    prev = (q->list).prev;
    (q->list).prev = (q->list).next;
    (q->list).next = prev;
}

void q_sort(queue_t *q)
{
    if (!q)
        return;
    list_msort(&q->list);
}
