#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <cstdlib>

typedef int SLTDataType; // 定义数据类型为整型，用SLTDataType代替int
//以提高代码的可读性和可维护性

// 定义单向链表的节点结构
typedef struct SListNode {
    SLTDataType data; // 数据域：存储节点的数据，这里为整型数据
    struct SListNode* next; // 指针域：指向链表中下一个节点的指针
} SListNode;

//创建新的节点
SListNode* CreateNode(SLTDataType value)
{
	SListNode* newNode = (SListNode*)malloc(sizeof(SListNode)); // 动态分配内存
	if (newNode == NULL) // 检查内存是否成功分配
	{
		perror("malloc fail");
		exit(-1);
	}
	newNode->data = value; // 设置节点的数据域
	newNode->next = NULL;  // 初始化指针域，目前此节点不指向其他节点
	return newNode;        // 返回新创建的节点
}

// 创建包含 num 个节点的单链表
SListNode* CreateSlist(int num)
{
	SListNode* phead = NULL; // 头指针，初始为空
	SListNode* ptail = NULL; // 尾指针，用于追踪链表末尾

	for (int i = 0; i < num; i++) {
		SListNode* newnode = CreateNode(i); // 创建一个新节点
		if (phead == NULL) {
			ptail = phead = newnode; // 如果链表为空，初始化头尾指针为第一个节点
		}
		else {
			ptail->next = newnode; // 将新节点链接到链表末尾
			ptail = newnode;       // 更新尾指针指向新的末尾节点
		}
	}
	return phead; // 返回链表头指针
}

//打印
void PrintList(SListNode* head)
{
	if (head == NULL) { // 如果头指针为 NULL，表示链表为空
		printf("The list is empty.\n");
	}
	else {
		printf("List: ");
		SListNode* current = head; // 使用一个临时指针从头节点开始遍历链表
				//保留 head 指针不变，使用另一个临时指针（current）进行遍历，
				//可以保证 head 指针始终指向链表的开始位置
		while (current != NULL) { // 遍历链表直到末尾
			printf("%d -> ", current->data); // 打印当前节点的数据
			current = current->next; // 移动到下一个节点
		}
		printf("NULL\n"); // 打印链表结束标志
	}
}

//摧毁
void DestroyList(SListNode** pphead)
{
	while (*pphead != NULL) {
		SListNode* temp = *pphead;       // 保存当前头节点
		*pphead = (*pphead)->next;       // 更新头指针到下一个节点
		free(temp);                      // 释放原头节点的内存
	}
	// 可选：确保链表完全清空后，外部指针也设置为NULL
	*pphead = NULL;
}


//头插
void SListPushFront(SListNode** pphead, SLTDataType value)
{
	SListNode* newNode = CreateNode(value); // 创建一个新节点
	newNode->next = *pphead; // 新节点的 next 指针指向当前的头节点
	*pphead = newNode;       // 更新头指针，现在它指向新的头节点
}

// 头删         注意：插入都不需要断言，删除需要断言，防止要删除得第一个为空
void SListPopFront(SListNode** pphead)
{
	assert(*pphead); //断言
	SListNode* temp = *pphead;
	*pphead = (*pphead)->next;
	free(temp);
	temp = NULL;
}

//尾插
//由于 pphead 是一个指向头指针的指针，这样设计允许函数内部直接修改头指针的值。这在链表为空时特别有用，因为需要将头指针指向新创建的第一个节点。如果只传递头指针的副本（即不通过双指针），函数内部的任何修改都不会反映到原始头指针上，从而无法更新链表的开始位置
void SListPushBack(SListNode** pphead, SLTDataType value)
{
	// 申请一个新结点，并初始化其数据为value
	SListNode* newnode = CreateNode(value); // 该函数需要预先定义，用于创建新节点并设置其数据

	// 判断传入的链表指针是否指向NULL，即检查链表是否为空
	if (*pphead == NULL) // 如果链表为空（即没有任何节点）
	{
		*pphead = newnode; // 将链表的头指针指向新节点，使新节点成为链表的第一个（也是唯一一个）节点
	}
	else // 如果链表不为空
	{
		SListNode* tail = *pphead; // 使用一个辅助指针tail开始于链表的头节点

		// 遍历链表找到最后一个节点，即其next指针为NULL的节点
		while (tail->next != NULL) // 继续遍历，直到找到一个next指针为NULL的节点
		{
			tail = tail->next; // 移动tail指针到下一个节点
		}

		// 在链表的末尾添加新节点
		tail->next = newnode; // 将找到的最后一个节点的next指针指向新创建的节点，从而将新节点链接到链表的末尾
	}
}
//尾删
void SListPopBack(SListNode** pphead) {
	if (*pphead == NULL) { // 检查链表是否为空
		return; // 链表为空，直接返回
	}
	if ((*pphead)->next == NULL) { // 如果链表只有一个节点
		free(*pphead); // 释放这个节点
		*pphead = NULL; // 将头指针设置为 NULL
		return;
	}
	SListNode* current = *pphead; // 用于遍历链表的临时指针
	while (current->next->next != NULL) { // 找到倒数第二个节点
		current = current->next;
	}
	free(current->next); // 释放最后一个节点
	current->next = NULL; // 将倒数第二个节点的 next 指针设置为 NULL
}

//单链表在pos位置前插入数据
void InsertNodeBeforePos(SListNode** pphead, int pos, SLTDataType value)
{
	if (pos < 0 || pphead == NULL) { // 检查位置是否有效
		return;
	}

	SListNode* newNode = CreateNode(value); // 创建新节点
	if (pos == 0) { // 如果位置是0，即在头部插入
		newNode->next = *pphead; // 新节点指向当前头节点
		*pphead = newNode; // 更新头节点为新节点
		return;
	}

	SListNode* current = *pphead;
	for (int i = 0; current != NULL && i < pos - 1; i++) { // 寻找位置 pos 的前一个节点
		current = current->next;
	}

	if (current == NULL) { // 如果位置超出链表长度
		free(newNode); // 释放新节点
		return;
	}

	// 插入新节点到链表中
	newNode->next = current->next; // 新节点指向当前节点的下一个节点
	current->next = newNode; // 当前节点的 next 更新为新节点
}


//单链表在pos位置前插入数据
void InsertNodeAfterPos(SListNode** pphead, int pos, SLTDataType value) {
	if (pos < 0 || pphead == NULL) { // 检查位置是否有效
		return;
	}

	SListNode* current = *pphead;
	for (int i = 0; current != NULL && i < pos; i++) { // 寻找位置 pos 的节点
		current = current->next;
	}

	if (current == NULL) { // 如果位置超出链表长度或链表为空
		return;
	}

	SListNode* newNode = CreateNode(value); // 创建新节点
	newNode->next = current->next; // 新节点指向当前节点的下一个节点
	current->next = newNode; // 当前节点的 next 更新为新节点
}


// 删除指定位置之后的所有节点
void DeleteNodesAfterPos(SListNode** pphead, int pos) {
	if (*pphead == NULL || pos < 0) { // 如果链表为空或位置无效
		return;
	}

	SListNode* current = *pphead; // 用于遍历链表的临时指针
	for (int i = 0; i < pos && current != NULL; i++) { // 遍历到指定位置
		current = current->next;
	}

	if (current == NULL || current->next == NULL) { // 如果位置超出链表范围或没有后续节点
		return;
	}

	SListNode* temp = current->next; // 保存要开始删除的第一个节点
	current->next = NULL; // 将指定位置的节点的 next 指针设置为 NULL，断开链接

	while (temp != NULL) { // 遍历并释放所有后继节点
		SListNode* toDelete = temp;
		temp = temp->next;
		free(toDelete);
	}
}

//链表删除pos位置的元素
void DeleteNodeAtPos(SListNode** pphead, int pos) {
	if (pos < 0 || *pphead == NULL) { // 检查位置是否有效或链表是否为空
		return;
	}
	SListNode* temp = *pphead; // 用于遍历的临时指针

	if (pos == 0) { // 如果要删除的是头节点
		*pphead = temp->next; // 更新头指针
		free(temp); // 释放头节点内存
		return;
	}

	for (int i = 0; i < pos - 1 && temp != NULL; i++) { // 寻找要删除节点的前一个节点
		temp = temp->next;
	}

	if (temp == NULL || temp->next == NULL) { // 如果位置无效或者pos超出了链表长度
		return; // 无操作
	}

	SListNode* toDelete = temp->next; // 指向要删除的节点
	temp->next = toDelete->next; // 将前一个节点的 next 指向要删除节点的下一个节点
	free(toDelete); // 释放要删除的节点的内存
}

//修改
void SListModify(SListNode* pos, SLTDataType x)
{
	pos->data = x;//将结点的数据改为目标数据
}