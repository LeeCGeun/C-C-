#include "common.h"
using namespace std;

class CMy // 접근 제한 지정자 : 클래스 내의 멤버변수 or 멤버함수의 접근 레벨(private, public, protected)
{		  // 대입 연산자는 컴파일러가 기본으로 처리, 그 외 연산자들은 사용자가 직접 정의해야함.
private: // private :
	int secret_int;
	float secret_float;

public: // 생성자, 소멸자는 사용자가 정의하지 않아도 컴파일러가 자동으로 존재인식, 대신 아무것도 안함.
	CMy() // 생성자 : 객체 생성 시 자동 호출(초기화 : 이니셜라이져).
		// 이니셜라이져
		: secret_int(100)
		, secret_float(0.3f) {}
		/*secret_int = 100;*/ // 이건 2단계(객채 생성 -> 객체에 초기값 입력)에 걸친 초기화
	
	/*~CMy();*/ // 소멸자(main스택 안에 CMy 클래스인 객체 Cmy는 main 함수 종료될 때 사라지므로, main 함수 종료시, 즉 return 0일 때 소멸자 자동 호출)

	// 멤버함수는 호출한 객체에만 적용
	
	void SetInt(int i) // 멤버함수 = 해당 클래스가 사용하는 전용 멤버 함수
					   // 객체가 존재해야지만 사용 가능. 그냥 CMy::SetInt(10); 이렇게 불가능(::는 그 안으로 들어가보겠다는 Scope 연산자)
	{
		secret_int = i; // secret_int가 private level이어도, public 멤버 함수인 SetInt함수를 통해 값 변경 가능.

		// 보이는 건 SetInt(int i)이지만, Setint(CMy* this, int i){this->secret_int = i;}원래 이런 식. 편의상 생략한 것)
	}   // this : 멤버함수를 호출한 해당 객체의 주소

	CMy& operator =(const CMy& _Other) // ( = ) 연산자 내부, operator ( = )을 호출한 객체 기준.
	{
		secret_int = _Other.secret_int;
		secret_float = _Other.secret_float;

		return *this;
	}
};

int main()
{	

	CMy c1;
	c1.SetInt(10);
	
	CMy c2;
	c2.SetInt(100);

	c1 = c2; // 대입 연산자는 기본으로 지원함.

	// c1 = c2 = c3가 성립되려면 우측부터 c2 = c3을 하고 return값이 있어야함 따라서 void가 아니라
	// 동일 객체 Cmy자료형이 오도록 대입 연산자 설정. 만약 void라면 c1 = ;이런 식으로 동작.
	// 그리고 return 값인 (*this)을 참조해주는거지. 정리하면 (=)연산자는 호출 객체인 *this를 참조, 별명을 붙여서 return한다는 뜻.


  	return 0;
}