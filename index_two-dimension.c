#include<stdio.h>
#include<stdlib.h>
// 函数：申请num个int大小的动态内存，并返回首地址
void ranking(int* p, int n);
void print_ranking(int* p, int n);
int* getMem(int num) {
  //调用calloc申请内存
  int* p = (int*)calloc(num,sizeof(int));
  //返回申请到的地址
  return p;
}
int main(void) {
  int n;
  printf("please enter positive integer:\n");
  scanf("%d", &n);
  int* p = getMem(n);
  int m;
  for (int i = 0;i<n;i++){
     scanf("%d", &m);
     p[i] = m;
  }
  ranking(p, n);
  print_ranking(p, n);
  free(p);
  p = NULL;

  return 0;
}
void ranking(int* p, int n) { 
  int ret = 0;
  for (int i = 0; i < n-1;i++){
    for (int j = 0; j < n - i - 1;j++){
        if(p[j]<p[j+1]){
          ret=p[j+1];
          p[j + 1] = p[j];
          p[j] = ret;
        }
    } 
  }
 }
 void print_ranking(int* p, int n) {
   for (int i = 0; i < n;i++){
     printf("%d\t", p[i]);
   }
}