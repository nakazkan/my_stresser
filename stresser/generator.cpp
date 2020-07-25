#include <bits/stdc++.h>
using namespace std;

int main () {
	ofstream out("stress_test.txt", ios_base::out | ios_base::trunc);


	srand(time(NULL));
	int a = rand(), b = rand();

	out << a << " " << b;

	out.close();

	return 0;
}