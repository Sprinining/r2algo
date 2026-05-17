## gdb

### 启动 / 退出

```shell
gdb 程序名        # 启动调试
q                # 退出 GDB
```

### 查看代码

```shell
l               # list → 显示当前附近代码（连续按 l 往下翻）
l 行号           # 显示某一行附近代码  例：l 30
l 函数名         # 显示某个函数的代码  例：l main
l 文件名:行号     # 多文件查看  例：l test.c:50
l 文件名:函数名   # 例：l test.c:func

show listsize     # 查看每次显示多少行代码
set listsize 30   # 让 GDB 每次显示 30 行代码（看得更爽）
```

### 运行程序

```shell
r                # run → 开始运行
r 参数1 参数2      # 带参数运行
c                # continue → 继续运行到下一个断点
ctrl + c         # 强制暂停程序
```

### 断点

```shell
b 行号            # 断点在某一行  例：b 20
b 函数名          # 断点在函数入口  例：b main
b 文件名:行号      # 例：b test.c:15
b 文件名:函数名    # 例：b test.c:func

info breakpoints  # 查看所有断点（简写 info b）
delete 断点编号    # 删除断点  例：delete 1
disable 断点编号   # 临时关闭断点
enable 断点编号    # 重新打开断点
delete            # 删除所有断点

# 两种打条件断点方式
# 1. 打断点时直接加条件
break filename.c:42 if save[i] > 0 
# 2. 先打断点，再加条件
break filename.c:42
condition 1 save[i] > 0
```

### 单步调试

```shell
n                # next → 下一步（不进函数）
s                # step → 进入函数内部
finish           # 跳出当前函数
until 行号        # 直接运行到某一行  例：until 50
return           # 立即结束当前函数
```

### 查看变量 / 指针 / 数组 / 结构体

```shell
p 变量            # 打印变量  例：p a
p &变量           # 打印变量地址
p *指针           # 打印指针指向的值
p 数组名          # 打印数组
p 数组名[下标]     # 打印数组某个元素
p 结构体.成员      # 打印结构体成员
p 指针->成员       # 指针结构体

display 变量      # 每次单步自动打印变量
undisplay 编号    # 取消自动打印
```

### 查看内存

```shell
x /Nfu 地址
x /10x 变量地址   # 以16进制显示10个单位内存
x /s 字符串地址   # 查看字符串
```

### 崩溃调试

```shell
bt               # 查看函数调用栈（程序崩溃必用）
f 栈帧编号        # 跳转到某一层栈  例：f 2
up               # 往上一层栈
down             # 往下一层栈
```

### 查看当前运行位置

```shell
where            # 现在停在哪一行
info frame       # 查看当前栈帧信息
info args        # 查看函数参数
info locals      # 查看所有局部变量（超级好用）
```

### 多文件调试

```shell
info sources     # 查看所有参与编译的源文件
info functions   # 查看所有函数
info variables   # 查看所有全局变量
```