#include <iostream>
#include<windows.h>
#include <iomanip>
#include<string>
#include<map>
using namespace std;
//货物结构
struct wares {
	int count; //货物数量
	int id;    //货物编码
	int value;  //货物价格
};
//第一级操作
void constructor(map<string, wares> &goods);
//第一级操作界面的选项
void printorder();
//进入系统时的欢迎词
void welcome();
//通过货物编码寻找货物名称
string findid(map<string, wares> &goods,int id);
//改变货物编码或单价
void change(map<string, wares> &goods);
//进行增加货物或数量
void input(map<string, wares> &goods);
//进行删除货物或减少货物数量
void output(map<string, wares> &goods);
//进行查询
void find(map<string, wares> &goods);
//判断货物是否存在
bool ifexist(const string& keyName, map<string, wares> goods);
//判断输入是否合法
bool verifyint(const string &amount);
//将字符转换为数
int tran(string str);

void printorder() {
	cout << "请按下列提示进行操作\n1.进货\n2.出货\n3.改变单价或货物编码\n4.查询\n5.退出系统" << endl;
}

void welcome() {
	cout << "欢迎使用仓库管理系统" << endl;
	printorder();
}

void input(map<string, wares> &goods) {
	cout << "1.增加已有货物数量\n2.增加新货物\n3.返回上一级" << endl;
	string command1;
	cin >> command1;
	system("cls");
	if (command1 == "2") {
		string name;
		struct wares ware;
		do {
			cout << "请输入货物名称（可输入除空格外任意字符）" << endl;
			cin >> name;
			system("cls");
			if (ifexist(name, goods) == 1) {
				goods.insert(pair<string, wares>(name, ware));
				cout << "该货物已存在，请重新输入" << endl;
			}
		} while (ifexist(name, goods) == true);
		string amount;
		do {
			cout << "请输入货物数量(请输入不超过九位的数字)" << endl;
			cin >> amount;
			system("cls");
			if (verifyint(amount) != 1) {
				cout << "输入不合法，请重新输入" << endl;
			}
			else {
				ware.count = tran(amount);
			}
		} while (verifyint(amount) != true);
		do {
			cout << "请输入货物编码(请输入不超过九位的数字)" << endl;
			cin >> amount;
			system("cls");
			if (verifyint(amount) != 1) {
				cout << "输入不合法，请重新输入" << endl;
			}
			if (findid(goods, tran(amount)) != "error") {
				cout << "该编码已存在，请重新输入" << endl;
			}
			else {
				ware.id = tran(amount);
			}
		} while (verifyint(amount) != true || findid(goods, tran(amount)) != "error");
		do {
			cout << "请输入货物单价(请输入不超过九位的数字)" << endl;
			cin >> amount;
			system("cls");
			if (verifyint(amount) != 1) {
				cout << "输入不合法，请重新输入" << endl;
			}
			else {
				ware.value = tran(amount);
			}
		} while (verifyint(amount) != true);
		goods.insert(pair<string, wares>(name, ware));
		cout << "增加完成，即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		input(goods);
	}
	else if (command1 == "1") {
		cout << "1.按货物名字进行访问\n2.按货物编码进行访问\n3.返回上一级" << endl;
		string command;
		cin >> command;
		system("cls");
		if (command == "1") {
			string name, upcount;
			do {
				cout << "请输入要增加的货物名称" << endl;
				cin >> name;
				system("cls");
				if (ifexist(name, goods) != true) {
					cout << "该货物不存在，请重新输入" << endl;
				}
			} while (ifexist(name, goods) != 1);
			do {
				cout << "请输入要增加的货物数量" << endl;
				cin >> upcount;
				system("cls");
				if (verifyint(upcount) != true) {
					cout << "输入不合法，请重新输入" << endl;
				}
			} while (verifyint(upcount) != true);
			int countup = tran(upcount);
			goods[name].count += countup;
			cout << "增加成功" << endl;
			Sleep(500);
			system("cls");
			input(goods);
		}
		if (command == "2") {
			string id1, upcount;
			int id = -1;
			do {
				cout << "请输入要增加的货物编码" << endl;
				cin >> id1;
				system("cls");
				if (verifyint(id1) == false) {
					cout << "输入不合法，请重新输入" << endl;
					continue;
				}
				else {
					id = tran(id1);
				}
				if (findid(goods,id) == "error") {
					cout << "该货物不存在，请重新输入" << endl;
				}
			} while (findid(goods,id) == "error");
			do {
				cout << "请输入要增加的货物数量" << endl;
				cin >> upcount;
				system("cls");
				if (verifyint(upcount) != true) {
					cout << "输入不合法，请重新输入" << endl;
				}
			} while (verifyint(upcount) != true);
			int countup = tran(upcount);
			string name = findid(goods, id);
			goods[name].count += countup;
			cout << "增加成功" << endl;
			Sleep(500);
			system("cls");
			input(goods);
		}
		else if (command == "3") {
			cout << "即将返回上一步" << endl;
			Sleep(500);
			system("cls");
			input(goods);
		}
		else {
			cout << "输入错误，即将返回上一步" << endl;
			Sleep(500);
			system("cls");
			input(goods);
		}
	}
	else if(command1 == "3"){
		cout << "即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		printorder();
		constructor(goods);
	}
	else {
		cout << "输入错误，即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		input(goods);
	}
}

void output(map<string, wares> &goods) {
	cout << "1.减少已有货物数量\n2.删除货物\n3.返回上一步" << endl;
	string command1;
	cin >> command1;
	system("cls");
	if (command1 == "2") {
		string command;
		cout << "1.按货物名字进行访问\n2.按货物编码进行访问\n3.返回上一级" << endl;
		cin >> command;
		system("cls");
		if (command == "1") {
			string name;
			cout << "请输入要删除的货物名称" << endl;
			cin >> name;
			system("cls");
			if (ifexist(name, goods) == 1) {
				goods.erase(name);
				cout << "删除完成，即将返回上一步" << endl;
			}
			else {
				cout << "商品不存在，即将返回上一步" << endl;
			}
		}
		else if (command == "2") {
			string id1;
			int id = -1;
			cout << "请输入要删除的货物编码" << endl;
			cin >> id1;
			system("cls");
			if (verifyint(id1) == true) {
				id = tran(id1);
			}
			string name = findid(goods, id);
			if (name != "error") {
				goods.erase(name);
				cout << "删除完成，即将返回上一步" << endl;
			}
			else {
				cout << "商品不存在，即将返回上一步" << endl;
			}
		}
		else if (command == "3") {
			cout << "即将返回上一步" << endl;
		}
		else {
			cout << "输入错误，即将返回上一步" << endl;
		}
		Sleep(500);
		system("cls");
		output(goods);
	}
	else if (command1 == "1") {
		cout << "1.按货物名字进行访问\n2.按货物编码进行访问\n3.返回上一级" << endl;
		string command;
		cin >> command;
		system("cls");
		if (command == "1") {
			string name, upcount;
			do {
				cout << "请输入货物名称" << endl;
				cin >> name;
				system("cls");
				if (ifexist(name, goods) != true) {
					cout << "该货物不存在，请重新输入" << endl;
				}
			} while (ifexist(name, goods) != 1);
			do {
				cout << "请输入要减少的货物数量" << endl;
				cin >> upcount;
				system("cls");
				if (verifyint(upcount) != true) {
					cout << "输入不合法，请重新输入" << endl;
				}
			} while (verifyint(upcount) != true);
			int countup = tran(upcount);
			goods[name].count -= countup;
			if (goods[name].count < 0) {
				goods[name].count = 0;
				cout << "减少数量多于库存，库存为0" << endl;
			}
			cout << "减少成功" << endl;
		}
		if (command == "2") {
			string id1, upcount;
			int id = -1;
			do {
				cout << "请输入货物编码" << endl;
				cin >> id1;
				system("cls");
				if (verifyint(id1) == false) {
					cout << "输入不合法，请重新输入" << endl;
					continue;
				}
				else {
					id = tran(id1);
				}
				if (findid(goods, id) == "error") {
					cout << "该货物不存在，请重新输入" << endl;
				}
			} while (findid(goods, id) == "error");
			do {
				cout << "请输入要减少的货物数量" << endl;
				cin >> upcount;
				system("cls");
				if (verifyint(upcount) != true) {
					cout << "输入不合法，请重新输入" << endl;
				}
			} while (verifyint(upcount) != true);
			int countup = tran(upcount);
			string name = findid(goods, id);
			goods[name].count -= countup;
			if (goods[name].count < 0) {
				goods[name].count = 0;
				cout << "减少数量多于库存，库存为0" << endl;
			}
			cout << "减少成功" << endl;
		}
		else if (command == "3") {
			cout << "即将返回上一步" << endl;
		}
		else {
			cout << "输入错误，即将返回上一步" << endl;
		}
		Sleep(500);
		system("cls");
		output(goods);
	}
	else if (command1 == "3") {
		cout << "即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		printorder();
		constructor(goods);
	}
	else {
		cout << "输入错误，即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		output(goods);
	}
}

void find(map<string, wares> &goods) {
	cout << "1.特定商品详情\n2.库存所有商品情况\n3.返回上一步" << endl;
	string command;
	cin >> command;
	system("cls");
	if (command == "3") {
		printorder();
		constructor(goods);
	}
	else if (command == "1") {
		cout << "1.通过名字查询\n2.通过货物编码查询\n3.返回上一步" << endl;
		cin >> command;
		system("cls");
		if (command == "1") {
			cout << "请输入货物名称" << endl;
			string name;
			cin >> name;
			system("cls");
			if (ifexist(name, goods) == 1) {
				cout << "商品名称:" << name << "\t数量:" << goods[name].count << "   \t货物编码:" << goods[name].id << "\t货物单价:" << goods[name].value << endl;
				system("pause");
				cout << "查找完成，即将返回上一步" << endl;
				Sleep(500);
				system("cls");
				find(goods);
			}
			else {
				cout << "这件物品不存在于仓库，即将返回上一步" << endl;
				Sleep(500);
				system("cls");
				find(goods);
			}
		}
		else if (command == "2") {
			cout << "请输入货物编码" << endl;
			string id1;
			int id = -1;
			cin >> id1;
			if (verifyint(id1) == true) {
				id = tran(id1);
			}
			system("cls");
			string name=findid(goods, id);
			if (name != "error") {
				cout << "商品名称:" << name << "\t数量:" << goods[name].count << "   \t货物编码:" << goods[name].id << "\t货物单价:" << goods[name].value << endl;
				system("pause");
				cout << "查找完成，即将返回上一步" << endl;
			}
			else {
				cout << "这件物品不存在于仓库，即将返回上一步" << endl;
			}
			Sleep(500);
			system("cls");
			find(goods);
		}
		else if (command == "3") {
			cout << "即将返回上一步" << endl;
			Sleep(500);
			system("cls");
			find(goods);
		}
		else {
			cout << "输入错误，即将返回上一步" << endl;
			Sleep(500);
			system("cls");
			find(goods);
		}
	}
	else if (command == "2") {
		system("cls");
		map<string, wares>::iterator it;
		it = goods.begin();
		//判断仓库中是否存在货物
		if (goods.size() == 0) {
			cout << "不存在货物" << endl;
		}
		else {
			while (it != goods.end()) {
				cout << "商品名称:" << it->first << "\t数量:" << it->second.count << "   \t货物编码:" << it->second.id << "\t货物单价:" << it->second.value << endl;
				it++;
			}
			system("pause");
			cout << "查找完成，即将返回上一步" << endl;
		}	
		Sleep(500);
		system("cls");
		find(goods);
	}
	else {
		cout << "输入错误，即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		find(goods);
	}
}

void constructor(map<string, wares> &goods) {
	string command;
	cin >> command;
	system("cls");
	if (command == "1") {
		input(goods);
	}
	else if (command == "2") {
		output(goods);
	}
	else if (command == "3") {
		change(goods);
	}
	else if (command == "4") {
		find(goods);
	}
}

bool ifexist(const string &keyName, map<string, wares> goods) {
	return (goods.find(keyName) != goods.end());
}

string findid(map<string, wares> &goods,int id) {
	map<string, wares>::iterator   it = goods.begin();
	for (; it != goods.end(); ++it) {
		if (id == it->second.id) {
			return it->first;
		}
	}
	string a = "error";
	return a;
}

void change(map<string, wares> &goods) {
	cout << "1.改变货物编码\n2.改变货物单价\n3.返回上一步" << endl;
	string command1;
	cin >> command1;
	system("cls");
	if (command1 == "1") {
		cout << "1.通过货物名称访问\n2.通过货物编码访问\n3.返回上一步" << endl;
		string command, newid;
		cin >> command;
		system("cls");
		if (command == "1") {
			string name;
			cout << "请输入货物名称" << endl;
			cin >> name;
			system("cls");
			if (ifexist(name, goods) == 1) {
				cout << "请输入货物编码" << endl;
				cin >> newid;
				if (verifyint(newid) == true) {
					if (findid(goods, tran(newid)) == "error") {
						goods[name].id = tran(newid);
					}
					else {
						cout << "该货物编码存在，即将返回上一步" << endl;
					}
				}
				else {
					cout << "输入不合法，即将返回上一步" << endl;
				}
			}
			else {
				cout << "该货物不存在，即将返回上一步" << endl;
			}
		}
		else if (command == "2") {
			string id;
			cout << "请输入货物编码" << endl;
			cin >> id;
			system("cls");
			if (verifyint(id) == true) {
				string name = findid(goods, tran(id));
				if (name != "error") {
					cout << "请输入新货物编码" << endl;
					cin >> newid;
					if (verifyint(newid) == true) {
						if (findid(goods, tran(newid)) == "error") {
							goods[name].id = tran(newid);
							cout << "货物编码修改成功，即将返回上一步" << endl;
						}
						else {
							cout << "该货物编码存在，即将返回上一步" << endl;
						}
					}
					else {
						cout << "输入不合法，即将返回上一步" << endl;
					}
					
				}
				else {
					cout << "该货物不存在，即将返回上一步" << endl;
				}
			}
			else {
				cout << "输入不合法，即将返回上一步" << endl;
			}		
		}
		else if (command == "3") {
			cout << "即将返回上一步" << endl;
		}
		else {
			cout << "输入错误，即将返回上一步" << endl;
		}
		Sleep(500);
		system("cls");
		change(goods);
	}
	else if (command1 == "2") {
		cout << "1.通过货物名称访问\n2.通过货物编码访问\n3.返回上一步" << endl;
		string command, newvalue;
		cin >> command;
		system("cls");
		if (command == "1") {
			string name;
			cout << "请输入货物名称" << endl;
			cin >> name;
			system("cls");
			if (ifexist(name, goods) == 1) {
				cout << "请输入货物单价" << endl;
				cin >> newvalue;
				if (verifyint(newvalue) == true) {
					goods[name].value = tran(newvalue);
					cout << "货物单价修改成功，即将返回上一步" << endl;
				}
				else {
					cout << "输入不合法，即将返回上一步" << endl;
				}
			}
			else {
				cout << "该货物不存在，即将返回上一步" << endl;
			}
		}
		else if (command == "2") {
			string id;
			cout << "请输入货物编码" << endl;
			cin >> id;
			system("cls");
			if (verifyint(id) == true) {
				string name = findid(goods, tran(id));
				if (name != "error") {
					cout << "请输入新单价" << endl;
					cin >> newvalue;
					if (verifyint(newvalue) == true) {
						goods[name].value = tran(newvalue);
						cout << "货物编码修改成功，即将返回上一步" << endl;
					}
					else {
						cout << "输入不合法，即将返回上一步" << endl;
					}			
				}
				else {
					cout << "该货物不存在，即将返回上一步" << endl;
				}
			}
			else {
				cout << "输入不合法，即将返回上一步" << endl;
			}
		}
		else if (command == "3") {
			cout << "即将返回上一步" << endl;
		}
		else {
			cout << "输入错误，即将返回上一步" << endl;
		}
		Sleep(500);
		system("cls");
		change(goods);
	}
	else if (command1 == "3") {
		cout << "即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		printorder();
		constructor(goods);
	}
	else {
		cout << "输入错误，即将返回上一步" << endl;
		Sleep(500);
		system("cls");
		change(goods);
	}	
}

bool  verifyint(const string &amount) {
	if (amount.size() > 9) {
		return false;
	}
	for (size_t a = 0; a < amount.size(); a++) {
		if (amount[a] < 48 || amount[a]>57) {
			return false;
		}
	}
	return true;
}

int tran(string str) {
	int num = 0;
	for (size_t a = 0; a < str.size(); a++) {
		num = num * 10 + str[a] - 48;
	}
	return num;
}

