#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;

typedef struct SListNode {
    SLTDataType data;
    struct SListNode* next;
} SListNode;

// ����������ȷ����ʹ��֮ǰ�Ѿ�����
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

// ��������ʹ����������ĺ���
int main() {
    SListNode* head = NULL;  // ��ʼ������Ϊ��

    // ʹ�ô���������
    head = CreateSlist(5);  // �������� 5 ���ڵ�������ڵ�����Ϊ 0 �� 4
    PrintList(head);        // ��ӡ����

    // ��ʾ�����ɾ������
    SListPushFront(&head, 100);  // ������ͷ�������� 100
    PrintList(head);             // ��ӡ����

    SListPushBack(&head, 200);   // ������β�������� 200
    PrintList(head);             // ��ӡ����

    SListPopFront(&head);        // ������ͷ��ɾ��һ���ڵ�
    PrintList(head);             // ��ӡ����

    SListPopBack(&head);         // ������β��ɾ��һ���ڵ�
    PrintList(head);             // ��ӡ����

    InsertNodeBeforePos(&head, 2, 300);  // ��λ�� 2 ǰ�������� 300
    PrintList(head);                    // ��ӡ����

    InsertNodeAfterPos(&head, 2, 400);   // ��λ�� 2 ��������� 400
    PrintList(head);                     // ��ӡ����

    DeleteNodeAtPos(&head, 3);           // ɾ��λ�� 3 �Ľڵ�
    PrintList(head);                     // ��ӡ����

    DeleteNodesAfterPos(&head, 1);       // ɾ��λ�� 1 ֮������нڵ�
    PrintList(head);                     // ��ӡ����

    SListModify(head->next, 500);        // �޸�λ�� 1 �Ľڵ�����Ϊ 500
    PrintList(head);                     // ��ӡ����

    DestroyList(&head);                  // ������������
    PrintList(head);                     // ��ӡ����Ӧ��ʾΪ��

    return 0;
}
