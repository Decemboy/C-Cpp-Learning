#include <stdio.h>
#include <stdlib.h>
//节点 链表定义 创建链表 创建节点 链表的死亡 尾部添加 指定下标插入 节点的删除 指定位置返回数据
typedef struct MyNode{
    int data;
    struct MyNode* pNext;
} Node;

typedef struct LinkList{
    Node* pHead;
    Node* pEnd;
    int length;
} LL;

LL*initList() { 
    LL* pTemp = (LL*)malloc(sizeof(LL)); 
    if(NULL==pTemp){
      return NULL;
    }
    pTemp->pHead = NULL;
    pTemp->pEnd = NULL;
    pTemp->length = 0;
    return pTemp;
}

Node*initNode(int data){
    Node* pTemp = (Node*)malloc(sizeof(Node)); 
    if(NULL==pTemp){
      return NULL;
    }
    pTemp->data = data;
    pTemp->pNext = NULL;
    return pTemp;
}
//链表的死亡
void deletList(LL**pList){
    if(NULL==*pList){
      return;
    }
    Node* pTemp = NULL;
    while((*pList)->pHead){
      pTemp = (*pList)->pHead;
      (*pList)->pHead = (*pList)->pHead->pNext;
      free(pTemp);
    }
    free(*pList);
    *pList = NULL;
}
//尾部插入append
void appendList(LL*pList,int val){
    if(NULL==pList){
      return;
    }
    Node* pTemp = initNode(val);
    if(NULL==pTemp){
      return;
    }
    //如果是空链表
    if(NULL==pList->pHead){
      pList->pHead = pList->pEnd = pTemp;
    }
    else{
      pList->pEnd->pNext = pTemp;
      pList->pEnd = pTemp;
    }
    pList->length++;
}
//指定下标插入节点
//判断插入位置
void insertList(LL*pList,int idx,int val){
    if(NULL==pList){
      return;
    }
    Node* pTemp = initNode(val);
    if(idx>=pList->length){
      pList->pEnd->pNext=pTemp;
      pList->pEnd = pTemp;
    }
    else if(idx<=0){
      pTemp->pNext = pList->pHead;
      pList->pHead = pTemp;
    }
    //中间
    else{
      Node* pInsertNode = pList->pHead;
      for (int i = 0; i < idx - 1;i++){
        pInsertNode = pInsertNode->pNext;
      }
      pTemp->pNext=pInsertNode->pNext;
      pInsertNode->pNext = pTemp;
    }
    pList->length++;
}
//指定位置删除
void deletNode(LL*pList,int idx){
    if(NULL==pList || pList->length==0){
      return;
    }
    if(idx<0 || idx>=pList->length){
      return;
    }
    Node* pTemp = NULL;
    if(0==idx){
      pTemp = pList->pHead;
      pList->pHead = pList->pHead->pNext;
    }
    else{
      Node* pCurNode = pList->pHead;
      for (int i = 0; i < idx - 1;i++){
        pCurNode = pCurNode->pNext;   
      }
      pTemp=pCurNode->pNext;
      pCurNode->pNext = pTemp->pNext;
      
      if(NULL==pCurNode->pNext){
        pList->pEnd = pCurNode;
      }
    }
    free(pTemp);
    pList->length--;
}
//指定位置返回下标idx
int findNode(LL*pList,int idx){
    if(NULL==pList || pList->length==0){
      return -1;
    }
    if(idx>=pList->length || idx<0){
      return -1;
    }
    Node* pTemp = pList->pHead;
    for (int i = 0; i < idx - 1;i++){
      pTemp = pTemp->pNext;
    }
    return pTemp->data;
}
int main() {
    LL* pList = initList();
    if(NULL==pList){
      return -1;
    }
    appendList(pList, 1);
    appendList(pList, 2);
    appendList(pList, 3);
    appendList(pList, 4);
    appendList(pList, 5);
    appendList(pList, 6);
    appendList(pList, 7);
    appendList(pList, 8);

    insertList(pList, 0, 9);
    insertList(pList, 2, 10);
    insertList(pList, 1, 11);
    insertList(pList, 3, 12);
    insertList(pList, 2, 13);

    deletNode(pList,0);
    deletNode(pList,3);
    deletNode(pList,0);
    deletNode(pList,2);

    int tmp;
    tmp = findNode(pList, 1);


    deletList(&pList);
    return 0;
}