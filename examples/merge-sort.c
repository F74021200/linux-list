#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "list.h"

static uint16_t values[256];

void cmp_merge(struct list_head *tmp_list,
               struct list_head *list_1,
               struct list_head *list_2)
{
    struct listitem *item_1 = NULL, *item_2 = NULL;

    while (!list_empty(list_1) && !list_empty(list_2)) {
        item_1 = list_entry(list_1->next, struct listitem, list);
        item_2 = list_entry(list_2->next, struct listitem, list);
        if (item_1->i <= item_2->i)
            list_move_tail(list_1->next, tmp_list);
        else
            list_move_tail(list_2->next, tmp_list);
    }
    if (list_empty(list_1))
        list_splice_tail_init(list_2, tmp_list);
    else
        list_splice_tail_init(list_1, tmp_list);
}

void merge_sort(struct list_head *unsorted_list)
{
    struct listitem *item = NULL;
    struct list_head tmp_list, sorted_1_list, sorted_2_list, tmp_no_merge;
    int size = 0, n = 0, twice_n = 0;

    list_for_each_entry (item, unsorted_list, list) {
        size++;
    }

    INIT_LIST_HEAD(&tmp_list);
    INIT_LIST_HEAD(&sorted_1_list);
    INIT_LIST_HEAD(&sorted_2_list);
    INIT_LIST_HEAD(&tmp_no_merge);
    n = 1;
    twice_n = n << 1;
    while (n <= size) {
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (j < n) {
                list_move_tail(unsorted_list->next, &sorted_1_list);
                j++;
            } else if (j >= n && j < twice_n) {
                list_move_tail(unsorted_list->next, &sorted_2_list);
                j++;
            } else if (j == twice_n) {
                cmp_merge(&tmp_list, &sorted_1_list, &sorted_2_list);
                j = 0;
                i--;
            }
        }
        if (!list_empty(&sorted_1_list)) {
            cmp_merge(&tmp_no_merge, &sorted_1_list, &sorted_2_list);
            merge_tail(&tmp_list, &tmp_no_merge, twice_n);
        }
        list_splice_init(&tmp_list, unsorted_list);

        n = n << 1;
        twice_n = n << 1;
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
