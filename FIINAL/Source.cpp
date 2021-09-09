#include"Priority_queue.h"
#include<iostream>
using namespace std;
int main() {
	Priority_queue<int> testpq;
	testpq.push(40);
	testpq.push(60);
	testpq.push(30);
	testpq.push(12);
	testpq.push(100);
	testpq.push(0);
	testpq.pop();
	while (!testpq.isEmpty()) {
		cout<<testpq.top()->getItem()<<endl;
		testpq.pop();
	}

}