#include <stdio.h>
#include <stdlib.h>

// 链表节点结构体（命名更简洁，添加const注释）
typedef struct Node {
    int data;           // 节点存储的数据
    struct Node* next;  // 指向下一个节点的指针
} Node;

// 链式队列结构体（精简命名，语义更清晰）
typedef struct Queue {
    Node* head;  // 队头指针
    Node* tail;  // 队尾指针
    int size;    // 新增：队列元素个数，避免遍历统计
} Queue;

/**
 * @brief 初始化队列
 * @return 成功返回队列指针，失败返回NULL
 */
Queue* queue_init() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        perror("malloc failed to create queue");  // 替换printf，输出系统错误信息
        return NULL;
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;  // 初始化大小为0
    return queue;
}

/**
 * @brief 创建新节点
 * @param val 节点存储的数值
 * @return 成功返回节点指针，失败返回NULL
 */
static Node* create_node(int val) {  // static：限定仅本文件可见，降低耦合
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        perror("malloc failed to create node");
        return NULL;
    }
    node->data = val;
    node->next = NULL;
    return node;
}

/**
 * @brief 入队操作
 * @param queue 队列指针（添加const限制，避免误改）
 * @param val 入队数值
 * @return 成功返回0，失败返回-1
 */
int queue_push(Queue* const queue, int val) {
    if (queue == NULL) {
        fprintf(stderr, "Error: queue is not initialized\n");  // 标准错误输出
        return -1;
    }

    Node* new_node = create_node(val);
    if (new_node == NULL) {
        return -1;
    }

    // 空队列：队头和队尾都指向新节点
    if (queue->head == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        // 非空队列：队尾节点指向新节点，更新队尾
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;  // 元素个数+1
    return 0;
}

/**
 * @brief 出队操作
 * @param queue 队列指针
 * @return 成功返回0，失败返回-1
 */
int queue_pop(Queue* const queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: queue is not initialized\n");
        return -1;
    }
    if (queue->head == NULL) {
        fprintf(stderr, "Error: queue is empty, cannot pop\n");
        return -1;
    }

    // 保存队头节点，用于释放
    Node* temp = queue->head;
    // 更新队头为下一个节点
    queue->head = queue->head->next;
    free(temp);  // 释放原队头节点
    temp = NULL; // 避免野指针

    // 队列为空时，队尾置空
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    queue->size--;  // 元素个数-1
    return 0;
}

/**
 * @brief 获取队头元素（添加安全校验）
 * @param queue 队列指针
 * @param out_val 输出参数：存储队头数值
 * @return 成功返回0，失败返回-1
 */
int queue_front(const Queue* const queue, int* out_val) {
    if (queue == NULL || queue->head == NULL) {
        fprintf(stderr, "Error: queue is null or empty\n");
        return -1;
    }
    if (out_val == NULL) {
        fprintf(stderr, "Error: out_val is null\n");
        return -1;
    }
    *out_val = queue->head->data;
    return 0;
}

/**
 * @brief 获取队尾元素（添加安全校验）
 * @param queue 队列指针
 * @param out_val 输出参数：存储队尾数值
 * @return 成功返回0，失败返回-1
 */
int queue_back(const Queue* const queue, int* out_val) {
    if (queue == NULL || queue->tail == NULL) {
        fprintf(stderr, "Error: queue is null or empty\n");
        return -1;
    }
    if (out_val == NULL) {
        fprintf(stderr, "Error: out_val is null\n");
        return -1;
    }
    *out_val = queue->tail->data;
    return 0;
}

/**
 * @brief 清空队列（释放所有节点，保留队列结构体）
 * @param queue 队列指针
 */
void queue_clear(Queue* const queue) {
    if (queue == NULL) {
        return;
    }
    Node* current = queue->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    // 重置队列状态
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

/**
 * @brief 销毁队列（清空+释放队列结构体）
 * @param queue 队列指针的指针（便于置空原指针）
 */
void queue_destroy(Queue** queue) {
    if (queue == NULL || *queue == NULL) {
        return;
    }
    queue_clear(*queue);  // 先清空所有节点
    free(*queue);         // 释放队列结构体
    *queue = NULL;        // 置空原指针，避免野指针
}

/**
 * @brief 获取队列大小
 * @param queue 队列指针
 * @return 成功返回队列大小，失败返回-1
 */
int queue_size(const Queue* const queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: queue is not initialized\n");
        return -1;
    }
    return queue->size;
}

// 测试主函数
int main(void) {
    Queue* queue = queue_init();
    if (queue == NULL) {
        return EXIT_FAILURE;  // 标准退出码：失败
    }

    // 入队操作
    if (queue_push(queue, 1) != 0) {
        fprintf(stderr, "Push 1 failed\n");
    }
    if (queue_push(queue, 2) != 0) {
        fprintf(stderr, "Push 2 failed\n");
    }

    // 出队操作
    if (queue_pop(queue) != 0) {
        fprintf(stderr, "Pop failed\n");
    }

    // 再次入队
    if (queue_push(queue, 3) != 0) {
        fprintf(stderr, "Push 3 failed\n");
    }

    // 获取队头、队尾
    int head_val, tail_val;
    if (queue_front(queue, &head_val) == 0) {
        printf("Queue front: %d\n", head_val);  // 预期输出：2
    }
    if (queue_back(queue, &tail_val) == 0) {
        printf("Queue back: %d\n", tail_val);    // 预期输出：3
    }

    // 打印队列大小
    printf("Queue size: %d\n", queue_size(queue));  // 预期输出：2

    // 销毁队列
    queue_destroy(&queue);
    if (queue == NULL) {
        printf("Queue destroyed successfully\n");
    }

    return EXIT_SUCCESS;  // 标准退出码：成功
}