#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode LN;

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;

    LN dummy;
    LN* tail = &dummy;
    dummy.next = NULL;

    int n = listsSize;

    while (1) {
        int min_idx = -1;
        int non_empty_count = 0;

        // 找最小节点，同时统计非空链表数量
        for (int i = 0; i < n; ++i) {
            if (lists[i] == NULL) continue;
            ++non_empty_count;
            if (min_idx == -1 || lists[i]->val < lists[min_idx]->val) {
                min_idx = i;
            }
        }
        // 全部链表空了
        if (min_idx == -1) break;

        // 如果只剩一个非空链表，直接接上
        if (non_empty_count == 1) {
            tail->next = lists[min_idx];
            break;
        }

        // 否则把当前最小节点接上
        tail->next = lists[min_idx];
        tail = tail->next;
        lists[min_idx] = lists[min_idx]->next;
        tail->next = NULL;
    }

    return dummy.next;
}
