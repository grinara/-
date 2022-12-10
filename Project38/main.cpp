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
map<char, vector<bool> > table;// таблица асооциирования кода с символом

void Build(Uzel* root) {
	if (root->left != NULL) // если слева что-то есть вносим в вектор 0
	{
		code.push_back(0);
		Build(root->left); // рекурсивно вызываем функцию
	}

	if (root->right != NULL)// если справа что-то есть вносим в вектор 1
	{
		code.push_back(1);
		Build(root->right);// рекурсивно вызываем функцию
	}

	if (root->left == NULL && root->right == NULL) {
		table[root->c] = code;  // если наткнулись на букву, то ассоциируем её с годом в table

	}
	if (!code.empty()) {
		code.pop_back(); //сокращаем код на 1}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	ifstream file1("11.txt", ios::out | ios::binary);
	map<char, int>  m;
	while (!file1.eof()) { //ищём количество вхождений каждого символа
		char c = file1.get();
		m[c]++;
	}
	list<Uzel*> da;

	map<char, int>::iterator i;

	for (i = m.begin(); i != m.end(); ++i) {
		Uzel* k = new Uzel;
		k->c = i->first; // char в map 
		k->a = i->second; // int в map
		da.push_back(k); // добовляем указатель в list
	}
	while (da.size() != 1) // пока не останеться один элемент
	{
		da.sort(MyCompare()); //сортировка по MyCompare

		Uzel* SonL = da.front(); // создаём левого потомка берём первый элемент из list 
		da.pop_front(); // удаляем элемент
		Uzel* SonR = da.front(); // создаём правого потомка берём первый(после удаления другого) элемент из list 
		da.pop_front(); // удаляем элемент

		Uzel* parent = new Uzel(SonL, SonR); // создаём узел 
		da.push_back(parent); // добавляем его в list
	}
	Uzel* root = da.front(); // указатель на корень дерева
	//Print(root);
	Build(root);

	file1.clear(); // сбрасываем указатель
	file1.seekg(0);// возвращаем указатель в начало файла

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

	int count = 0; // счётчик
	char buf = 0; //вспомогательная переменная
	while (!file1.eof()) {
		char c = file1.get();
		vector<bool> x = table[c];
		for (int j = 0; j < x.size(); j++) {
			buf = buf | x[j] << (7 - count); // преобразуем вектор x в байт
			count++;
			if (count == 8) { count = 0; file1_cip << buf; buf = 0; } // если достигли count = 8  байт записывем в file1_cip
		}
	}

	file1.close(); // не забываем закрыть файл
	file1_cip.close(); // не забываем закрыть файл
	main1();
	return 0;
}
