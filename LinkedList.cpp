#include "common.h"

typedef struct _tagNode // �����Ϳ� ���� �ּҸ� ������ Node ����ü.
{
	int			iData; // �߰��ϴ� �����Ͱ� int��� ����.
	struct      _tagNode* pNextNode; // ���� tNode �������� �ʾ����Ƿ� struct type���� ��� ���� ����.
}tNode;

typedef struct _tagList // ������ �߰� Ƚ���� ù��° ����� �ּҸ� ������ List ����ü.
{
	// �ʿ��� ������ �����Ҵ� �ϹǷ�, �����迭�� �޸� MaxCnt �ʿ����. 
	int		iCount;
	tNode* pHeadNode;

}tLinkedList;

void InitList(_tagList* _pList) // Linked List �ʱ�ȭ
{
	_pList->pHeadNode = nullptr; // �����Ͱ� ���� ���� ��带 ������̱� ������ nullptr.
	_pList->iCount = 0; // ��������.
}

void PushBack(_tagList* _pList, int _iData) // �����͸� �ڿ� �߰��ϴ� �Լ�.
{
	// �����͸� �߰��� ������ ����־�� �ϴϱ� �����Ҵ����� Heap �޸� ������ ��� ����.

	tNode* pNode = (tNode*)malloc(sizeof(tNode)); 

	pNode->iData = _iData; // �ϴ� ������Ų ��忡 �����͸� �߰��ϰ�, ���� ����� �ּҸ� ����.
	pNode->pNextNode = nullptr ; // Push"Back"�̴ϱ� ���� ����� �����ʹ� nullptr��.
	
	// �߰��� �����Ͱ� ó������ �ƴ��� Ȯ���ؾ���.
	if (0 == _pList->iCount) // ���� Ƚ���� �Ǵ��ϰų� _pList->pHeadNode == 0���� Ȯ��.
	{						 // �� ���� �ȵ��Դٸ� Ƚ���� 0�̰ų�, HeadNode�� ����Ǿ����� ����.
		_pList->pHeadNode = pNode; // ó�� �߰��Ǵ� ����� �׳� HeadNode�� �������ָ� ��.
	}
	else // �̹� ����Ʈ�� ��尡 1�� �̻��� ���.
	{
		// _pList->pHeadNode�� NextNode�� nullptr�� ��츦 ã�ƾ��ϴµ�
		// _pList->pHeadNode�� �̹� Head�� �������ݾ�. �׷��ϱ� �̰� ��ü�� �����Ű�� Head�� �Ҵ� �Ŵϱ�
		// ���������� _pList->pHeadNode�� �޴°���.

		tNode* pTempNode = _pList->pHeadNode;

		while (pTempNode->pNextNode) // HeadNode���� ��� NextNode�� nullptr�� ���� ������ �ݺ�.
		{	
			pTempNode = pTempNode->pNextNode; // NextNode�� �ּҰ��� �ִٸ� �ӽ�HeadNode�� �� NextNode�� ����.
		}
		pTempNode->pNextNode = pNode; // ���� ���ϴ� nullptr�� ������(���� ���� ������ ��尡 ������) �߰��� ��带 NextNode�� ����.
	}

	++_pList->iCount; // �߰�Ƚ�� ����.
}

//void Release(tNode* _pNode) // ����Լ��� ������ �� ���������� ��带 �����ϴ� �Լ�.
//{	
//	if (nullptr == _pNode) // Ż�� ����.
//		return;
//
//	Release(_pNode->pNextNode); // �ٷ� _pNode�� �����ϸ� �ȵǴϱ� free���� ����Լ��� NextNode�� Release�Լ� ���ڷ� ����.
//	free(_pNode); // ������ ��忡 ���� if���� �ɷ��� return��ȯ�ϸ� �׶����� �Ųٷ� free�ϴ� ���.
//}

void ReleaseList(tLinkedList* _pList) // Linked List �޸� ���� : ������� �����ؾ���(����Լ� or �ݺ���)
{	
	/*Release(_pList->pHeadNode);*/ // ����Լ��� ������ �� �ϴ� �ƴ� �� HeadNode�ۿ� �𸣴� �̷��� ȣ���ϰ� ���� Release�Լ� �������.

	tNode* pDeleteNode = _pList->pHeadNode; //  Head�� ���� �ʱ� ���� �������� DeleteNode�� _pList->pHeadNode�� �޴°���.
											// �� ������ ���� DeleteNode�� ������ ��°���.
	
	while (pDeleteNode)
	{	
		tNode* pNext = pDeleteNode->pNextNode; // �ٷ� �����ϸ� �� ������ �𸣴ϱ�
											   // DeleteNode�� free�ϱ� ���� DeleteNode, �� HeadNode�� NextNode�� �̸� �޾Ƴ���.
		free(pDeleteNode);					   // ���� �ڿ� DeleteNode�� free.
		pDeleteNode = pNext;				   // �׸��� ���� NextNode �ٽ� DeleteNode�� �ٲ�. �ֳ��ϸ� ���ǹ��� NextNode�� ����
											   // ������ ������ free��ų�Ŵϱ�.
	}

}