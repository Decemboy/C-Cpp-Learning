#include <stdio.h>
#include <stdlib.h>
// 栈（stack）
#define STACK_LEN 10 //栈的最大容量宏定义为10

typedef struct Mystack {  // 顺序结构的栈
  int dataArr[STACK_LEN]; //分配一个可以存放10个数据的数组（栈的储存空间）
  int top;//栈顶指针 栈顶元素的位置
  /* 
  top的含义：
  top=0 栈为空（没有元素）
  top=n 栈中有n个元素 栈顶元素在dataArr[n-1]位置
  top=STACK_LEN 栈满（无法再入栈） 因为数组的空间有限 会出现满栈的情况
  */
} STACK;
// 创建
STACK* initStack() { //initialize 初始化
  //为栈结构分配内存
  STACK* pStack = (STACK*)malloc(sizeof(STACK));
  //malloc分配的是随机垃圾值 判断内存分配失败的情况
  if (NULL == pStack) {
    return NULL;
  }
  //初始化栈顶指针 顶部为0
  pStack->top = 0;
  //返回栈的指针
  return pStack;
}
//判断栈满
int fullStack(STACK* pStack) {
  //检查栈是否存在 指针非空
  if (NULL == pStack) {
    printf("栈不存在\n");
    return 0;
  }
  //栈顶指针=>最大长度 栈满返回1 否则返回0
  if (pStack->top >= STACK_LEN) {
    return 1;
  }
  //0表示栈未满或者栈不存在
  return 0;
}
//栈空判断
int emptyStack(STACK* pStack){
  //检查栈是否存在
  if (NULL == pStack) {
    printf("栈不存在\n");
    return 0;
  }
  //top 栈顶为0 返回1 否则返回0
  if(0==pStack->top){
    return 1;
  }
  //0表示栈不存在或者栈空
  return 0;
}
//入栈
void pushStack(STACK* pStack, int val) {
  //栈不存在直接返回
  if (NULL == pStack) {
    printf("栈不存在，不能入栈\n");
    return;
  }
  //栈满直接返回
  if(fullStack(pStack)==1){
    printf("栈已满，不能入栈\n");
    return;
  }
  //将值存入栈顶 然后top+1
  //因为第一开始初始化栈 所以是空栈 向一个底部密封的容器添加数据 栈顶指针上移
  pStack->dataArr[pStack->top++] = val;
}
//出栈
void popStack(STACK*pStack){
  //判断栈是否存在
  if (NULL == pStack) {
    printf("栈不存在，不能出栈\n");
    return;
  }
  //判断是否是空栈 
  if(1==emptyStack(pStack)){
    printf("栈为空，不能出栈\n");
    return;
  }
  //栈顶指针下移（逻辑删除栈顶元素）
  //栈顶元素不在被访问 也就是越界处理 并不是实际上的删除
  pStack->top--;
}
//获取栈顶元素 
//因为第一开始定义就是top 栈顶元素的位置 所以获取栈顶元素
int topStack(STACK* pStack) {  //这边的pStack指针 我们认为应该是一个非空指针 因为空指针没法用
  //正常表示 如果pStack为空 会出错
  //top 元素个数 数组下标从0开始
  return pStack->dataArr[pStack->top-1]; 
}
//释放栈的内存
//用二级指针 要修改原指针的指向（置空）
void clearStack(STACK**pStack){
  //栈指针非空
  if(NULL!=*pStack){
  //释放栈的堆内存
    free(*pStack);
  //指针置空
    *pStack = NULL;
  }
}
int main() {
  //初始化栈 栈为空栈（top=0）
  STACK* pStack=NULL;
  pStack = initStack();
  pushStack(pStack, 1);
  pushStack(pStack, 2);
  popStack(pStack);
  pushStack(pStack, 3);
  int val = topStack(pStack);

  return 0; 
}
