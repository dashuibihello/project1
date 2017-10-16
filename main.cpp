#include <iostream>
#include <iomanip>
#include<fstream>
#include<map>
#include "source.h"
using namespace std;

int main() {
	ifstream fin("save.txt");
	welcome();
	map<string, wares> Goods;   //进行仓库的创建
	int num;
	fin >> num;
	for (int a = 0; a < num; a++) {
		struct wares good;
		string name;
		fin >> name >> good.count >> good.id >> good.value;
		Goods.insert(pair<string, wares>(name, good));

	}
	constructor(Goods);                              //进入系统进行操作
	cout << "感谢您的使用!再见！" << endl;          //退出系统的感谢
	system("pause");
	ofstream fout("save.txt");
	fout << Goods.size() << endl; 
	map<string, wares> ::iterator iter;
	if (!Goods.empty())
		for (iter = Goods.begin(); iter != Goods.end(); ++iter) {
			fout << iter->first << " " << iter->second.count << " " << iter->second.id << " " << iter->second.value << endl;
		}
	fout.close();
	fin.close();

	return 0;
}
