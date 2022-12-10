#include "Header.h"
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
using namespace std;

struct MyCompare
{
	bool operator()(const Uzel* l, const Uzel* r) const { return l->a < r->a; }
};
void Print(Uzel* root, unsigned k=0) {
	if (root != NULL) {
		Print(root->left, k + 3);
		for (unsigned i = 0; i < k; i++) {
			cout << " ";
		}
		if (root->c) {
			cout << root->a << " (" << root->c << ")" << endl;
		}
		else {
			cout << root->a << endl;
			Print(root->right, k + 3);
		}
	}
}
vector<bool> code;
map<char, vector<bool> > table;// ������� �������������� ���� � ��������

void Build(Uzel* root) {
	if (root->left != NULL) // ���� ����� ���-�� ���� ������ � ������ 0
	{
		code.push_back(0);
		Build(root->left); // ���������� �������� �������
	}

	if (root->right != NULL)// ���� ������ ���-�� ���� ������ � ������ 1
	{
		code.push_back(1);
		Build(root->right);// ���������� �������� �������
	}

	if (root->left == NULL && root->right == NULL) {
		table[root->c] = code;  // ���� ���������� �� �����, �� ����������� � � ����� � table

	}
	if (!code.empty()) {
		code.pop_back(); //��������� ��� �� 1}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	ifstream file1("11.txt", ios::out | ios::binary);
	map<char, int>  m;
	while (!file1.eof()) { //���� ���������� ��������� ������� �������
		char c = file1.get();
		m[c]++;
	}
	list<Uzel*> da;

	map<char, int>::iterator i;

	for (i = m.begin(); i != m.end(); ++i) {
		Uzel* k = new Uzel;
		k->c = i->first; // char � map 
		k->a = i->second; // int � map
		da.push_back(k); // ��������� ��������� � list
	}
	while (da.size() != 1) // ���� �� ���������� ���� �������
	{
		da.sort(MyCompare()); //���������� �� MyCompare

		Uzel* SonL = da.front(); // ������ ������ ������� ���� ������ ������� �� list 
		da.pop_front(); // ������� �������
		Uzel* SonR = da.front(); // ������ ������� ������� ���� ������(����� �������� �������) ������� �� list 
		da.pop_front(); // ������� �������

		Uzel* parent = new Uzel(SonL, SonR); // ������ ���� 
		da.push_back(parent); // ��������� ��� � list
	}
	Uzel* root = da.front(); // ��������� �� ������ ������
	//Print(root);
	Build(root);

	file1.clear(); // ���������� ���������
	file1.seekg(0);// ���������� ��������� � ������ �����

	fstream file1_cip("112.txt", ios::binary | ios::out);
	int c = m.size();
	char buff = 0;
	file1_cip.write((char*)&c, sizeof(int));
	for (i = m.begin(); i != m.end(); ++i) {
		buff = i->first;
		c = i->second;
		file1_cip.write((char*)&buff, sizeof(char));
		file1_cip.write((char*)&c, sizeof(int));
	}

	int count = 0; // �������
	char buf = 0; //��������������� ����������
	while (!file1.eof()) {
		char c = file1.get();
		vector<bool> x = table[c];
		for (int j = 0; j < x.size(); j++) {
			buf = buf | x[j] << (7 - count); // ����������� ������ x � ����
			count++;
			if (count == 8) { count = 0; file1_cip << buf; buf = 0; } // ���� �������� count = 8  ���� ��������� � file1_cip
		}
	}

	file1.close(); // �� �������� ������� ����
	file1_cip.close(); // �� �������� ������� ����
	main1();
	return 0;
}
