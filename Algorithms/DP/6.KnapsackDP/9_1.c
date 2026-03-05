#include <stdlib.h>
#include <string.h>

#define MAX_DEEP 2001

int mmax(int a, int b) { return a > b ? a : b; }

typedef struct {
    int cost;
    int weight;
} Item;

typedef struct {
    int item_cnt;
    Item items[MAX_DEEP];
} Group;

int maxValueOfCoins(int** piles, int pilesSize, int* pilesColSize, int limit) {
    Group* gps = malloc(sizeof(*gps) * pilesSize);
    for (int i = 0; i < pilesSize; ++i) {
        int presum = 0;
        gps[i].item_cnt = 0;
        for (int j = 0; j < pilesColSize[i]; ++j) {
            presum += piles[i][j];
            gps[i].items[gps[i].item_cnt].cost = j + 1;
            gps[i].items[gps[i].item_cnt].weight = presum;
            ++(gps[i].item_cnt);
        }
    }

    int rows = pilesSize + 1;
    int cols = limit + 1;
    int* dp = calloc(cols, sizeof(*dp));
    for (int i = 1; i < rows; ++i) {
        for (int j = cols - 1; j > 0; --j) {
            int p = dp[j];
            for (int k = 0; k < gps[i - 1].item_cnt; ++k) {
                int cost = gps[i - 1].items[k].cost;
                int weight = gps[i - 1].items[k].weight;
                if (cost <= j) p = mmax(p, dp[j - cost] + weight);
            }
            dp[j] = p;
        }
    }

    return dp[cols - 1];
}