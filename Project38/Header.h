#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#pragma
#ifndef Uzel_H
#define Uzel_H
using namespace std;
class Uzel
{
private:
	
public:
	int a;
	char c;
	Uzel* left, * right;
	Uzel() {
		left = right = NULL;
	}
	Uzel(Uzel* L, Uzel* R)
	{
		left = L;
		right = R;
		a = L->a + R->a;
	}
#endif
};
void Print(Uzel* root, unsigned k);
void main1();
