#include <bits/stdc++.h>
using namespace std;


int main () {

	ifstream in("stress_test.txt", ios_base::in);
	ofstream out("stress.out", ios_base::out | ios_base::trunc);

	int a, b;
	in >> a >> b;
	out << a + b;

	in.close();
	out.close();

	return 0;
}