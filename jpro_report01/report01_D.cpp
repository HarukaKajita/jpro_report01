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
	void decrement();	//numberを1増やす
	bool check_name(string);//食品名が一緒かどうかチェックする
	string get_name() { return name; }
	int get_number() { return number; }
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

void Food::decrement() {
	number--;
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
	void output_foods();
	void printStorage();
	void sort_by_number();
	void sort_by_name();
	void reduction_foods(int);
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

void Storage::output_foods() {
	//ファイルからの入力の準備
	cout << "Output Foods." << endl;;
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
		//一行ずつ読んで配列から該当食品を探しデクリメント
		for (int i = 0; i < cnt; i++) {

			if (!foods[i].check_name(current_name)) continue;
			foods[i].decrement();

			//食品の在庫が0になったらリストから削除
			if (foods[i].get_number() == 0) {
				reduction_foods(i);
				cnt--;
			}
			break;
		}
	}
}

//foods配列から引数で指定した要素番号の要素を削除する
void Storage::reduction_foods(int index) {
	//削除する要素以降の要素を一つ後の要素で上書きして要素を詰める

	for (int i = index; i < cnt-1; i++) {

		//次の要素ので上書き
		swap(foods[i], foods[i + 1]);
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

void Storage::sort_by_number()
{
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i + 1; j < cnt; j++) {
			//食品の数が昇順になっていなければswapFlagをtrueにする
			bool swapFlag = foods[j].get_number() < foods[i].get_number();
			if (!swapFlag) continue;
			//入れ替え
			swap(foods[i], foods[j]);
		}
	}
}

void Storage::sort_by_name()
{
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i + 1; j < cnt; j++) {
			//アルファベット順になっていなければswapFlagをtrueにする
			bool swapFlag = foods[j].get_name() < foods[i].get_name();
			if (!swapFlag) continue;
			//入れ替え
			swap(foods[i], foods[j]);
			//swapFoods(i,j);
		}
	}
}



int main() {
	Storage s1;
	s1.input_foods();

	s1.printStorage();
	s1.output_foods();

	s1.sort_by_name();
	s1.printStorage();

}
