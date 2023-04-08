#include "common.h"

typedef struct _tagNode // 데이터와 다음 주소를 가지는 Node 구조체.
{
	int			iData; // 추가하는 데이터가 int라고 가정.
	struct      _tagNode* pNextNode; // 아직 tNode 정의하지 않았으므로 struct type으로 멤버 변수 선언.
}tNode;

typedef struct _tagList // 데이터 추가 횟수와 첫번째 노드의 주소를 가지는 List 구조체.
{
	// 필요할 때마다 동적할당 하므로, 가변배열과 달리 MaxCnt 필요없음. 
	int		iCount;
	tNode* pHeadNode;

}tLinkedList;

void InitList(_tagList* _pList) // Linked List 초기화
{
	_pList->pHeadNode = nullptr; // 데이터가 들어올 때만 노드를 만들것이기 때문에 nullptr.
	_pList->iCount = 0; // 마찬가지.
}

void PushBack(_tagList* _pList, int _iData) // 데이터를 뒤에 추가하는 함수.
{
	// 데이터를 추가할 때마다 살아있어야 하니까 동적할당으로 Heap 메모리 공간에 노드 생성.

	tNode* pNode = (tNode*)malloc(sizeof(tNode)); 

	pNode->iData = _iData; // 일단 생성시킨 노드에 데이터를 추가하고, 다음 노드의 주소를 선언.
	pNode->pNextNode = nullptr ; // Push"Back"이니까 다음 노드의 데이터는 nullptr임.
	
	// 추가한 데이터가 처음인지 아닌지 확인해야함.
	if (0 == _pList->iCount) // 들어온 횟수로 판단하거나 _pList->pHeadNode == 0으로 확인.
	{						 // 한 번도 안들어왔다면 횟수가 0이거나, HeadNode가 연결되어있지 않음.
		_pList->pHeadNode = pNode; // 처음 추가되는 노드라면 그냥 HeadNode에 연결해주면 됌.
	}
	else // 이미 리스트에 노드가 1개 이상인 경우.
	{
		// _pList->pHeadNode의 NextNode가 nullptr인 경우를 찾아야하는데
		// _pList->pHeadNode는 이미 Head를 갖고있잖아. 그러니까 이것 자체를 변경시키면 Head를 잃는 거니까
		// 지역변수로 _pList->pHeadNode를 받는거지.

		tNode* pTempNode = _pList->pHeadNode;

		while (pTempNode->pNextNode) // HeadNode부터 멤버 NextNode가 nullptr가 나올 때까지 반복.
		{	
			pTempNode = pTempNode->pNextNode; // NextNode에 주소값이 있다면 임시HeadNode를 그 NextNode로 변경.
		}
		pTempNode->pNextNode = pNode; // 이제 원하던 nullptr가 나오면(현재 기준 마지막 노드가 나오면) 추가할 노드를 NextNode와 연결.
	}

	++_pList->iCount; // 추가횟수 증가.
}

//void Release(tNode* _pNode) // 재귀함수로 해제할 시 연속적으로 노드를 해제하는 함수.
//{	
//	if (nullptr == _pNode) // 탈출 조건.
//		return;
//
//	Release(_pNode->pNextNode); // 바로 _pNode를 해제하면 안되니까 free전에 재귀함수로 NextNode를 Release함수 인자로 실행.
//	free(_pNode); // 마지막 노드에 가서 if문에 걸려서 return반환하면 그때부터 거꾸로 free하는 방식.
//}

void ReleaseList(tLinkedList* _pList) // Linked List 메모리 해제 : 순서대로 해제해야함(재귀함수 or 반복문)
{	
	/*Release(_pList->pHeadNode);*/ // 재귀함수로 해제할 시 일단 아는 건 HeadNode밖에 모르니 이렇게 호출하고 위에 Release함수 실행되지.

	tNode* pDeleteNode = _pList->pHeadNode; //  Head를 잃지 않기 위해 지역변수 DeleteNode로 _pList->pHeadNode를 받는거지.
											// 그 다음에 이제 DeleteNode를 가지고 노는거지.
	
	while (pDeleteNode)
	{	
		tNode* pNext = pDeleteNode->pNextNode; // 바로 삭제하면 그 다음을 모르니까
											   // DeleteNode를 free하기 전에 DeleteNode, 즉 HeadNode의 NextNode를 미리 받아놓고.
		free(pDeleteNode);					   // 받은 뒤에 DeleteNode를 free.
		pDeleteNode = pNext;				   // 그리고 받은 NextNode 다시 DeleteNode로 바꿈. 왜냐하면 조건문에 NextNode의 값이
											   // 존재할 때까지 free시킬거니까.
	}

}