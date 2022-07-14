#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long int



long long power(long long a, long long b, long long c)
{
	long long ans = 1;
	for (int i = 1; i <= b; i++)
	{
		ans *= a;
		ans %= c;
	}
	return ans;
}

long long numberToBinary(int number)
{
	int n = (int)(log2(number));
	string result = bitset<64>(number).to_string().substr(64 - n - 1);
	return atoll(result.c_str());
}

// a^b mod c
int process(int c, int d, int n)
{
	long long binaryNumber = numberToBinary(d);
	cout << d << " = " << binaryNumber << endl;
	int p = 0;
	int decNumber = 0;
	while (binaryNumber > 0)
	{
		int temp = (binaryNumber % 10) * pow(2, p);
		decNumber += temp;
		if (temp != 0)
		{
			cout << temp << " - ";
			cout << c << "^" << temp << " mod " << n << " = " << power(c, temp, n) << endl;
		}
		++p;
		binaryNumber /= 10;
	}
	cout << "\t" << c << "^" << d << " mod " << n << " = " << power(c, d, n) << endl;
	return (int)power(c, d, n);
}
int calculatorD(int n,int phi_n,int e) {
	int d = 1;
	for (int i = 1; i < n; i++)
	{
		if (((e * i) % phi_n) == 1)
		{
			d = i;
			break;
		}
	}
	return d;
}
void LapBang(int phi_n, int e) {
	int matrix[10][7];
	int i = 1;
	matrix[0][0] = phi_n / e;
	matrix[0][1] = phi_n;
	matrix[0][2] = e;
	matrix[0][3] = phi_n % e;
	matrix[0][4] = 0;
	matrix[0][5] = 1;
	matrix[0][6] = -(phi_n / e);
	cout << "q" << "\t" << "r1" << "\t" << "r2" << "\t" << "r" << "\t" << "t1" << "\t" << "t2" << "\t" << "t" << endl;
	cout << "==================================================" << endl;
	while (true)
	{
		matrix[i][1] = matrix[i-1][2];
		matrix[i][2] = matrix[i-1][3];
		matrix[i][4] = matrix[i-1][5];
		matrix[i][5] = matrix[i-1][6];
		if(matrix[i][2] == 0) {
			matrix[i][6] = -999;
			matrix[i][0] = -999;
			matrix[i][3] = -999;
			break;
		}
		
		matrix[i][0] = (matrix[i][1] / matrix[i][2]);
		matrix[i][3] = (matrix[i][1] % matrix[i][2]);
		matrix[i][6] = (matrix[i][4] - (matrix[i][5] * matrix[i][0]) );
		i++;	
	}
	
	
	for (size_t t = 0; t <= i; t++)
	{
		for (size_t j = 0; j < 7; j++)
		{
			cout << matrix[t][j] << "\t";
		}
		cout << "\n";
		
	}
	cout << "======================================================" << endl;
	if(matrix[i][4] > 0) {
		cout << "\nVi t1 > 0 nen d = t1";
		cout << "\nD = " << matrix[i][4] << endl;
	}else
	{
		cout << "\nVi t1 < 0 nen d = t1 + t2";
		cout << "\nD = " << (matrix[i][4] + matrix[i][5]) << endl;
	}
	
	
}

void show(int p, int q,int e, int n, int phi_n, int d) {
	cout << "P = " << p << "\t";
	cout << "Q = " << q << "\t";
	cout << "E = " << e << "\t";
	cout << "N = " << n << "\t";
	cout << "Phi(n) = " << phi_n << "\n";
	cout << "C2:D = " << d << "\n";
	cout << "Vi " << d << " * " << e << " = " << (d * e) << " = " << (d * e - 1) / phi_n << " * " << phi_n << " + 1" << endl << endl;
	LapBang(phi_n,e);
	cout << "KU" << "{" << e << "," << n << "}" << endl;
	cout << "KR" << "{" << d << "," << n << "}" << endl;
}
void program()
{
	int m,hm;
	int pa, qa, ea, pb, qb, eb;

	cout << "Nhap Alice(P,Q,E):";
	cin >> pa >> qa >> ea;
	cout << "Nhap Bob(P,Q,E):";
	cin >> pb >> qb >> eb;
	int na = pa * qa;
	int phi_na = (pa - 1) * (qa - 1);
	int da = calculatorD(na,phi_na,ea);
	cout << "\nAlice\n";
	show( pa,  qa, ea,  na,  phi_na,  da);
	// LapBang(phi_na,ea);

	// bob
	int nb = pb * qb;
	int phi_nb = (pb - 1) * (qb - 1);
	int db = calculatorD(nb,phi_nb,eb);
	cout << "\nBob\n";
	show( pb,  qb, eb,  nb,  phi_nb,  db);
	// LapBang(phi_nb,eb);

	while (true)
	{
		int choose;
		cout << "\n--------MENU-----------\n";
		cout << "\n1.Ma Hoa - Giai Ma\n";
		cout << "\n2.Ky Gui H(m)\n";
		cout << "\n3.Diffie-Hellman\n";
		cout << "\n0.Exit\n";
		cout << "\n--------END-----------\n";
		cout << "nhap lua chon:";
		cin >> choose;

		switch (choose)
		{
			case 0: {
				exit(0);
				break;
			}
			case 1:
			{
				int choose2;
				cout << "\n-------------------\n";
				cout << "\n1.Alice gui ban ro bob\n";
				cout << "\n2.Bob gui ban ro Alice\n";
				cout << "\n-------------------\n";
				cout << "nhap lua chon:";
				cin >> choose2;
				cout << "\nNhap M:";
				cin >> m;
				if (choose2 == 1)
				{
					cout << "\nMa Hoa\n";
					cout << "\nc = m^e mod n\n";
					int ca = process(m, eb, nb);
					cout << "\nGiai Ma\n";
					cout << "\nm = c^d mod n\n";
					process(ca, db, nb);
				}
				else if (choose2 == 2)
				{
					cout << "\nMa Hoa\n";
					cout << "\nc = m^e mod n\n";
					int cb = process(m, ea, na);
					cout << "\nGiai Ma\n";
					cout << "\nm = c^d mod n\n";
					process(cb, da, na);
				}
				else
				{
					cout << "\nNhap cc gi vay bro?\n";
				}
				break;
			}

			case 2:
			{
				int choose2;
				cout << "\n-----------------\n";
				cout << "\n1.Alice ky vao H(m)\n";
				cout << "\n2.Bob ky vao H(m)\n";
				cout << "\n-------------------\n";
				cout << "nhap lua chon:";
				cin >> choose2;
				cout << "\nNhap H(m):";
				cin >> hm;
				if (choose2 == 1)
				{
					cout << "\nMa Hoa\n";
					cout << "\ns = h(m)^d mod n\n";
					int s = process(hm, da, na);
					cout << "\nGiai Ma\n";
					cout << "\nh(m) = s^e mod n\n";
					process(s, ea, na);
				}
				else if (choose2 == 2)
				{
					cout << "\nMa Hoa\n";
					cout << "\ns = h(m)^d mod n\n";
					int s = process(hm, db, nb);
					cout << "\nGiai Ma\n";
					cout << "\nh(m) = s^e mod n\n";
					process(s, eb, nb);
				}
				else
				{
					cout << "\nNhap cc gi vay bro?\n";
				}
				break;
			}
			case 3: {
				int xa,xb,q,alpha;
				cout << "\nNhap Xa,Xb,Q,alpha:";
				cin >> xa >> xb >> q >> alpha;
				int ya = process(alpha, xa, q);
				cout << "\nYa = " << ya << endl << endl;
				int yb =  process(alpha, xb, q);
				cout << "\nYb = " << yb << endl;
				cout << "\n======================\n";
				cout << "\nBen A\n";
				process(yb, xa, q);
				cout << "\nBen B\n";
				process(ya, xb, q);
				break;
			}
			default:
				cout << "\nNhap cc gi vay bro?\n";
				break;
		}
	}
	
}


int main(int argc, char **argv)
{
	program();
	
	return 0;
}
