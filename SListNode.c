#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <cstdlib>

typedef int SLTDataType; // ������������Ϊ���ͣ���SLTDataType����int
//����ߴ���Ŀɶ��ԺͿ�ά����

// ���嵥������Ľڵ�ṹ
typedef struct SListNode {
    SLTDataType data; // �����򣺴洢�ڵ�����ݣ�����Ϊ��������
    struct SListNode* next; // ָ����ָ����������һ���ڵ��ָ��
} SListNode;

//�����µĽڵ�
SListNode* CreateNode(SLTDataType value)
{
	SListNode* newNode = (SListNode*)malloc(sizeof(SListNode)); // ��̬�����ڴ�
	if (newNode == NULL) // ����ڴ��Ƿ�ɹ�����
	{
		perror("malloc fail");
		exit(-1);
	}
	newNode->data = value; // ���ýڵ��������
	newNode->next = NULL;  // ��ʼ��ָ����Ŀǰ�˽ڵ㲻ָ�������ڵ�
	return newNode;        // �����´����Ľڵ�
}

// �������� num ���ڵ�ĵ�����
SListNode* CreateSlist(int num)
{
	SListNode* phead = NULL; // ͷָ�룬��ʼΪ��
	SListNode* ptail = NULL; // βָ�룬����׷������ĩβ

	for (int i = 0; i < num; i++) {
		SListNode* newnode = CreateNode(i); // ����һ���½ڵ�
		if (phead == NULL) {
			ptail = phead = newnode; // �������Ϊ�գ���ʼ��ͷβָ��Ϊ��һ���ڵ�
		}
		else {
			ptail->next = newnode; // ���½ڵ����ӵ�����ĩβ
			ptail = newnode;       // ����βָ��ָ���µ�ĩβ�ڵ�
		}
	}
	return phead; // ��������ͷָ��
}

//��ӡ
void PrintList(SListNode* head)
{
	if (head == NULL) { // ���ͷָ��Ϊ NULL����ʾ����Ϊ��
		printf("The list is empty.\n");
	}
	else {
		printf("List: ");
		SListNode* current = head; // ʹ��һ����ʱָ���ͷ�ڵ㿪ʼ��������
				//���� head ָ�벻�䣬ʹ����һ����ʱָ�루current�����б�����
				//���Ա�֤ head ָ��ʼ��ָ������Ŀ�ʼλ��
		while (current != NULL) { // ��������ֱ��ĩβ
			printf("%d -> ", current->data); // ��ӡ��ǰ�ڵ������
			current = current->next; // �ƶ�����һ���ڵ�
		}
		printf("NULL\n"); // ��ӡ���������־
	}
}

//�ݻ�
void DestroyList(SListNode** pphead)
{
	while (*pphead != NULL) {
		SListNode* temp = *pphead;       // ���浱ǰͷ�ڵ�
		*pphead = (*pphead)->next;       // ����ͷָ�뵽��һ���ڵ�
		free(temp);                      // �ͷ�ԭͷ�ڵ���ڴ�
	}
	// ��ѡ��ȷ��������ȫ��պ��ⲿָ��Ҳ����ΪNULL
	*pphead = NULL;
}


//ͷ��
void SListPushFront(SListNode** pphead, SLTDataType value)
{
	SListNode* newNode = CreateNode(value); // ����һ���½ڵ�
	newNode->next = *pphead; // �½ڵ�� next ָ��ָ��ǰ��ͷ�ڵ�
	*pphead = newNode;       // ����ͷָ�룬������ָ���µ�ͷ�ڵ�
}

// ͷɾ         ע�⣺���붼����Ҫ���ԣ�ɾ����Ҫ���ԣ���ֹҪɾ���õ�һ��Ϊ��
void SListPopFront(SListNode** pphead)
{
	assert(*pphead); //����
	SListNode* temp = *pphead;
	*pphead = (*pphead)->next;
	free(temp);
	temp = NULL;
}

//β��
//���� pphead ��һ��ָ��ͷָ���ָ�룬��������������ڲ�ֱ���޸�ͷָ���ֵ����������Ϊ��ʱ�ر����ã���Ϊ��Ҫ��ͷָ��ָ���´����ĵ�һ���ڵ㡣���ֻ����ͷָ��ĸ���������ͨ��˫ָ�룩�������ڲ����κ��޸Ķ����ᷴӳ��ԭʼͷָ���ϣ��Ӷ��޷���������Ŀ�ʼλ��
void SListPushBack(SListNode** pphead, SLTDataType value)
{
	// ����һ���½�㣬����ʼ��������Ϊvalue
	SListNode* newnode = CreateNode(value); // �ú�����ҪԤ�ȶ��壬���ڴ����½ڵ㲢����������

	// �жϴ��������ָ���Ƿ�ָ��NULL������������Ƿ�Ϊ��
	if (*pphead == NULL) // �������Ϊ�գ���û���κνڵ㣩
	{
		*pphead = newnode; // �������ͷָ��ָ���½ڵ㣬ʹ�½ڵ��Ϊ����ĵ�һ����Ҳ��Ψһһ�����ڵ�
	}
	else // �������Ϊ��
	{
		SListNode* tail = *pphead; // ʹ��һ������ָ��tail��ʼ�������ͷ�ڵ�

		// ���������ҵ����һ���ڵ㣬����nextָ��ΪNULL�Ľڵ�
		while (tail->next != NULL) // ����������ֱ���ҵ�һ��nextָ��ΪNULL�Ľڵ�
		{
			tail = tail->next; // �ƶ�tailָ�뵽��һ���ڵ�
		}

		// �������ĩβ����½ڵ�
		tail->next = newnode; // ���ҵ������һ���ڵ��nextָ��ָ���´����Ľڵ㣬�Ӷ����½ڵ����ӵ������ĩβ
	}
}
//βɾ
void SListPopBack(SListNode** pphead) {
	if (*pphead == NULL) { // ��������Ƿ�Ϊ��
		return; // ����Ϊ�գ�ֱ�ӷ���
	}
	if ((*pphead)->next == NULL) { // �������ֻ��һ���ڵ�
		free(*pphead); // �ͷ�����ڵ�
		*pphead = NULL; // ��ͷָ������Ϊ NULL
		return;
	}
	SListNode* current = *pphead; // ���ڱ����������ʱָ��
	while (current->next->next != NULL) { // �ҵ������ڶ����ڵ�
		current = current->next;
	}
	free(current->next); // �ͷ����һ���ڵ�
	current->next = NULL; // �������ڶ����ڵ�� next ָ������Ϊ NULL
}

//��������posλ��ǰ��������
void InsertNodeBeforePos(SListNode** pphead, int pos, SLTDataType value)
{
	if (pos < 0 || pphead == NULL) { // ���λ���Ƿ���Ч
		return;
	}

	SListNode* newNode = CreateNode(value); // �����½ڵ�
	if (pos == 0) { // ���λ����0������ͷ������
		newNode->next = *pphead; // �½ڵ�ָ��ǰͷ�ڵ�
		*pphead = newNode; // ����ͷ�ڵ�Ϊ�½ڵ�
		return;
	}

	SListNode* current = *pphead;
	for (int i = 0; current != NULL && i < pos - 1; i++) { // Ѱ��λ�� pos ��ǰһ���ڵ�
		current = current->next;
	}

	if (current == NULL) { // ���λ�ó���������
		free(newNode); // �ͷ��½ڵ�
		return;
	}

	// �����½ڵ㵽������
	newNode->next = current->next; // �½ڵ�ָ��ǰ�ڵ����һ���ڵ�
	current->next = newNode; // ��ǰ�ڵ�� next ����Ϊ�½ڵ�
}


//��������posλ��ǰ��������
void InsertNodeAfterPos(SListNode** pphead, int pos, SLTDataType value) {
	if (pos < 0 || pphead == NULL) { // ���λ���Ƿ���Ч
		return;
	}

	SListNode* current = *pphead;
	for (int i = 0; current != NULL && i < pos; i++) { // Ѱ��λ�� pos �Ľڵ�
		current = current->next;
	}

	if (current == NULL) { // ���λ�ó��������Ȼ�����Ϊ��
		return;
	}

	SListNode* newNode = CreateNode(value); // �����½ڵ�
	newNode->next = current->next; // �½ڵ�ָ��ǰ�ڵ����һ���ڵ�
	current->next = newNode; // ��ǰ�ڵ�� next ����Ϊ�½ڵ�
}


// ɾ��ָ��λ��֮������нڵ�
void DeleteNodesAfterPos(SListNode** pphead, int pos) {
	if (*pphead == NULL || pos < 0) { // �������Ϊ�ջ�λ����Ч
		return;
	}

	SListNode* current = *pphead; // ���ڱ����������ʱָ��
	for (int i = 0; i < pos && current != NULL; i++) { // ������ָ��λ��
		current = current->next;
	}

	if (current == NULL || current->next == NULL) { // ���λ�ó�������Χ��û�к����ڵ�
		return;
	}

	SListNode* temp = current->next; // ����Ҫ��ʼɾ���ĵ�һ���ڵ�
	current->next = NULL; // ��ָ��λ�õĽڵ�� next ָ������Ϊ NULL���Ͽ�����

	while (temp != NULL) { // �������ͷ����к�̽ڵ�
		SListNode* toDelete = temp;
		temp = temp->next;
		free(toDelete);
	}
}

//����ɾ��posλ�õ�Ԫ��
void DeleteNodeAtPos(SListNode** pphead, int pos) {
	if (pos < 0 || *pphead == NULL) { // ���λ���Ƿ���Ч�������Ƿ�Ϊ��
		return;
	}
	SListNode* temp = *pphead; // ���ڱ�������ʱָ��

	if (pos == 0) { // ���Ҫɾ������ͷ�ڵ�
		*pphead = temp->next; // ����ͷָ��
		free(temp); // �ͷ�ͷ�ڵ��ڴ�
		return;
	}

	for (int i = 0; i < pos - 1 && temp != NULL; i++) { // Ѱ��Ҫɾ���ڵ��ǰһ���ڵ�
		temp = temp->next;
	}

	if (temp == NULL || temp->next == NULL) { // ���λ����Ч����pos������������
		return; // �޲���
	}

	SListNode* toDelete = temp->next; // ָ��Ҫɾ���Ľڵ�
	temp->next = toDelete->next; // ��ǰһ���ڵ�� next ָ��Ҫɾ���ڵ����һ���ڵ�
	free(toDelete); // �ͷ�Ҫɾ���Ľڵ���ڴ�
}

//�޸�
void SListModify(SListNode* pos, SLTDataType x)
{
	pos->data = x;//���������ݸ�ΪĿ������
}