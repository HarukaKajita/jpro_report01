#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>

//デバッグ時のディレクティブ定義
//#define _DEBUG
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
	void decrement();	//numberを1減らす
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
	void increase_foods(int, string, int);
	void reduction_foods(int);
};

void Storage::input_foods() {
	//ファイルからの入力の準備
	cout << "Input Foods." << endl;;
	cout << "Filename? :";
	string fname;
#ifdef  _DEBUG
	fname = "foods_input.txt";
#else
	cin >> fname;
#endif // _DEBUG


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
			increase_foods(i, current_name, 1);
		}

	}
}

void Storage::output_foods() {
	//ファイルからの入力の準備
	cout << "Output Foods." << endl;;
	cout << "Filename? :";
	string fname;
#ifdef _DEBUG
	fname = "foods_output.txt";
#else
	cin >> fname;
#endif // _DEBUG

	ifstream fin(fname.c_str());
	if (!fin) {
		cerr << "File Not Found" << endl;
		exit(1);//異常終了
	}

	string current_name;//ファイルから一行読み込んだ食品名

	Food unexistFoods[300];
	int unexistFoodsNum = 0;

	while (fin >> current_name) {
		//一行ずつ読んで配列から該当食品を探しデクリメント
		for (int i = 0; i < cnt; i++) {

			if (foods[i].check_name(current_name)) {
				foods[i].decrement();
				//食品の在庫が0になったらリストから削除
				if (foods[i].get_number() == 0) reduction_foods(i);
				break;
			}

			//取り出そうとした食品がリストに存在しなかった場合の処理
			//在庫がないのに取り出そうとした個数をカウントして配列に所持
			if (i == cnt-1) {
				if (unexistFoodsNum == 0) {
					unexistFoods[0] = Food(current_name, 1);
					unexistFoodsNum++;
				} else {
					for (int i = 0; i < unexistFoodsNum; i++) {
						if (unexistFoods[i].check_name(current_name)) {
							unexistFoods[i].increment();
							break;
						}
						if (i == unexistFoodsNum - 1) {
							unexistFoods[unexistFoodsNum] = Food(current_name, 1);
							unexistFoodsNum++;
							break;
						}
					}
				}
			}
		}
	}

	//存在しないのに取り出そうしていた場合は足りていなかった食品の情報を出力
	if (unexistFoodsNum > 0) {
		cout << endl;
		cout << "=====存在しないのに取り出そうとした食品=====" << endl;
		for (int i = 0; i < unexistFoodsNum; i++) {
			cout << "[" << setw(2) << i + 1 << "] ";
			unexistFoods[i].printFood();
		}
		cout << "============================================" << endl;
	}
}

void Storage::increase_foods(int index, string foodName, int num) {
	foods[index] = Food(foodName, num);
	cnt++;
}

//foods配列から引数で指定した要素番号の要素を削除する
void Storage::reduction_foods(int index) {
	//削除する要素以降の要素を一つ後の要素で上書きして要素を詰める
	for (int i = index; i < cnt - 1; i++) {

		//次の要素ので上書き
		swap(foods[i], foods[i + 1]);
	}
	cnt--;
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