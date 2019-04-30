#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>

using namespace std;

class Food {
private:
	string name;		//食品名
	int number;		//個数
public:
	Food();			//コンストラクタ
	Food(string, int);	//nameとnumberを設定可能なコンストラクタ
	void printFood();	//nameとnumberを出力する
	void increment();	//numberを1増やす
	bool check_name(string);//食品名が一緒かどうかチェックする
};

Food::Food() {//コンストラクタ(食品名は空文字列""に、個数は0に初期化)
	name = "";
	number = 0;
}

Food::Food(string str, int u) {//コンストラクタ(食品名はstrに、個数はuに初期化)
	name = str;
	number = u;
}

void Food::printFood() {
	cout << name << ":" << number << endl;
}

void Food::increment() {
	number++;
}

bool Food::check_name(string str) {
	if (name == str) {
		return true;
	}
	else {
		return false;
	}
}

class Storage {
private:
	Food foods[300];
	int cnt;
public:
	Storage() { cnt = 0; }
	void input_foods();
	void printStorage();
};

void Storage::input_foods() {
	//ファイルからの入力の準備
	cout << "Input Foods." << endl;;
	cout << "Filename? :";
	string fname;
	cin >> fname;
	ifstream fin(fname.c_str());
	if (!fin) {
		cerr << "File Not Found" << endl;
		exit(1);//異常終了
	}

	string current_name;//ファイルから一行読み込んだ食品名

	while (fin >> current_name) {
		int i;
		for (i = 0; i < cnt; i++) {
			if (foods[i].check_name(current_name)) {
				foods[i].increment();
				break;
			}
		}
		if (i == cnt) {
			foods[i] = Food(current_name, 1);
			cnt++;
		}

	}
}

void Storage::printStorage() {
	//食品リストの表示
	cout << endl;
	cout << "////////////// All Food List ///////////////" << endl;
	for (int i = 0; i < cnt; i++) {
		cout << "[" << setw(2) << i + 1 << "] ";
		foods[i].printFood();
	}
	cout << "////////////// All Food List END ///////////////" << endl;
	cout << endl;
}

int main() {
	Storage s1;
	s1.input_foods();
	s1.printStorage();
}
