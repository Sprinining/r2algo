## 排序

### 参数

`qsort` 是 C 标准库（`stdlib.h`）提供的一个**通用排序函数**。

```c
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));
```

数组起始地址 base:

```c
int arr[5];
qsort(arr, ...);
```

元素个数 nmemb:

```c
sizeof(arr) / sizeof(arr[0])
```

每个元素的大小 size:

```c
sizeof(int)
```

比较函数 compar:

```c
int cmp(const void *a, const void *b);
```

返回值规则：

| 返回值 | 含义   |
| ------ | ------ |
| < 0    | a 在前 |
| = 0    | 相等   |
| > 0    | b 在前 |

### cmp 写法

错误写法：

```c
return *(int*)a - *(int*)b;
```

如果数据很大可能溢出。

正确写法：

```c
int cmp(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}
```

### 二维数组

```c
#include <stdio.h>
#include <stdlib.h>

// 1. 静态二维数组的比较函数
int cmp_static_2d(const void* a, const void* b) {
    // 静态数组中，a 拿着的是行数据 arr[i] 的物理起点
    // 类型是 int[3]，即一个拥有 3 个 int 的一维数组
    // 作为参数传递时退化为一级指针，变成 int* 类型
    // 退化后的物理地址刚好等于 &arr[i][0]
    printf("  [cmp_static] a 存的地址=%p, 指向的数字=%d\n", a, *(int*)a);
    int* x = (int*)a;
    int* y = (int*)b;
    return x[0] - y[0];
}

// 2. 动态数组的比较函数
int cmp_dynamic(const void* a, const void* b) {
    // 动态数组中，主数组格子里装的是行指针（int*）
    // qsort 传过来的 a 是“存放这个行指针的格子的地址”，即二级指针（int**）
    // 所以必须通过 *(int**)a，伸手把格子里存的那个“行指针”掏出来！
    int* x = *(int**)a;
    int* y = *(int**)b;

    printf(
        "  [cmp_dynamic] a 存的格子地址=%p, 掏出来的行指针=%p, 指向的数字=%d\n",
        a, (void*)x, x[0]);

    return x[0] - y[0];
}

int main() {
    // 方式一：静态二维数组 int arr1[2][3]
    printf("=== 验证方式一：静态二维数组 int arr[2][3] ===\n");
    // 整个二维数组在内存中是一个“统一的整体”
    // 编译器在栈上只“斩下一刀”分配了 24 字节。
    // 尽管栈是向下生长的，但数组作为单一变量，其内部元素必须遵循“行优先原则”：
    // 它的微观排布是绝对正向递增的
    // 所以第二行的首地址完美的、紧紧地接在第一行最后一个元素之后
    int arr1[2][3] = {{2, 4, 6}, {1, 3, 5}};
    for (int i = 0; i < 2; ++i) {
        // arr1[i] 的官方类型是 int[3]，sizeof 为 3 * 4 = 12 字节
        printf("arr1[%d]的行起点地址=%p, sizeof=%zu\n", i, (void*)arr1[i],
               sizeof(arr1[i]));
        for (int j = 0; j < 3; ++j) {
            printf("  arr1[%d][%d]=%d, 地址=%p\n", i, j, arr1[i][j],
                   (void*)&arr1[i][j]);
        }
    }
    printf("开始 qsort 排序...\n");
    // 每个格子是行数据，大小为 sizeof(arr1[0]) = 12 字节
    qsort(arr1, 2, sizeof(arr1[0]), cmp_static_2d);
    printf("排序后结果: arr1[0][0]=%d, arr1[1][0]=%d\n\n", arr1[0][0],
           arr1[1][0]);

    // 方式二：动态指针数组 int* arr2[2] (行指针存在栈上，数据在堆上或静态区)
    printf("=== 验证方式二：动态指针数组 int* arr2[2] ===\n");
    // rowA 和 rowB
    // 是“两个彼此独立”的局部变量。在现代计算机中，栈内存是“向下生长（由高到低）”的。
    // 先创建的 rowA 占据了高地址，后创建的 rowB 被压入了更低的地址。
    // 因此微观上虽然每行内部连续递增，但宏观上 rowB 的首地址反而比 rowA 更小
    // 表现出来的诡异现象就是：第二行的结尾（rowB[2]）刚好顶在了第一行开头（rowA[0]）的屁股后面。
    int rowA[3] = {
        2, 4, 6};  // 先声明，在栈的高地址方向，行内三个元素内存地址连续递增
    int rowB[3] = {
        1, 3, 5};  // 后声明，在栈的低地址方向，行内三个元素内存地址连续递增

    // arr2 是一个包含 2 个 int* 指针的数组，即指针数组
    int* arr2[2] = {rowA, rowB};

    for (int i = 0; i < 2; ++i) {
        // arr2[i] 的官方类型是 int*（指针），在64位系统下 sizeof 永远是 8 字节
        printf("arr2[%d]指针变量自身的地址=%p, 里面存的行指针=%p, sizeof=%zu\n",
               i, (void*)&arr2[i], (void*)arr2[i], sizeof(arr2[i]));
        for (int j = 0; j < 3; ++j) {
            printf("  arr2[%d][%d]=%d, 地址=%p\n", i, j, arr2[i][j],
                   (void*)&arr2[i][j]);
        }
    }
    printf("开始 qsort 排序...\n");
    // 主数组里面装的是指针
    // 所以每个格子大小是单个指针的大小 sizeof(arr2[0]) = 8 字节
    qsort(arr2, 2, sizeof(arr2[0]), cmp_dynamic);
    printf("排序后结果: arr2[0][0]=%d, arr2[1][0]=%d\n\n", arr2[0][0],
           arr2[1][0]);

    // 方式三：双重动态二级指针 int** arr3 (全套娃，第一层和第二层都在堆上)
    printf("=== 验证方式三：双重动态二级指针 int** arr3 ===\n");
    // 第一步：在堆上申请一个能放下 2 个 int* 指针的连续空间
    int** arr3 = (int**)malloc(2 * sizeof(int*));

    // 第二步：为每一行独立申请能放 3 个 int 数字的空间，并赋值
    // 单次 malloc 内部由于是一维数组，所以行内的三个元素内存地址绝对是连续的。
    // 但是两次 malloc 之间由于是独立申请，堆内存可能早就被其他程序插足
    // 因此行与行之间在内存中是离散的。
    // 导致的结果就是：第二行的首地址（arr3[1][0]）和第一行的结尾（arr3[0][2]）毫无关联
    arr3[0] = (int*)malloc(3 * sizeof(int));
    arr3[0][0] = 2;
    arr3[0][1] = 4;
    arr3[0][2] = 6;

    arr3[1] = (int*)malloc(3 * sizeof(int));
    arr3[1][0] = 1;
    arr3[1][1] = 3;
    arr3[1][2] = 5;

    for (int i = 0; i < 2; ++i) {
        // arr3[i] 的官方类型依然是 int*（指针），sizeof 固定是 8 字节
        printf("arr3[%d]堆格子自身的地址=%p, 里面存的行指针=%p, sizeof=%zu\n",
               i, (void*)&arr3[i], (void*)arr3[i], sizeof(arr3[i]));
        for (int j = 0; j < 3; ++j) {
            printf("  arr3[%d][%d]=%d, 地址=%p\n", i, j, arr3[i][j],
                   (void*)&arr3[i][j]);
        }
    }
    printf("开始 qsort 排序...\n");
    // 第一层主数组里装的依然指针，单格大小是 sizeof(arr3[0]) = 8 字节
    qsort(arr3, 2, sizeof(arr3[0]), cmp_dynamic);
    printf("排序后结果: arr3[0][0]=%d, arr3[1][0]=%d\n\n", arr3[0][0],
           arr3[1][0]);

    return 0;
}

```

```css
=== 验证方式一：静态二维数组 int arr[2][3] ===
arr1[0]的行起点地址=0x7ffd029ee3d0, sizeof=12
  arr1[0][0]=2, 地址=0x7ffd029ee3d0
  arr1[0][1]=4, 地址=0x7ffd029ee3d4
  arr1[0][2]=6, 地址=0x7ffd029ee3d8
arr1[1]的行起点地址=0x7ffd029ee3dc, sizeof=12
  arr1[1][0]=1, 地址=0x7ffd029ee3dc
  arr1[1][1]=3, 地址=0x7ffd029ee3e0
  arr1[1][2]=5, 地址=0x7ffd029ee3e4
开始 qsort 排序...
  [cmp_static] a 存的地址=0x7ffd029ee3d0, 指向的数字=2
排序后结果: arr1[0][0]=1, arr1[1][0]=2

=== 验证方式二：动态指针数组 int* arr2[2] ===
arr2[0]指针变量自身的地址=0x7ffd029ee3a0, 里面存的行指针=0x7ffd029ee3c4, sizeof=8
  arr2[0][0]=2, 地址=0x7ffd029ee3c4
  arr2[0][1]=4, 地址=0x7ffd029ee3c8
  arr2[0][2]=6, 地址=0x7ffd029ee3cc
arr2[1]指针变量自身的地址=0x7ffd029ee3a8, 里面存的行指针=0x7ffd029ee3b8, sizeof=8
  arr2[1][0]=1, 地址=0x7ffd029ee3b8
  arr2[1][1]=3, 地址=0x7ffd029ee3bc
  arr2[1][2]=5, 地址=0x7ffd029ee3c0
开始 qsort 排序...
  [cmp_dynamic] a 存的格子地址=0x7ffd029ee3a0, 掏出来的行指针=0x7ffd029ee3c4, 指向的数字=2
排序后结果: arr2[0][0]=1, arr2[1][0]=2

=== 验证方式三：双重动态二级指针 int** arr3 ===
arr3[0]堆格子自身的地址=0x365bb420, 里面存的行指针=0x365bb440, sizeof=8
  arr3[0][0]=2, 地址=0x365bb440
  arr3[0][1]=4, 地址=0x365bb444
  arr3[0][2]=6, 地址=0x365bb448
arr3[1]堆格子自身的地址=0x365bb428, 里面存的行指针=0x365bb460, sizeof=8
  arr3[1][0]=1, 地址=0x365bb460
  arr3[1][1]=3, 地址=0x365bb464
  arr3[1][2]=5, 地址=0x365bb468
开始 qsort 排序...
  [cmp_dynamic] a 存的格子地址=0x365bb420, 掏出来的行指针=0x365bb440, 指向的数字=2
排序后结果: arr3[0][0]=1, arr3[1][0]=2

```

### 数组传参会退化为指针

```c
// sums 有 5 列
printf("%d %d %d", sizeof(int), sizeof(sums), sizeof(*sums) * cols);
// 4 8 20
```

函数参数中的数组，本质是指针，sizeof 拿到的是地址大小（8 字节），不是数组长度。为什么指针是 8 字节？因为我都电脑是 64 位系统，地址长度 = 64 位 = 8 字节。