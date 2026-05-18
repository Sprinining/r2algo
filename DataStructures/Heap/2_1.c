#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode LN;

// 每次从链表数组中找到最小的头节点，加入最终结果
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;

    LN dummy;
    LN* tail = &dummy;
    dummy.next = NULL;

    while (1) {
        int min_idx = -1;
        // 找当前最小节点
        for (int i = 0; i < listsSize; ++i) {
            if (lists[i] == NULL) continue;
            if (min_idx == -1 || lists[i]->val < lists[min_idx]->val) {
                min_idx = i;
            }
        }
        // 全部链表遍历完
        if (min_idx == -1) break;

        tail->next = lists[min_idx];
        tail = tail->next;
        lists[min_idx] = lists[min_idx]->next;
        tail->next = NULL;
    }

    return dummy.next;
}
