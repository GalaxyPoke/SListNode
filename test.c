#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;

typedef struct SListNode {
    SLTDataType data;
    struct SListNode* next;
} SListNode;

// 函数声明，确保在使用之前已经定义
SListNode* CreateNode(SLTDataType value);
SListNode* CreateSlist(int num);
void PrintList(SListNode* head);
void DestroyList(SListNode** pphead);
void SListPushFront(SListNode** pphead, SLTDataType value);
void SListPopFront(SListNode** pphead);
void SListPushBack(SListNode** pphead, SLTDataType value);
void SListPopBack(SListNode** pphead);
void InsertNodeBeforePos(SListNode** pphead, int pos, SLTDataType value);
void InsertNodeAfterPos(SListNode** pphead, int pos, SLTDataType value);
void DeleteNodesAfterPos(SListNode** pphead, int pos);
void DeleteNodeAtPos(SListNode** pphead, int pos);
void SListModify(SListNode* pos, SLTDataType x);

// 主函数，使用上述定义的函数
int main() {
    SListNode* head = NULL;  // 初始化链表为空

    // 使用创建链表函数
    head = CreateSlist(5);  // 创建包含 5 个节点的链表，节点数据为 0 到 4
    PrintList(head);        // 打印链表

    // 演示插入和删除操作
    SListPushFront(&head, 100);  // 在链表头插入数据 100
    PrintList(head);             // 打印链表

    SListPushBack(&head, 200);   // 在链表尾插入数据 200
    PrintList(head);             // 打印链表

    SListPopFront(&head);        // 从链表头部删除一个节点
    PrintList(head);             // 打印链表

    SListPopBack(&head);         // 从链表尾部删除一个节点
    PrintList(head);             // 打印链表

    InsertNodeBeforePos(&head, 2, 300);  // 在位置 2 前插入数据 300
    PrintList(head);                    // 打印链表

    InsertNodeAfterPos(&head, 2, 400);   // 在位置 2 后插入数据 400
    PrintList(head);                     // 打印链表

    DeleteNodeAtPos(&head, 3);           // 删除位置 3 的节点
    PrintList(head);                     // 打印链表

    DeleteNodesAfterPos(&head, 1);       // 删除位置 1 之后的所有节点
    PrintList(head);                     // 打印链表

    SListModify(head->next, 500);        // 修改位置 1 的节点数据为 500
    PrintList(head);                     // 打印链表

    DestroyList(&head);                  // 销毁整个链表
    PrintList(head);                     // 打印链表，应显示为空

    return 0;
}
