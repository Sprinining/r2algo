#define MOD 1000000007
#define MAXN 30005

typedef long long ll;

/**
 * 1. 当数组中存在多个相同的最小值时（例如 [..., 1a, ..., 1b, ..., 1c, ...]）：
 *    包含多个 '1' 的大子数组，若不处理会被重复计算。
 *
 * 2. 本代码采用的去重策略是：相同数字留在栈中不弹出（使用 arr[...] > arr[i]）
 *    这种策略在逻辑上规定：如果数值相同，位置越靠左的数字，算作越小
 *
 * 3. 越靠左的数（如 1a）在栈底呆得最久，右视线极强，能穿透右边相同数直达天际
 *
 * 4. 越靠右的数（如 1b）压在别人上面，向左看时一低头就会被屁股下的相同数卡死
 *
 * 5. 包含 [1a, 1b, 1c] 的大子数组：只有 1a 的视线能全部包容，因此全盘上交给 1a
 *    包含 [1b, 1c] 但不含 1a 的子数组：1c 左边被 1b 卡死，因此全盘上交给 1b
 *
 * 6. 通过这种左侧放宽穿透，右侧严格卡死的规则，重叠区间被完美瓜分，不重不漏
 */

int stk[MAXN];
int left_next_min[MAXN];
int right_next_min[MAXN];
int sz;

int sumSubarrayMins(int* arr, int arrSize) {
    int n = arrSize;
    sz = 0;

    // 单调栈正向扫描
    for (int i = 0; i < n; ++i) {
        // 使用严格大于，当相等时条件不成立，不触发弹出，相同数字会齐刷刷地留在栈里
        while (sz > 0 && arr[stk[sz - 1]] > arr[i]) {
            int top = stk[--sz];

            // 右边界：只有遇到严格小于它的数 i 才会触发弹出
            // 如果右边是相同的数，它会直接压在 top 上面而不是弹出 top
            // 所以 top 的右视线成功穿透了右边所有相同的数，直达这个严格小的 i
            right_next_min[top] = i;

            // 左边界：top 被弹出后，当前栈顶元素就是它的左边界。
            // 因为相同的数都留在了栈里，若屁股下压着相同的数，会直接变成它的左边界
            // 从而导致它的左视线被相同数死死卡住（即左侧满足小于等于关系）
            left_next_min[top] = sz > 0 ? stk[sz - 1] : -1;
        }
        // 相同的数和拉升栈的数一律压入栈中
        stk[sz++] = i;
    }

    // 留在栈里的元素，说明它们右边已经没有任何严格小于它们的数了
    while (sz > 0) {
        int top = stk[--sz];
        // 右边界直接触及虚拟边界 n
        right_next_min[top] = n;
        // 左边界的逻辑依然不变：等于它屁股下面的那个元素下标（若空则为 -1）
        left_next_min[top] = sz > 0 ? stk[sz - 1] : -1;
    }

    ll res = 0;
    for (int i = 0; i < n; ++i) {
        // 左距离 l = 必须包含 arr[i] 时，起始的位置总数
        // 右距离 r = 必须包含 arr[i] 时，结束的位置总数
        ll l = i - left_next_min[i];
        ll r = right_next_min[i] - i;
        ll temp = (l * r) % MOD;
        temp = (temp * arr[i]) % MOD;
        res = (res + temp) % MOD;
    }

    return (int)res;
}
