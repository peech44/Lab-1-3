#include <iostream>

#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
//display table
void display(int[10][10]);
//random rider position
void rand_rider(int[10][10], int[30], int[30], int& nr);
//flodor move
void flodor_move(int[10][10], char& turn, int& x, int& y, int& z, int& tmz, int& s);
//check flodor to exit
int win(int[10][10], int& x, int& y, int& s);
//check win or fail and show display bad-end or congrate
void check_s(int& s, int& level);
//rider move
void rider_move(int[10][10], int[30], int[30], int[30], int[30], int& s, int& nr);
//check level pass or fail
int newlevel(int[10][10], int[30], int[30], int& s, int& x, int& y, int& z, int& level, int& nr);
//set colum and row
const int colum = 10, row = 10;


int main() {

	cout << "Hello world" << endl;

	//user input position where he want
	// q w s
	// a   d
	// z x c
	char turn;
	//set table
	int n[row][colum] = {};
	//set x = row
	int x = 0;
	//set y = colum
	int y = 0;
	//set z to restore x
	int z = 0;
	//for y
	//set tmz to restore y
	int tmz = 0;
	//check s = 1 to turn, s = 2 gameover, s = 0 win
	int s = 1;
	//set level
	int level = 1;
	//number of rider
	int nr = 3;
	//set c d
	int c[30] = {};
	int d[30] = {};
	// set a b
	int a[30] = {};
	int b[30] = {};
	//default flodor
	n[x][y] = 1;
	//set exit
	n[9][9] = 2;

	while (level <= 10) {
		//random rider position
		rand_rider(n, a, b, nr);

		cout << "Welcome Level " << level;
		cout << "---------------------" << endl;
		//display table
		display(n);

		cout << "press q w e" << endl;
		cout << "      a   d" << endl;
		cout << "      z x c to walk..." << endl;
		do {
			//user move flodor to position
			flodor_move(n, turn, x, y, z, tmz, s);

			//rider move
			rider_move(n, a, b, c, d, s, nr);
			//display table
			display(n);
			//in flodor_move and rider move is set s if s=0 pass, s=1 turn again, s=2 fail;
		} while (s == 1);
		// show display if fail or win
		check_s(s, level);
		//set default if win and out of loop if fail
		newlevel(n, a, b, s, x, y, z, level, nr);

	}


	system("pause");
	return 0;

}


//check flodor to exit
int win(int n[10][10], int& x, int& y, int& s) {
	//if flodor = n[9][9] return s=0
	if (n[x][y] == n[9][9]) {
		s = 0;
		return s;

	}
	return 1;
}
// check display win or fail
void check_s(int& s, int& level) {
	if (s == 0) {
		cout << endl;
		cout << "------Congratulation you win!!!!-------" << endl;
		if (level == 10) {
			cout << "------Congratulation your mission is complete !!!-------" << endl;
		}
	}
	else {
		cout << endl;
		cout << "------Bad end you are weak!!!!-------" << endl;

	}
}
//display table
void display(int n[10][10]) {
	//create table
	for (int j = 0; j <= 9; j++) {
		for (int i = 0; i <= 9; i++) {
			//if n[j][i] = 0 ,show space.
			if (n[j][i] == 0) {
				cout << setw(1) << "|" << " ";

			}
			//if n[j][i] = 1 ,show * ,It is player 
			else if (n[j][i] == 1) {
				cout << setw(1) << "|" << "F";
			}
			//if n[j][i] = 2 ,show E ,It is Exit
			else if (n[j][i] == 2) {
				cout << setw(1) << "|" << "E";
			}
			//if n[j][i] = 3 ,show R ,It is DarkRider
			else if (n[j][i] == 3) {
				cout << setw(1) << "|" << "R";
			}


		}
		cout << "|";
		cout << endl;
		cout << "---------------------" << endl;

	}

}
//set default if going to next level
int newlevel(int n[10][10], int a[30], int b[30], int& s, int& x, int& y, int& z, int& level, int& nr) {
	//set default
	if (s == 0) {
		x = 0;
		y = 0;
		z = 0;
		s = 1;

		n[x][y] = 1;
		n[9][9] = 2;
		//set rider = 0
		for (int i = 0; i < nr; i++) {

			n[a[i]][b[i]] = 0;
		}
		//add rider+3
		nr = nr + 3;
		//return level
		return level++;


	}
	else if (s == 2) {
		//if fail return 11 ad out of loop
		return level = 11;
	}
	return level = 11;

}
//rider move
void rider_move(int n[10][10], int a[30], int b[30], int c[30], int d[30], int& s, int& nr) {
	//random move
	for (int i = 0; i < nr; i++) {
		int checkrider = 0;
		while (checkrider == 0) {
			// e set row of a[i] and already to random 
			int e[3] = { a[i], a[i] - 1, a[i] + 1 };
			// e set colum of b[i] and already to random 
			int f[3] = { b[i], b[i] - 1, b[i] + 1 };
			//set int to already to random
			int je = 0;
			int jf = 0;

			// random 0-2
			je = rand() % 3;
			jf = rand() % 3;

			//set new position c[i]
			//set new position d[i]
			//to replace a[i] and b[i]
			c[i] = e[je];
			d[i] = f[jf];

			//check if random to same position
			if (n[a[i]][b[i]] == n[c[i]][d[i]]) {
				checkrider = 0;

			}
			//check if position out of table
			else if (c[i] < 0 || c[i] > 9) {
				checkrider = 0;

			}
			//check if position out of table
			else if (d[i] < 0 || d[i] > 9) {
				checkrider = 0;

			}
			//check if position is = Exit
			else if (n[c[i]][d[i]] == n[9][9]) {
				checkrider = 0;

			}
			//check if position random to another DarkRider
			else if (n[c[i]][d[i]] == 3) {
				checkrider = 0;

			}
			//check if position random to place Flodor
			else if (n[c[i]][d[i]] == 1) {
				checkrider = 1;
				s = 2;

			}
			//check if position is normal
			else {
				checkrider = 1;

				n[a[i]][b[i]] = 0;
				n[c[i]][d[i]] = 3;
				a[i] = c[i];
				b[i] = d[i];
			}

		}

	}
}
//flodor move
void flodor_move(int n[10][10], char& turn, int& x, int& y, int& z, int& tmz, int& s) {

	int check = 1;
	while (check == 1) {

		cout << "Enter here ";
		cin >> turn;
		cout << endl;
		//switch case q w e a d z x c.
		switch (turn)
		{


		case 'q':
			z = x;
			tmz = y;
			x = x - 1;
			y = y - 1;
			//if go out of table
			if (x < 0 || y < 0) {
				x = z;
				y = tmz;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[z][tmz] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;

		case 'w':
			z = x;
			x = x - 1;
			//if go out of table
			if (x < 0) {
				x = z;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[z][y] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;

		case 'e':
			z = x;
			tmz = y;
			x = x - 1;
			y = y + 1;
			//if go out of table
			if (x < 0 || y > 9) {
				x = z;
				y = tmz;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[z][tmz] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;


		case 'a':
			z = y;
			y = y - 1;
			//if go out of table
			if (y < 0) {
				y = z;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[x][z] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;


		case 'd':
			z = y;
			y = y + 1;
			//if go out of table
			if (y > 9) {
				y = z;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[x][z] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;
		case 'z':
			z = x;
			tmz = y;
			x = x + 1;
			y = y - 1;
			//if go out of table
			if (x > 9 || y < 0) {
				x = z;
				y = tmz;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[z][tmz] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;
		case 'x':
			z = x;
			x = x + 1;
			//if go out of table
			if (x > 9) {
				x = z;
				cout << "Wrong way pls try again!! " << endl;
			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[z][y] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;
		case 'c':
			z = x;
			tmz = y;
			x = x + 1;
			y = y + 1;
			//if go out of table
			if (x > 9 || y > 9) {
				x = z;
				y = tmz;
				cout << "Wrong way pls try again!! " << endl;

			}
			//if to go place rider
			else if (n[x][y] == 3) {
				s = 2;
				check = 0;

			}
			//go good position
			else {
				n[z][tmz] = 0;
				n[x][y] = 1;
				check = 0;
				win(n, x, y, s);
			}

			break;



		default:
			check = 1;
			cout << "Unknow pls type again" << endl;

			break;
		}
	}
}
//random rider position
void rand_rider(int n[10][10], int a[30], int b[30], int& nr) {
	//srand time
	srand(time(0));
	//random rider
	for (int i = 0; i < nr; i++) {
		int checksame = 0;
		while (checksame == 0) {

			a[i] = rand() % 8 + 1;
			b[i] = rand() % 8 + 1;
			//if random same position go to new random
			if (n[a[i]][b[i]] == 3) {
				checksame = 0;
			}
			//it's work
			else {
				n[a[i]][b[i]] = 3;
				checksame = 1;
			}

		}
	}

}
/////finished !!!!!