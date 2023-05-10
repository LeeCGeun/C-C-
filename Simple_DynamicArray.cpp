#include <iostream>
#include <assert.h>
using namespace std;

class CArr
{
private:

	int* m_pInt; // ���� �迭 ���� �ּ�
	int m_iCount; // �Էµ� int data ����
	int m_iMaxCount; // �ִ� data ����

public:
	
	void push_back(int _Data) // data pushback
	{
		if (m_iMaxCount <= m_iCount) // this ����� �ʿ����.
		{							 // �̹� �� ��ü�� ����Ǳ� ������.
			resize(m_iMaxCount * 2); // �ִ� data �������� 2�� ū �޸� ���Ҵ�
		}
		m_pInt[m_iCount++] = _Data;
	}

	void resize(int _iResizeCount) // heap memory allocate, ó������ ������ ������ ���� ��쿡�� �ϴ� resize�ϰ� �����ϴ� ��� �����Ƿ� public level
	{
		if (m_iMaxCount >= _iResizeCount) // ���� ���뷮���� �� ���� ������ Ȯ���Ϸ��� ���
		{
			assert(nullptr); // ����
		}
		int* pNew = new int[_iResizeCount]; // ���� ���� �ּ� ���� �ʱ� ���� ���������� ���ϴ� ũ�� �Ҵ�

		for (int i = 0; i < m_iCount; i++)
		{
			pNew[i] = m_pInt[i]; // �Ҵ��� �޸𸮿� ���� data ����
		}

		delete[] m_pInt; // ���� �� �޸� ����
		m_pInt = pNew; // ���� �ּ� ����
		m_iMaxCount = _iResizeCount; // �ִ� data ������ �����Ǿ����
	}
	CArr()
		: m_pInt(nullptr)
		, m_iCount(0)
		, m_iMaxCount(2) // �ִ� data 0�̸� ���۾��ϹǷ� ������ �� 
	{
		m_pInt = new int[2];
	}
	~CArr()
	{
		delete [] m_pInt;
	}
};

int main()
{
	CArr carr;

	carr.push_back(10);
	carr.push_back(20);
	carr.push_back(30);
	
	
	return 0;
}