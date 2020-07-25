#include <bits/stdc++.h>
using namespace std;

int main () {
	//открываю файл для чтения настройки
	ifstream in("stresser.cfg", ios_base::in);
	string s;

	string solve_in, //файл, в который выводит некорректное решение
	stress_in, //файл, в который выводит некорректное решение
	res, //файл, куда пишется результат чекера
	stress_test, //файл, где содержиться сам стресс-тест
	en; //строка, которую выводит чекер при ненахождении конт теста


	//та же формула, что и в start.cpp
	while (in >> s) {
		int x = s.find("standart_checker.input_solve");
		if (x != string::npos) {
			solve_in = s.substr(x + 29, s.size() - (x + 29) + 1);
			continue;
		}

		x = s.find("standart_checker.input_stress");
		if (x != string::npos) {
			stress_in = s.substr(x + 30, s.size() - (x + 30) + 1);
			continue;
		}

		x = s.find("standart_checker.res");
		if (x != string::npos) {
			res = s.substr(x + 21, s.size() - (x + 21) + 1);
			continue;
		}

		x = s.find("standart_checker.test");
		if (x != string::npos) {
			stress_test = s.substr(x + 22, s.size() - (x + 22) + 1);
			continue;
		}

		x = s.find("standart_checker.end");
		if (x != string::npos) {
			en = s.substr(x + 21, s.size() - (x + 21) + 1);
			continue;
		}
	}	

	in.close();

	ifstream in_sol(solve_in.c_str(), ios_base::in);
	ifstream in_str(stress_in.c_str(), ios_base::in);
	ofstream out(res.c_str(), ios_base::out | ios_base::trunc);

	string a, b;

	while (true) {
		//каждый раз читаю по строке из каждого файла
		getline(in_sol, a);
		getline(in_str, b);

		if (a != b) {
			//нашел контр тест, выпишу его 
			ifstream in_test(stress_test.c_str(), ios_base::in);
			while (!in_test.eof()) {
				string d;
				getline(in_test, d);
				out << d;
			}

			in_sol.close();
			in_str.close();
			out.close();
			in_test.close();

			return 0;
		}

		if (in_sol.eof() && in_str.eof()) {
			//не нашел контр тест и оба файла закончились
			out << en;

			in_sol.close();
			in_str.close();
			out.close();

			return 0;
		}
	}



	return 0;
}