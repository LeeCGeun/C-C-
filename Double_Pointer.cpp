#include "common.h"


struct client_info_list* input_client(int num)
{
	int no;
	client_info_list* head = nullptr;
	client_info_list* current, * previous = nullptr;
	head = (client_info_list*)malloc(sizeof(client_info_list)); // head = 첫번째 구조체 포인터
	current = head; // 헤드 포인터 유지, 현재 구조체 포인터를 이동시키면서 다음 구조체 연결
	current->next = nullptr; // 마지막 구조체의 다음 포인터는 항상 NULL : 연결 리스트의 마지막 표시
	for (int i = 0; i < num; i++)
	{
		printf("고객번호 :");
		scanf_s("%d%*c", &current->no);
		printf("고객이름 :");
		scanf_s("%s", current->name, MAX_LEN);
		printf("구매금액 :");
		scanf_s("%lf", &current->pamount);
		current->birth = (date*)malloc(sizeof(date));
		printf("생년월일(YYYY MM DD) :");
		scanf_s("%d %d %d", &current->birth->year, &current->birth->month, &current->birth->day);
		current->next = (client_info_list*)malloc(sizeof(client_info_list));
		previous = current;
		current = current->next;
	}
	free(current); // 마지막에 추가적으로 할당된 구조체 메모리 해제
	previous->next = nullptr; // 마지막 구조체의 다음 포인터는 항상 NULL : 연결 리스트의 마지막표시
	return(head); // 고객 정보 구조체 리스의 시작 주소(헤드 포인터) 반환
}
void output_client(struct client_info_list* head)
{
	struct client_info_list* current;
	current = head;
	while (current != nullptr)
	{
		printf("고객번호 : %d\n", current->no);
		printf("고객이름 : %s\n", current->name);
		printf("구매금액 : %lf\n", current->pamount);
		printf("생년월일(YYYY MM DD): %d %d %d\n\n", current->birth->year, current->birth-> month, current->birth->day);
		current = current->next;
	}
}

void add_client(struct client_info_list** headp)
{
	struct client_info_list* current = NULL;
	if (*headp == NULL) //첫번째 고객 정보 입력 --> 연결 리스트 헤드 변경(NULL --> 1번째 구조체)
 {
 *headp = (struct client_info_list*)malloc(sizeof(struct client_info_list));
 // 이중 포인터 headp가 가르키는 내용(연결 리스트의 헤드) 변경
 printf("고객번호 :");
 scanf_s("%d%*c", &(*headp)->no);
 printf("고객이름 :");
 scanf_s("%s", (*headp)->name, MAX_LEN);
 printf("구매금액 :");
 scanf_s("%lf", &(*headp)->pamount);
 (*headp)->birth = (struct date*)malloc(sizeof(struct date));
 printf("생년월일(YYYY MM DD) :");
 scanf_s("%d %d %d", &(*headp)->birth->year, &(*headp)->birth->month, &(*headp)->birth -> day);
 (*headp)->next = NULL; // 마지막 구조체의 다음 포인터는 항상 NULL : 연결  리스트의 마지막 표시
 }
	else // 헤드 변경 없음
	{
		current = *headp;
		while (current->next != NULL) // while (current != NULL) 형식 주의 : NULL->next 오류
			current = current->next;
		current->next = (struct client_info_list*)malloc(sizeof(struct client_info_list));
		current = current->next;
		printf("고객번호 :");
		scanf_s("%d%*c", &current->no);
		printf("고객이름 :");
		scanf_s("%s", current->name, MAX_LEN);
		printf("구매금액 :");
		scanf_s("%lf", &current->pamount);
		current->birth = (struct date*)malloc(sizeof(struct date));
		printf("생년월일(YYYY MM DD) :");
		scanf_s("%d %d %d", &current->birth->year, &current->birth->month, &current->birth->day);
		current->next = NULL; // 마지막 구조체의 다음 포인터는 항상 NULL : 연결 리스트의 마지막 표시
	}
}
void delete_client(struct client_info_list** headp, char* name)
{
	
	struct client_info_list* cur, * item = nullptr;
	cur = *headp;

	// 삭제할 노드 찾는 과정.
	while (cur->next != nullptr)
	{
		if (strcmp(cur->name, name) != 0) // 삭제할 노드를 못 찾을 경우.
		{
			item = cur; // 현재와 임시저장 노드 설정.
			cur = cur->next;
		}
		else if (strcmp(cur->name, name) == 0) // 같을 경우에, 첫번째 노드와 중간 노드 삭제 과정.
		{
			if (cur == *headp)
			{
				*headp = cur->next; // 첫번 째 노드 삭제하고 Heap 영역 메모리 해제.
				free(cur);
				break;
			}
			else if (cur->next != nullptr) // 중간 노드 삭제 후 next로 리스트 연결, 그 다음 Heap 영역 메모리 해제.
			{
				item = cur->next;
				(*headp)->next = cur->next;
				free(cur);
				break;
			}
		}
		
	}
	if (cur->next == nullptr) // 마지막 노드 삭제 후 마지막 전 노드의 next를 nullptr로 만들어줌.
	{
		item->next = nullptr;
		free(cur);
	}
	
}