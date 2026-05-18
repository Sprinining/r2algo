#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode LN;

LN* merge(LN* p, LN* q) {
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

// 遍历链表数组，每次把一整条链表和最终链表合并
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    LN* res = NULL;
    for (int i = 0; i < listsSize; ++i) res = merge(lists[i], res);
    return res;
}
