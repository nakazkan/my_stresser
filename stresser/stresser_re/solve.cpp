#include <bits/stdc++.h>
using namespace std;


int main () {
	ofstream out("solve.out", ios_base::out | ios_base::trunc);
	ifstream in("stress_test.txt", ios_base::in);

	int a, b;
	in >> a >> b;
	out << a << " " << b;

	in.close();
	out.close();

	return 0;
}