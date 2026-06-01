#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 30005

typedef long long ll;

int stk[MAXN];
int sz;

int sumSubarrayMins(int* arr, int arrSize) {
    int n = arrSize + 2;
    sz = 0;
    // 头尾各加一个哨兵
    int* nums = malloc(sizeof(int) * n);
    nums[0] = nums[n - 1] = 0;
    memcpy(nums + 1, arr, sizeof(int) * arrSize);

    ll res = 0;
    // 头哨兵必须扫描入栈：是为了给后面所有元素提供一个绝对安全的左边界
    // 尾哨兵必须扫描入栈：是为了发出清场信号，强行把栈里所有残留的元素逼出来结算
    for (int i = 0; i < n; ++i) {
        while (sz > 0 && nums[stk[sz - 1]] > nums[i]) {
            int top = stk[--sz];
            // 结算栈顶
            ll left = top - stk[sz - 1];
            ll right = i - top;
            ll temp = (left * right) % MOD;
            temp = (temp * nums[top]) % MOD;
            res = (res + temp) % MOD;
        }
        stk[sz++] = i;
    }
    // 栈里最终会剩下两个哨兵

    return res;
}
