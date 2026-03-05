#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mmax(long long a, long long b) { return a > b ? a : b; }

int main() {
    int t, m;
    scanf("%d%d", &t, &m);

    int (*choice)[2] = malloc(sizeof(*choice) * m);
    for (int i = 0; i < m; ++i) scanf("%d%d", &choice[i][0], &choice[i][1]);

    int rows = m + 1;
    int cols = t + 1;
    long long* dp = calloc(cols, sizeof(*dp));

    // O(m * t²)
    for (int i = 1; i < rows; ++i) {
        int cost = choice[i - 1][0];
        int val = choice[i - 1][1];
        for (int j = cols - 1; j > 0; --j) {
            for (int k = 1; k * cost <= j; ++k) {
                dp[j] = mmax(dp[j], dp[j - k * cost] + k * val);
            }
        }
    }

    printf("%lld", dp[cols - 1]);
}