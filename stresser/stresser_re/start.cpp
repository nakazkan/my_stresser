#include <bits/stdc++.h>
using namespace std;


int main () {
	//открываю файл для чтения настроек
	ifstream in("stresser.cfg", ios_base::in);
	string s;

	int count = 0; //количество стресс тестирований
	string st_e, //здесь содержиться название исполняемого файла стресс-решения
	st_c, //здесь содержится название исходного файла стресс-решения 
	so_e, //здесь содержится название исполняемого файла некорректного решения
	so_c, //здесь содеожится название исходного файла некорректного решения
	cm_e, //здесь содержится название исполняемого файла пользовательского чекера
	cm_c, //здесь содержится название исходного файла пользовательского чекера
	ge_e, //здесь содержится название исполняемого файла генератора
	ge_c, //здесь содержится название исходного фалйа генератора
	ch_c, //название исходного файла чекера (пользовательский или стандартный чекер - зависит от 'bool cmp')
	ch_e, //название исполняемого файла чекера
	st_t, //название файла, где храниться стресс-тест
	en, //строка, которую выводит чекер при ненахождении контр теста
	dir; //директория, в которой находится программа
	bool cmp = false; //отвечает за то, какой чеке используется (false если стандартный)

	//для "вырезания" нужной части строки используется простая формула :
	// x - начало нужной части строки
	// substr(x + 'длина ненужной строки', 'длина строки' - (x + 'длина ненужной строки') + 1)

	while (in >> s) {
		int x = s.find("start.stress_tests_count");
		if (x != string::npos) {
			string d = s.substr(x + 25, s.size() - (x + 25) + 1);
			count = atoi(d.c_str());
			continue;
		}

		x = s.find("start.stress.exe");
		if (x != string::npos) {
			st_e = s.substr(x + 17, s.size() - (x + 17) + 1);
			continue;
		}

		x = s.find("start.stress.cpp");
		if (x != string::npos) {
			st_c = s.substr(x + 17, s.size() - (x + 17) + 1);
			continue;
		}

		x = s.find("start.solve.exe");
		if (x != string::npos) {
			so_e = s.substr(x + 16, s.size() - (x + 16) + 1);
			continue;
		}

		x = s.find("start.solve.cpp");
		if (x != string::npos) {
			so_c = s.substr(x + 16, s.size() - (x + 16) + 1);
			continue;
		}

		x = s.find("start.cmp.use");
		if (x != string::npos) {
			cmp = s.back() - '0';
			continue;
		}

		x = s.find("start.cmp.exe");
		if (x != string::npos) {
			cm_e = s.substr(x + 14, s.size() - (x + 14) + 1);
			continue;
		}

		x = s.find("start.cmp.cpp");
		if (x != string::npos) {
			cm_c = s.substr(x + 14, s.size() - (x + 14) + 1);
			continue;
		}

		x = s.find("start.generator.exe");
		if (x != string::npos) {
			ge_e = s.substr(x + 20, s.size() - (x + 20) + 1);
			continue;
		}

		x = s.find("start.generator.cpp");
		if (x != string::npos) {
			ge_c = s.substr(x + 20, s.size() - (x + 20) + 1);
			continue;
		}

		x = s.find("start.stress_test.txt");
		if (x != string::npos) {
			st_t = s.substr(x + 22, s.size() - (x + 22) + 1);
			continue;
		}

		x = s.find("start.end");
		if (x != string::npos) {
			en = s.substr(x + 10, s.size() - (x + 10) + 1);
			continue;
		}

		x = s.find("start.dir");
		if (x != string::npos) {
			dir = s.substr(x + 10, s.size() - (x + 10) + 1);
			continue;
		}
	}


	//здесь производится компиляция всех нужных файлов
	string comp = string() + "g++ " + dir + st_c + " -o " + dir + st_e;
	system(comp.c_str());

	comp = string() + "g++ " + dir + so_c + " -o " + dir + so_e;
	system(comp.c_str());

	if (!cmp) {
		ch_c = "standart_checker.cpp";
		ch_e = "standart_checker.exe";
	}
	else {
		ch_c = cm_c;
		ch_e = cm_e;
	}

	comp = string() + "g++ " + dir + ch_c + " -o " + dir + ch_e;
	system(comp.c_str());

	comp = string() + "g++ " + dir + ge_c + " -o " + dir + ge_e;
	system(comp.c_str());


	//здесь производятся стресс тестирования
	while (count--) {
		string d;
		d = dir + ge_e;
		system(d.c_str());

		d = dir + st_e;
		system(d.c_str());

		d = dir + so_e;
		system(d.c_str());

		d = dir + ch_e;
		system(d.c_str());

		ifstream _in(st_t.c_str(), ios_base::in);
		_in >> d;
		if (d != en)
			break;
	}


	in.close();

	return 0;
}