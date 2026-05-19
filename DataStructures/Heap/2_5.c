#include <stdlib.h>

#define MAXL 10000

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode LN;

LN* heap[MAXL];
int len;

void heapify(int idx) {
    LN* node = heap[idx];
    int cur = idx;
    int lc = 2 * cur + 1;
    while (lc < len) {
        if (lc + 1 < len && heap[lc + 1]->val < heap[lc]->val) ++lc;
        if (node->val <= heap[lc]->val) break;
        heap[cur] = heap[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }

    heap[cur] = node;
}

void bottomUp(LN** lists, int n) {
    len = 0;
    // 过滤空链表
    for (int i = 0; i < n; ++i) {
        if (!lists[i]) continue;
        // 保存链表首个节点
        heap[len++] = lists[i];
    }
    for (int i = len / 2 - 1; i >= 0; --i) heapify(i);
}

void swap(LN** a, LN** b) {
    LN* t = *a;
    *a = *b;
    *b = t;
}

LN* pop() {
    if (len == 0) return NULL;
    LN* res = heap[0];
    heap[0] = heap[0]->next;
    res->next = NULL;
    // 当前链表空
    if (heap[0] == NULL) swap(&heap[0], &heap[--len]);
    heapify(0);
    return res;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    bottomUp(lists, listsSize);

    LN dummy;
    dummy.next = NULL;
    LN* tail = &dummy;

    while (len > 0) {
        LN* node = pop();
        tail->next = node;
        tail = tail->next;
    }

    return dummy.next;
}
