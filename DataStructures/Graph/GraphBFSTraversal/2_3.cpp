#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minStickers(vector<string>& stickers, string target) {
        int n = stickers.size();

        // 1. 统计所有贴纸的字母频次
        // stickersCount[i][c] 表示第 i 张贴纸中字符 c 的数量
        vector<vector<int>> stickersCount(n, vector<int>(26, 0));

        // graph[c] 记录所有“包含字符 c”的贴纸的下标
        vector<vector<int>> graph(26);

        for (int i = 0; i < n; ++i) {
            for (char ch : stickers[i]) ++stickersCount[i][ch - 'a'];
            // 如果这张贴纸有字符 ch，就把贴纸下标 i 加到 graph[ch] 中
            // 这里的条件保证了同一种字符只加一次索引，避免重复
            for (int j = 0; j < 26; ++j)
                if (stickersCount[i][j] > 0) graph[j].push_back(i);
        }

        // 2. 剪枝：如果 target 里的某个字符在所有贴纸里都没有，直接无解
        vector<int> targetCount(26, 0);
        for (char ch : target) ++targetCount[ch - 'a'];
        for (int i = 0; i < 26; ++i)
            if (targetCount[i] > 0 && graph[i].empty()) return -1;

        // 3. 开始标准 BFS 层序遍历
        queue<string> q;
        unordered_set<string> visited;

        // 将初始状态排序，方便去重
        sort(target.begin(), target.end());
        q.push(target);
        visited.insert(target);

        int level = 1;  // 记录当前使用的贴纸数量（层数）

        while (!q.empty()) {
            int level_sz = q.size();  // 当前层的状态总数

            // 逐个处理当前层的所有状态
            for (int i = 0; i < level_sz; ++i) {
                string curr = q.front();
                q.pop();

                // 统计当前剩余 target 字符串的字母频次
                vector<int> currCount(26, 0);
                for (char ch : curr) ++currCount[ch - 'a'];

                // 贪心剪枝策略：我们只干掉当前剩余字符串中的第一个字符 curr[0]
                // 这样能大大缩减分支，而且由于该字符迟早要被消掉，所以绝对不会漏掉最优解
                int first_ch = curr[0] - 'a';

                // 遍历所有包含 first_ch 的贴纸下标
                for (int sticker_idx : graph[first_ch]) {
                    // 计算用这张贴纸消除后的新状态
                    string next_state = "";
                    for (int j = 0; j < 26; ++j) {
                        if (currCount[j] <= 0) continue;
                        // 减去贴纸能提供的字符数量，如果减成负数则记为 0
                        int remain = max(
                            0, currCount[j] - stickersCount[sticker_idx][j]);
                        // 重新拼接成排好序的字符串作为下一阶段的状态
                        next_state.append(remain, j + 'a');
                    }

                    // 如果拼出的新状态为空，说明 target
                    // 全部字符都被消光了，大功告成！
                    if (next_state.empty()) return level;

                    // 如果这个状态在之前没有遇到过，则加入队列
                    if (visited.find(next_state) == visited.end()) {
                        visited.insert(next_state);
                        q.push(next_state);
                    }
                }
            }
            ++level;  // 当前层全部处理完，进入下一层（贴纸数 +1）
        }

        return -1;
    }
};
