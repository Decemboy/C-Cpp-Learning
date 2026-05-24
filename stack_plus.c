#include <stdio.h>
#include <stdlib.h>

// 初始容量（不再固定死最大容量）
//宏定义的变量 大写字母表示
#define INIT_CAPACITY 4

// 动态栈结构体
typedef struct Mystack {
    //*data=data[0] 就是栈的第一个元素
    int* data;      // 动态数组指针（替代固定数组）储存栈元素
    int top;        // 栈顶元素个数
    int capacity;   // 当前栈最大容量
} STACK;
// 1. 初始化栈（动态分配）
STACK* initStack() {
    //栈结构体本身分配内存
    STACK* pStack = (STACK*)malloc(sizeof(STACK));
    if (pStack == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    //动态分配数组空间 大小为4个int类型
    pStack->data = (int*)malloc(sizeof(int) * INIT_CAPACITY);
    //如果数组分配失败 必须把刚才分配的结构体释放 避免内存泄漏
    if (pStack->data == NULL) {
        printf("数组内存分配失败\n");
        free(pStack);
        return NULL;
    }
    //初始化栈顶为0 表示空栈
    pStack->top = 0;
    //初始化栈的最大容量为4
    pStack->capacity = INIT_CAPACITY;
    //返回创建好的栈
    return pStack;
}
// 2. 判断栈满
int fullStack(STACK* pStack) {
    //判断栈是否存在
    if (pStack == NULL) {
        printf("栈不存在\n");
        return 0;
    }
    //元素个数==容量->满
    //如果等式成立返回值1 表示栈满
    return pStack->top == pStack->capacity;
}
// 3. 判断栈空
int emptyStack(STACK* pStack) {
    if (pStack == NULL) {
        printf("栈不存在\n");
        return 0;
    }
    //栈空 top=0
    //如果等式成立返回值1 表示栈空
    return pStack->top == 0;
}
// 4. 动态扩容
//如果栈满了 自动把容量扩大到原来的二倍
int resizeStack(STACK* pStack) {
    //如果栈不存在 直接返回失败
    if (pStack == NULL) return 0;
    //新容量为原来的二倍
    int newCapacity = pStack->capacity * 2;
    //分配更大的内存 保留原来的数据
    int* newData = (int*)realloc(pStack->data, sizeof(int) * newCapacity);
    //如果扩容失败返回值0
    if (newData == NULL) {
        printf("扩容失败\n");
        return 0;
    }
    //更新栈的数据
    pStack->data = newData;
    //更新栈的容量
    pStack->capacity = newCapacity;
    //扩容成功返回值1
    return 1;
}
// 5. 入栈（自动扩容）
void pushStack(STACK* pStack, int val) {
    //判断栈是否存在
    if (pStack == NULL) {
        printf("栈不存在，无法入栈\n");
        return;
    }
    // 满了就自动扩容
    if (fullStack(pStack)) {
        //判断是否扩容成功
        if (!resizeStack(pStack)) {
            printf("入栈失败（扩容失败）\n");
            return;
        }
    }
    //把值放到栈顶 栈值+1
    pStack->data[pStack->top++] = val;
}
// 6. 出栈
void popStack(STACK* pStack) {
    //判断栈是否存在
    if (pStack == NULL) {
        printf("栈不存在，无法出栈\n");
        return;
    }
    //判断是否是空栈
    if (emptyStack(pStack)) {
        printf("栈为空，无法出栈\n");
        return;
    }
    //出栈 top-1
    pStack->top--;
}
// 7. 获取栈顶元素（增加空指针/空栈检查，安全性提高）
int topStack(STACK* pStack) {
    //判断栈是否存在 返回值-1 不会访问栈顶元素
    if (pStack == NULL) {
        printf("栈不存在！\n");
        return -1; 
    }
    //判断栈是否为空 返回值-1 不会访问栈顶元素
    if (emptyStack(pStack)) {
        printf("栈为空，无栈顶元素！\n");
        return -1;
    }
    //数组下标从0开始 栈顶元素为top-1
    return pStack->data[pStack->top - 1];
}
// 8. 销毁栈（彻底释放内存，修复内存泄漏）
void destroyStack(STACK** pStack) {
    if (*pStack != NULL) {
        // 先释放数组
        free((*pStack)->data);
        // 再释放结构体
        free(*pStack);
        *pStack = NULL; // 指针置空，避免野指针
    }
}
//测试主函数
int main() {
    STACK* pStack = initStack();

    //测试大量入栈 → 自动触发扩容
    for (int i = 1; i <= 10; i++) {
        pushStack(pStack, i);
    }
    //测试出栈
    popStack(pStack);
    //测试空栈 不是空栈继续出栈
    while (!emptyStack(pStack)) {
        popStack(pStack);
    }
    //空栈不会再访问栈顶元素
    topStack(pStack); 
    //销毁栈，彻底释放内存
    destroyStack(&pStack);
    return 0;
}