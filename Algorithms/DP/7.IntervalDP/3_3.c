#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int** dp;
int* data;

int minScoreTriangulation(int* values, int valuesSize) {
    dp = malloc(sizeof(*dp) * valuesSize);
    data = calloc(valuesSize * valuesSize, sizeof(*data));
    for (int i = 0; i < valuesSize; ++i) dp[i] = data + i * valuesSize;

    for (int i = valuesSize - 3; i >= 0; --i) {
        for (int j = i + 2; j < valuesSize; ++j) {
            int res = 0x7fffffff;
            for (int m = i + 1; m < j; ++m) {
                res = MMIN(res, values[i] * values[m] * values[j] + dp[i][m] + dp[m][j]);
            }
            dp[i][j] = res;
        }
    }
    return dp[0][valuesSize - 1];
}
