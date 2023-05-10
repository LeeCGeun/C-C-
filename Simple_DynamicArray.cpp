#include <iostream>
#include <assert.h>
using namespace std;

class CArr
{
private:

	int* m_pInt; // 가변 배열 시작 주소
	int m_iCount; // 입력된 int data 개수
	int m_iMaxCount; // 최대 data 개수

public:
	
	void push_back(int _Data) // data pushback
	{
		if (m_iMaxCount <= m_iCount) // this 사용할 필요없음.
		{							 // 이미 그 객체에 적용되기 때문에.
			resize(m_iMaxCount * 2); // 최대 data 개수보다 2배 큰 메모리 재할당
		}
		m_pInt[m_iCount++] = _Data;
	}

	void resize(int _iResizeCount) // heap memory allocate, 처음부터 데이터 개수가 많은 경우에는 일단 resize하고 시작하는 경우 있으므로 public level
	{
		if (m_iMaxCount >= _iResizeCount) // 현재 수용량보다 더 적은 양으로 확장하려는 경우
		{
			assert(nullptr); // 오류
		}
		int* pNew = new int[_iResizeCount]; // 원래 시작 주소 잃지 않기 위해 지역변수로 원하는 크기 할당

		for (int i = 0; i < m_iCount; i++)
		{
			pNew[i] = m_pInt[i]; // 할당한 메모리에 원래 data 복사
		}

		delete[] m_pInt; // 복사 후 메모리 해제
		m_pInt = pNew; // 시작 주소 변경
		m_iMaxCount = _iResizeCount; // 최대 data 개수도 수정되어야함
	}
	CArr()
		: m_pInt(nullptr)
		, m_iCount(0)
		, m_iMaxCount(2) // 최대 data 0이면 동작안하므로 적당한 값 
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