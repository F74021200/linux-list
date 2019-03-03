#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "list.h"

static uint16_t values[256];

void merge_sort(struct list_head *unsorted_list)
{
    struct listitem *item = NULL;
    int size = 0;

    list_for_each_entry (item, unsorted_list, list) {
        size++;
    }
}

int main()
{
    struct list_head testlist;
    struct listitem *item = NULL;
    size_t i;

    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));

    INIT_LIST_HEAD(&testlist);

    assert(list_empty(&testlist));

    for (i = 0; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }
    list_for_each_entry (item, &testlist, list) {
        printf("%d ", item->i);
    }
    printf("\n");

    return 0;
}
