#include "stdafx.h"

int main(int argc, char* argv[])
{
	CSystem* pSystem = new CSystem; //메모리 할당 //객체 생성

	pSystem->Initialize(); //초기화

	pSystem->Run(); //실행

	pSystem->Terminate(); //종료

	delete pSystem; //객체 삭제 //메모리 정리

	return 0;
}


