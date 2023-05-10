#include "common.h"


struct client_info_list* input_client(int num)
{
	int no;
	client_info_list* head = nullptr;
	client_info_list* current, * previous = nullptr;
	head = (client_info_list*)malloc(sizeof(client_info_list)); // head = ù��° ����ü ������
	current = head; // ��� ������ ����, ���� ����ü �����͸� �̵���Ű�鼭 ���� ����ü ����
	current->next = nullptr; // ������ ����ü�� ���� �����ʹ� �׻� NULL : ���� ����Ʈ�� ������ ǥ��
	for (int i = 0; i < num; i++)
	{
		printf("����ȣ :");
		scanf_s("%d%*c", &current->no);
		printf("���̸� :");
		scanf_s("%s", current->name, MAX_LEN);
		printf("���űݾ� :");
		scanf_s("%lf", &current->pamount);
		current->birth = (date*)malloc(sizeof(date));
		printf("�������(YYYY MM DD) :");
		scanf_s("%d %d %d", &current->birth->year, &current->birth->month, &current->birth->day);
		current->next = (client_info_list*)malloc(sizeof(client_info_list));
		previous = current;
		current = current->next;
	}
	free(current); // �������� �߰������� �Ҵ�� ����ü �޸� ����
	previous->next = nullptr; // ������ ����ü�� ���� �����ʹ� �׻� NULL : ���� ����Ʈ�� ������ǥ��
	return(head); // �� ���� ����ü ������ ���� �ּ�(��� ������) ��ȯ
}
void output_client(struct client_info_list* head)
{
	struct client_info_list* current;
	current = head;
	while (current != nullptr)
	{
		printf("����ȣ : %d\n", current->no);
		printf("���̸� : %s\n", current->name);
		printf("���űݾ� : %lf\n", current->pamount);
		printf("�������(YYYY MM DD): %d %d %d\n\n", current->birth->year, current->birth-> month, current->birth->day);
		current = current->next;
	}
}

void add_client(struct client_info_list** headp)
{
	struct client_info_list* current = NULL;
	if (*headp == NULL) //ù��° �� ���� �Է� --> ���� ����Ʈ ��� ����(NULL --> 1��° ����ü)
 {
 *headp = (struct client_info_list*)malloc(sizeof(struct client_info_list));
 // ���� ������ headp�� ����Ű�� ����(���� ����Ʈ�� ���) ����
 printf("����ȣ :");
 scanf_s("%d%*c", &(*headp)->no);
 printf("���̸� :");
 scanf_s("%s", (*headp)->name, MAX_LEN);
 printf("���űݾ� :");
 scanf_s("%lf", &(*headp)->pamount);
 (*headp)->birth = (struct date*)malloc(sizeof(struct date));
 printf("�������(YYYY MM DD) :");
 scanf_s("%d %d %d", &(*headp)->birth->year, &(*headp)->birth->month, &(*headp)->birth -> day);
 (*headp)->next = NULL; // ������ ����ü�� ���� �����ʹ� �׻� NULL : ����  ����Ʈ�� ������ ǥ��
 }
	else // ��� ���� ����
	{
		current = *headp;
		while (current->next != NULL) // while (current != NULL) ���� ���� : NULL->next ����
			current = current->next;
		current->next = (struct client_info_list*)malloc(sizeof(struct client_info_list));
		current = current->next;
		printf("����ȣ :");
		scanf_s("%d%*c", &current->no);
		printf("���̸� :");
		scanf_s("%s", current->name, MAX_LEN);
		printf("���űݾ� :");
		scanf_s("%lf", &current->pamount);
		current->birth = (struct date*)malloc(sizeof(struct date));
		printf("�������(YYYY MM DD) :");
		scanf_s("%d %d %d", &current->birth->year, &current->birth->month, &current->birth->day);
		current->next = NULL; // ������ ����ü�� ���� �����ʹ� �׻� NULL : ���� ����Ʈ�� ������ ǥ��
	}
}
void delete_client(struct client_info_list** headp, char* name)
{
	
	struct client_info_list* cur, * item = nullptr;
	cur = *headp;

	// ������ ��� ã�� ����.
	while (cur->next != nullptr)
	{
		if (strcmp(cur->name, name) != 0) // ������ ��带 �� ã�� ���.
		{
			item = cur; // ����� �ӽ����� ��� ����.
			cur = cur->next;
		}
		else if (strcmp(cur->name, name) == 0) // ���� ��쿡, ù��° ���� �߰� ��� ���� ����.
		{
			if (cur == *headp)
			{
				*headp = cur->next; // ù�� ° ��� �����ϰ� Heap ���� �޸� ����.
				free(cur);
				break;
			}
			else if (cur->next != nullptr) // �߰� ��� ���� �� next�� ����Ʈ ����, �� ���� Heap ���� �޸� ����.
			{
				item = cur->next;
				(*headp)->next = cur->next;
				free(cur);
				break;
			}
		}
		
	}
	if (cur->next == nullptr) // ������ ��� ���� �� ������ �� ����� next�� nullptr�� �������.
	{
		item->next = nullptr;
		free(cur);
	}
	
}