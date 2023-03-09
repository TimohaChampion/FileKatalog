#include <iostream>
#include <windows.h>
#include<fstream>
#include <io.h>
#include <stdio.h>
#include <Windows.h>
using namespace std;

void test_open(const char* name) {
	FILE* pf;
	fopen_s(&pf, name, "r");
	//char str;
	//while (!feof(pf)) {
	//	fread_s(&str, sizeof(char), 1, 1, pf);
	//	//if (str != '\n')
	//	cout << str;
	//}
	cout << endl;
	fclose(pf);
}

class IHandler {
protected:
	IHandler* next = nullptr;
public:
	virtual void show(string path) = 0;
	void set_next(IHandler* next) {
		this->next = next;
	}
	virtual ~IHandler() {};
protected:
	bool isPath(string path) {
		_finddata_t* fileinfo = new _finddata_t;
		intptr_t done = _findfirst(path.data(), fileinfo);

		if (done != -1 && (fileinfo->attrib & _A_SUBDIR))
			return true;
		return false;
	}
};

class Handler_Path : public IHandler {
public:
	void show(string path) override {
		if (!isPath(path)) {
			if (next)next->show(path);
		}
		else {
			cout << "Hello, Handler_Path" << endl;

		}
	}
	~Handler_Path() {}
};

class Handler_Txt : public IHandler {
public:

	void show(string path) override {
		if (path.find(".txt") != -1 || path.find(".cpp") != -1) {
			cout << "Hello, Handler_Txt" << endl;
			test_open(path.data());
		}
		else {
			if (next)next->show(path);
		}
	}
	~Handler_Txt() {}
};

class Handler_Png : public IHandler {
public:
	void show(string path) override {
		if (path.find(".png") != -1) {
			cout << "Hello, Handler_Png" << endl;

		}
		else {
			if (next)next->show(path);
		}
	}
	~Handler_Png() {}
};

void test_find() {
	_finddata_t* fileinfo = new _finddata_t;
	intptr_t done = _findfirst("*.*", fileinfo);
	intptr_t isFind = done;
	while (isFind != -1) {
		cout << fileinfo->name << " " << fileinfo->attrib << " " << _A_SUBDIR;
		if (fileinfo->attrib & _A_SUBDIR) {
			cout << " dir ";
		}
		cout << "\n";
		//test_open(fileinfo->name);
		isFind = _findnext(done, fileinfo);
	}
	delete fileinfo;
}

void fun_filename() {
	IHandler* path_shower = new Handler_Path();
	IHandler* txt_shower = new Handler_Txt();
	IHandler* png_shower = new Handler_Png();

	/*path_shower->set_next(txt_shower);
	txt_shower->set_next(png_shower);*/

	_finddata_t* fileinfo1 = new _finddata_t;
	intptr_t done = _findfirst("*.txt", fileinfo1);
	intptr_t isFind = done;

	while (isFind != -1) {
		cout << fileinfo1->name;
		path_shower->show(fileinfo1->name);
		cout << endl;
		fstream f;
		string str;
		f.open(fileinfo1->name,ios::in);
		if (f.is_open()) {
			while (!f.eof()) {
				f >> str;
				cout << str;
			}
			f.close();
		}
		cout << "\n";
		isFind = _findnext(done, fileinfo1);
	}
	delete fileinfo1;
}



int main()
{
	SetConsoleCP(1251);
	setlocale(0, "ru");

	IHandler* path_shower = new Handler_Path();
	IHandler* txt_shower = new Handler_Txt();
	IHandler* png_shower = new Handler_Png();

	path_shower->set_next(txt_shower);
	txt_shower->set_next(png_shower);

	//path_shower->show("test.txt");
	//path_shower->show(""); //new_path
	//path_shower->show("1.png");

	_finddata_t* fileinfo = new _finddata_t;
	intptr_t done = _findfirst("*.*", fileinfo);
	intptr_t isFind = done;

	while (isFind != -1) {
		cout << fileinfo->name;
		//path_shower->show(fileinfo->name);
		cout << "\n";
		isFind = _findnext(done, fileinfo);
	}
	int value, k=0;
	while (k == 0) {
		cout << "Введите одну из команд: \"..\" - 1, \"имя каталога\" - 2, \"имя файла\" - 3, для заершения программы введите \"-1\"" << endl;
		cin >> value;
		switch (value) {
		case -1:k = -1; break;
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			fun_filename();
			break;
		default:cout << "Ошибка! Введите заново!" << endl;
		}

	}
	

	delete fileinfo;
	delete path_shower;
	delete txt_shower;
	delete png_shower;

	
	system("pause");
}




