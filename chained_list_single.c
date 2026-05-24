#include <stdio.h>
#include <stdlib.h>
//Node 节点
//在实现链表之前，先确定表中的某一个节点类型
typedef struct  MyNode //typedef作用是把MyNode重命名为NODE
{
  int data;//节点存储的核心数据（此处为整型，可根据需求修改为字符、结构体等）
  struct MyNode* pNext;//指向下一个节点的指针，是链表 “链式” 的核心 —— 通过指针连接多个节点，最后一个节点的pNext为NULL
  //插入和删除是链表的核心操作，而这些操作的本质就是修改 pNext 的指向
}NODE;
//单向链表整体结构定义
typedef struct LinkLsit{
  NODE* pHead;//指向链表第一个节点（头节点）的指针 空链表时为NULL
  NODE* pEnd;//指向链表最后一个节点（尾节点）的指针 空链表时为NULL
  int length;//记录链表的节点总数（长度） 避免每次统计长度都遍历链表 提升效率
} LL;
//创建单链表
LL* initList(){  //init 初始化 
    LL* pTemp = (LL*)malloc(sizeof(LL)); 
    //pTemp的作用 你要销毁链表 必须一个一个节点释放内存 但释放之前 你必须先把下一个节点的地址保存下来
    //调用malloc分配一块大小为LL结构体的内存 用于存储链表的管理信息（头指针 尾指针 长度）
    if(NULL==pTemp ){  
      return NULL;
    }
    //检查内存分配是否成功（如内存不足时malloc返回NULL） 失败则直接返回NULL 避免后续操作出错 
    //因为malloc分配的内存随机垃圾值，所以需要检查分配是否成功
    pTemp->pHead = NULL;
    pTemp->pEnd = NULL;
    //空链表没有任何节点 因此头指针 尾指针都置为NULL
    pTemp->length = 0;
    //空链表长度为0
    return pTemp;
    //返回初始化完成的链表管理结构指针
}
//创建链表的一个节点
//创建一个存储指定数据的链表节点，返回节点指针
NODE* initNode(int data) { 
    NODE* pTemp = (NODE*)malloc(sizeof(NODE)); 
    //为单个节点分配内存（大小为NODE结构体）
    if(NULL==pTemp){
      return NULL;
    }
    //依旧判断是否分配成功
    pTemp->data = data;
    //将传入的data赋值给节点的data成员 完成数据存储
    pTemp->pNext = NULL;
    //新节点默认不指向任何节点（后续可通过指针修改 连接到链表中）
    return pTemp;
    //返回创建好的新节点指针
}
//链表的死亡
void delList(LL**pList ){ //链表管理结构的二级指针
    if(NULL==*pList){
      printf("链表不存在\n");
      return;
      //检查链表是否存在（若*pList为NULL 说明链表已销毁或未创建） 直接返回并提示
      //*pList = main 函数里那个链表指针本身
    }
    NODE* pTemp = NULL;
    //定义临时指针 用于保存待释放的节点地址
    while((*pList)->pHead){
      //循环条件 头指针不为NULL（链表还有节点）
      //利用循环遍历链表
      pTemp = (*pList)->pHead;
      //保存当前头节点的地址
      (*pList)->pHead = (*pList)->pHead->pNext;
      //将头指针指向下一个节点（链表 “头移”）
      free(pTemp);
      //释放原头节点的内存
    }
    free(*pList);
    //释放链表管理结构的内存
    *pList = NULL;
    //将原链表指针置为NULL 避免后续误操作（野指针）
}
//这里是在尾部添加 append 附加
void appendList(LL*pList,int val){ 
    if(NULL==pList ){
      printf("链表不存在 ，无法添加\n");
      return;
    }
    //创建新节点
    NODE* pTemp = initNode(val);
    if(NULL==pTemp){
      printf("节点分配失败，无法添加\n");
      return;
    }
    if(NULL==pList->pHead){//空链表
    pList->pHead = pList->pEnd = pTemp;//空链表中追加节点，既是头也是尾
    }
    //非空链表 链表尾节点next指向新节点 更新尾节点
    else {
    pList->pEnd->pNext = pTemp;
    pList->pEnd = pTemp;
    }
    //链表长度加一
    pList->length++;
}
//指定下标插入节点
void insertList(LL*pList,int idx,int val){ ////insert 插入 idx 是插入的位置 index指针 索引
    //依旧分情况讨论
    if(NULL==pList ){
    printf("链表不存在 ，无法插入\n");
    return;
    }
    NODE* pTemp = initNode(val);
    if(NULL==pTemp){
    printf("节点分配失败，无法添加\n");
    return;
    }
    //在链表存在的情况下 进行节点的插入 讨论插入时的情况
    if(idx>=pList->length){//插入的下标超出元素的个数，直接在尾部
    pList->pEnd->pNext = pTemp;
    pList->pEnd = pTemp;
    }
    else if(idx<=0){//插入的下标小于等于0，在头节点插入
    pTemp->pNext = pList->pHead;
    pList->pHead = pTemp;
    }
    else{//中间插入（头尾间）
    NODE* pInsertNode = pList->pHead;//找插入的节点
    for (int i = 0; i < idx - 1;i++){//循环停在插入位置的前面
    pInsertNode = pInsertNode->pNext;
    }
    pTemp->pNext = pInsertNode->pNext;
    pInsertNode->pNext = pTemp;
  }
    //链表长度加一 因为你添加新节点了
    pList->length++;
}
//对节点的删除
void deleteNode(LL*pList,int idx){
    if(NULL==pList||0==pList->length ){
    printf("链表不存在 ，无法删除\n");
    return;
    }
    //检查删除的下标是否合法
    if(idx<0||idx>=pList->length){
    printf("删除位置错误\n");
    return;
    }
    //保持待删除位置的节点
    NODE* pTemp = NULL;
    //删除头节点
    if(0==idx){
    pTemp = pList->pHead;//保留原头节点
    pList->pHead = pList->pHead->pNext;//头指针移到下一个节点
    }
    //删除中间/尾部节点
    else{
    NODE* pCurNode = pList->pHead;
    //找到删除位置的前一个节点
    for (int i = 0; i < idx - 1;i++){
    pCurNode = pCurNode->pNext;
    }
    pTemp = pCurNode->pNext;//保存待删节点
    pCurNode->pNext= pTemp->pNext;//前节点next跳过待删除节点
    //特殊情况 删除的是尾节点->更新pEnd指针
    if(NULL==pCurNode->pNext){
      pList->pEnd = pCurNode;
    }
    }
    //释放待删除节点的内存
    free(pTemp);
    //节点删除 链表长度减一
    pList->length--;
}
//查找指定位置数据 返回下标为idx的节点数据
int findData(LL*pList,int idx){
    // 先检查链表是否存在
    if (NULL == pList) {
    printf("链表不存在，无法查找\n");
    return -1;
    }
    // 再检查链表是否为空
    if (pList->length == 0) {
    printf("链表为空，无法查找\n");
    return -1;
    }
    // 最后检查下标合法性
    if (idx < 0 || idx >= pList->length) {
    return -1;
    }
    NODE* pTemp = pList->pHead;
    //遍历到指定下标节点
    for (int i = 0; i < idx;i++){
      pTemp = pTemp->pNext;
    }
    return pTemp->data;
  }
int main(void){
  LL*pList=initList();
  //调用initList创建空链表 指针赋值给pList
  if(NULL==pList){
    printf("链表创建不成功\n");
    return -1; //非0即为真，不存在返回-1 假的
    //检查链表创建是否成功 失败则打印提示并退出程序
  }
  //尾部追加
  appendList(pList, 1);
  appendList(pList, 2);
  //指定位置增加
  insertList(pList, 9, 999);
  insertList(pList, -2, 666);
  insertList(pList, 2, 123);
  //删除操作
  deleteNode(pList, 0);
  deleteNode(pList, 3);
  deleteNode(pList, 1);
  //查找指定位置数据
  int n;
  n=findData(pList, 1);
  delList(&pList);
  //调用delList销毁链表（传入pList的地址 因为函数需要二级指针）
  return 0; 
}