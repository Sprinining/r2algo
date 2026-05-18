#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode LN;

LN* mergeTwo(LN* p, LN* q) {
    if (!p || !q) return p ? p : q;

    LN dummy;
    dummy.next = NULL;
    LN* tail = &dummy;

    while (p && q) {
        if (p->val <= q->val) {
            tail->next = p;
            p = p->next;
        } else {
            tail->next = q;
            q = q->next;
        }
        tail = tail->next;
    }

    tail->next = p ? p : q;
    return dummy.next;
}

// 分治
LN* mergeRange(LN** lists, int left, int right) {
    if (left > right) return NULL;
    if (left == right) return lists[left];
    int l = left, r = right;
    int m = left + (right - left) / 2;
    return mergeTwo(mergeRange(lists, l, m), mergeRange(lists, m + 1, r));
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    return mergeRange(lists, 0, listsSize - 1);
}
