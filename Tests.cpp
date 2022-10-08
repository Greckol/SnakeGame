#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <conio.h>

using namespace std;

void EndGame(map<int, vector<int>> h) {
	char ok;
	system("cls");
	cout << ("GAME OVER, SCORE: ") << h.size() - 1;
	cin >> ok;
}

void CreateSnake(int x, int y, vector<vector<int>>& v, map<int, vector<int>>& h) {
	h[0] = {x / 2, y / 2};	//добавление в историю
	
}

void PrintField(vector<vector<int>> v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int b = 0; b < v[i].size(); ++b) {
			cout << v[i][b] << " ";
		}
		cout << endl;
	}
}

vector<int> CreateBerry(vector<vector<int>>& f, map<int, vector<int>>& h) {
	srand(time(0));
	vector<int> test;
	int flag;
	while (1) {
		flag = 1;
		int rnd_x = 1 + rand() % (f.size() -1 - 1); // строки
		int rnd_y = 1 + rand() % (f[0].size() - 1 - 1); // столбцы
		test = { rnd_x, rnd_y };
		for (auto i : h) {
			if (i.second == test) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) break;
	}
	f[test[0]][test[1]] = 5;
	return test;
}

void Check(map<int, vector<int>>& h) {
	if (h.size() > 1) {
		if (h[0] == h[1]) EndGame(h);
	}
};

void Move(char m, vector<vector<int>>& v, map<int, vector<int>>& h, vector<int>& b) {
	vector<int> copy_first, copy_second;
	if (m == 'w') {
		copy_first = { h[0][0], h[0][1] };	// копирование изначального положения
		h[0][0] -= 1;	// Поднять первый элемент 
		Check(h);	// проверка на разбитие

		if (h[0] == b) {		// пройдение через ягоду
			h[h.size()] = h[h.size() - 1];
			b = CreateBerry(v, h);
		}

		for (int i = 1; i < h.size(); ++i) {
			copy_second = h[i];
			h[i] = copy_first;
			copy_first = copy_second;
		}
	}

	else if (m == 'a') {
		copy_first = { h[0][0], h[0][1] };	// копирование изначального положения
		h[0][1] -= 1;	// свинуть влево первый элемент 
		Check(h);

		if (h[0] == b) {		// пройдение через ягоду
			h[h.size()] = h[h.size() - 1];
			b = CreateBerry(v, h);
		}

		for (int i = 1; i < h.size(); ++i) {
			copy_second = h[i];
			h[i] = copy_first;
			copy_first = copy_second;
		}
	}

	else if (m == 's') {
		copy_first = { h[0][0], h[0][1] };	// копирование изначального положения
		h[0][0] += 1;	// свинуть вниз первый элемент 
		Check(h);

		if (h[0] == b) {		// пройдение через ягоду
			h[h.size()] = h[h.size() - 1];
			b = CreateBerry(v, h);
		}

		for (int i = 1; i < h.size(); ++i) {
			copy_second = h[i];
			h[i] = copy_first;
			copy_first = copy_second;
		}
	}

	else if (m == 'd') {
		copy_first = { h[0][0], h[0][1] };	// копирование изначального положения
		h[0][1] += 1;	// свинуть вправо первый элемент 
		Check(h);

		if (h[0] == b) {		// пройдение через ягоду
			h[h.size()] = h[h.size() - 1];
			b = CreateBerry(v, h);
		}

		for (int i = 1; i < h.size(); ++i) {
			copy_second = h[i];
			h[i] = copy_first;
			copy_first = copy_second;
		}
	}
}

void ChangeElement(vector<vector<int>>& v, map<int, vector<int>>& h, vector<int>& b) {
	for (int i = 0; i < v.size(); ++i) {
		for (int b = 0; b < v[i].size(); ++b) {
			if ((i == 0 || i == v.size()-1) || (b == 0 || b == v.size() - 1)) {
				v[i][b] = 2;	//рамка
			}
			else {
				v[i][b] = 0;
			}
		}
	}

	for (auto i : h) {
		if (h[0][0] == 0 || h[0][0] == v.size() - 1 ||
			h[0][1] == 0 || h[0][1] == v.size() - 1) EndGame(h); // проверка на выход за границы поля

		if (i.first == 0) {
			v[i.second[0]][i.second[1]] = 9;	//голова
			for (int t = 1; t < h.size(); t++) {
				if (h[0] == h[t]) EndGame(h);	//конец
			}
		}
		else {
			v[i.second[0]][i.second[1]] = 1;	//тело
		}
	}

	v[b[0]][b[1]] = 5;
}

void Input(vector<vector<int>>& v, map<int, vector<int>>& h, vector<int> b) {
	char ch;
	while (1) {
		ch = _getch();
		system("cls");
		if (ch == 'w') {
			Move('w', v, h, b);
		}
		else if (ch == 'a') {
			Move('a', v, h, b);
		}
		else if (ch == 's') {
			Move('s', v, h, b);
		}
		else if (ch == 'd') {
			Move('d', v, h, b);
		}
		ChangeElement(v, h, b);
		PrintField(v);
	}
}


int main() {
	int ramka = 1;
	int x = 6+ramka; int y = 6+ramka;	// field size
	vector<vector<int>> field;
	field.assign(x, vector<int>(y, 0));
	map<int, vector<int>> history;
	vector<int> ber = CreateBerry(field, history);


	//game
	CreateSnake(x, y, field, history);
	ChangeElement(field, history, ber);
	PrintField(field);
	Input(field, history, ber);
}