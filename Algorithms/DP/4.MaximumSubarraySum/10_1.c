#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = 3;
    // prefixSums[i] = 前 i 个数的前缀和
    int* prefixSums = malloc(sizeof(*prefixSums) * (numsSize + 1));
    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    int* res = malloc(sizeof(*res) * 3);
    int maxSum = 0x80000000;
    for (int i = 0; i <= numsSize - 3 * k; ++i) {
        int s1 = prefixSums[i + k] - prefixSums[i];
        for (int j = i + k; j <= numsSize - 2 * k; ++j) {
            int s2 = prefixSums[j + k] - prefixSums[j];
            for (int t = j + k; t <= numsSize - k; ++t) {
                int s3 = prefixSums[t + k] - prefixSums[t];
                int s = s1 + s2 + s3;
                if (s > maxSum) {
                    maxSum = s;
                    res[0] = i;
                    res[1] = j;
                    res[2] = t;
                }
            }
        }
    }

    return res;
}