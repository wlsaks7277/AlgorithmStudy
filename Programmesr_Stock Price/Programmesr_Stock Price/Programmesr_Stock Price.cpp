// Programmesr_Stock Price.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
//#include <queue>
#include <stack>

using namespace std;

int * solution(int prices[], size_t prices_len);

int main()
{
	int prices[] = { 2,3,1,4 };

	
	int * temp = solution(prices, sizeof(prices) / sizeof(int));

	for (int i = 0; i < sizeof(prices) / sizeof(int); i++) {
		std::cout << temp[i];
	}

	system("pause");
	return 0;
}

int * solution(int prices[], size_t prices_len) {
	//시간초과 코드
	/*int * answer = (int*)malloc(sizeof(int)* prices_len);
	for (int i = 0; i < prices_len; i++) {
		answer[i] = 0;
		for (int j = i + 1; j < prices_len; j++) {
			if (prices[i] <= prices[j]) answer[i]++;	
		}
	}*/

	int * answer = (int*)malloc(sizeof(int)* prices_len);

	stack <int> s;

	for (int i = 0; i < prices_len; i++) {
		while (!s.empty() && prices[s.top()] > prices[i]) {
			auto top = s.top();
			s.pop();
			answer[top] = i - top;
			
		}
		s.push(i);
	}

	while (!s.empty()) {
		auto top = s.top();
		answer[top] = prices_len -1 - top;
		s.pop();
	}

	return answer;

}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
