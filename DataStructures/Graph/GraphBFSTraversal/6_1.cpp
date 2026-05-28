#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    unordered_set<string> word_dict;   // 存放词典，用于判断新单词是否合法
    unordered_set<string> cur_level;   // 存放当前 BFS 层的所有单词
    unordered_set<string> next_level;  // 存放下一 BFS 层将要扩散到的所有单词

    // 反向图
    // key 为新单词（后继）
    // value 数组存放所有能变成该新单词的旧单词（前驱）
    unordered_map<string, vector<string>> res_graph;

    vector<vector<string>> all_paths;  // 最终结果集
    vector<string> curr_path;          // DFS 回溯时的单条路径缓存

    // 初始化词典
    void build_dict(const vector<string>& word_list) {
        for (const auto& item : word_list) word_dict.emplace(item);
    }

    bool bfs_build_graph(const string& begin_word, const string& target_word) {
        bool is_found = false;
        cur_level.emplace(begin_word);  // 将起点加入当前层

        while (!cur_level.empty()) {
            /* * 【核心点：延迟去重】
             * 在开始处理当前层之前，把当前层出现的所有单词从总词典中彻底抹去。
             * 1.保证了同一层内多个不同的单词可以同时指向同一个新单词（保留多条最短路径）。
             * 2.防止了深层的波及回踩这一层的单词，从而陷入死循环或走回头路。
             */
            for (const auto& item : cur_level) word_dict.erase(item);

            // 遍历当前层的所有单词，向外扩散一步
            for (const string& word : cur_level) {
                string next_word = word;
                // 尝试改变当前单词的每一个位置的字符
                for (int i = 0; i < word.length(); ++i) {
                    char origin_char = next_word[i];
                    // 26 个字母轮流替换
                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        next_word[i] = ch;
                        // 如果变换后的新单词在词典中存在
                        if (word_dict.find(next_word) != word_dict.end()) {
                            // 撞到了终点
                            if (next_word == target_word) is_found = true;
                            // 建立反向边：新单词由旧单词转换而来
                            res_graph[next_word].emplace_back(word);
                            // 将新单词放入下一层集合中（自动去重）
                            next_level.emplace(next_word);
                        }
                    }
                    // 恢复当前位置的原始字符
                    next_word[i] = origin_char;
                }
            }

            // 如果在当前层已经发现了终点，说明当前层就是最短路径的最后一层，无需再向下扩展
            if (is_found) return true;

            // 准备进入下一层：将下一层的单词集合挪到当前层，清空下一层
            swap(cur_level, next_level);
            next_level.clear();
        }
        return false;
    }

    void dfs_find_paths(const string& curr_word, const string& target_word) {
        // 把当前单词加入到路径缓存的末尾
        curr_path.push_back(curr_word);

        if (curr_word == target_word) {
            // 此时 curr_path 存的是：[endWord, word_x, word_y, ..., beginWord]
            // 顺序是反的
            vector<string> correct_path = curr_path;
            // 把顺序反转过来，变成：[beginWord, ..., word_y, word_x, endWord]
            reverse(correct_path.begin(), correct_path.end());
            // 塞入最终结果集
            all_paths.emplace_back(correct_path);
        } else if (res_graph.find(curr_word) != res_graph.end()) {
            // 继续往回搜
            // 查一下反向图，看看有哪些旧单词（前驱）可以变成当前的 curr_word
            for (const auto& prev_word : res_graph[curr_word]) {
                // 递归进去，让 prev_word 变成接下来的当前单词
                dfs_find_paths(prev_word, target_word);
            }
        }

        // 回溯：当前节点的可能性尝试完了，把它从路径中弹出来
        // 腾出位置给别的分支（比如同一层的其他前驱节点）
        curr_path.pop_back();
    }

    // 主接口函数
    vector<vector<string>> findLadders(string beginWord, string endWord,
                                       vector<string>& wordList) {
        word_dict.clear();
        cur_level.clear();
        next_level.clear();
        res_graph.clear();
        all_paths.clear();
        curr_path.clear();
        build_dict(wordList);

        // 如果终点根本不在词典里，直接返回空结果
        if (word_dict.find(endWord) == word_dict.end()) return all_paths;

        // BFS 判定是否可达，并同步构建出最优反向图
        if (bfs_build_graph(beginWord, endWord)) {
            // 从终点出发，沿着反向图 DFS 捞出所有正解
            dfs_find_paths(endWord, beginWord);
        }
        return all_paths;
    }
};
