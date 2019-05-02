#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>

using namespace std;

class Food {
private:
	string name;		//�H�i��
	int number;		//��
public:
	Food();			//�R���X�g���N�^
	Food(string, int);	//name��number��ݒ�\�ȃR���X�g���N�^
	void printFood();	//name��number���o�͂���
	void increment();	//number��1���₷
	void decrement();	//number��1���₷
	bool check_name(string);//�H�i�����ꏏ���ǂ����`�F�b�N����
	string get_name() { return name; }
	int get_number() { return number; }
};

Food::Food() {//�R���X�g���N�^(�H�i���͋󕶎���""�ɁA����0�ɏ�����)
	name = "";
	number = 0;
}

Food::Food(string str, int u) {//�R���X�g���N�^(�H�i����str�ɁA����u�ɏ�����)
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
	//�t�@�C������̓��͂̏���
	cout << "Input Foods." << endl;;
	cout << "Filename? :";
	string fname;
	cin >> fname;
	
	ifstream fin(fname.c_str());
	if (!fin) {
		cerr << "File Not Found" << endl;
		exit(1);//�ُ�I��
	}

	string current_name;//�t�@�C�������s�ǂݍ��񂾐H�i��

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
	//�t�@�C������̓��͂̏���
	cout << "Output Foods." << endl;;
	cout << "Filename? :";
	string fname;
	cin >> fname;

	ifstream fin(fname.c_str());
	if (!fin) {
		cerr << "File Not Found" << endl;
		exit(1);//�ُ�I��
	}

	string current_name;//�t�@�C�������s�ǂݍ��񂾐H�i��

	while (fin >> current_name) {
		//��s���ǂ�Ŕz�񂩂�Y���H�i��T���f�N�������g
		for (int i = 0; i < cnt; i++) {

			if (!foods[i].check_name(current_name)) continue;
			foods[i].decrement();

			//�H�i�̍݌ɂ�0�ɂȂ����烊�X�g����폜
			if (foods[i].get_number() == 0) {
				reduction_foods(i);
				cnt--;
			}
			break;
		}
	}
}

//foods�z�񂩂�����Ŏw�肵���v�f�ԍ��̗v�f���폜����
void Storage::reduction_foods(int index) {
	//�폜����v�f�ȍ~�̗v�f�����̗v�f�ŏ㏑�����ėv�f���l�߂�

	for (int i = index; i < cnt-1; i++) {

		//���̗v�f�̂ŏ㏑��
		swap(foods[i], foods[i + 1]);
	}
}

void Storage::printStorage() {
	//�H�i���X�g�̕\��
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
			//�H�i�̐��������ɂȂ��Ă��Ȃ����swapFlag��true�ɂ���
			bool swapFlag = foods[j].get_number() < foods[i].get_number();
			if (!swapFlag) continue;
			//����ւ�
			swap(foods[i], foods[j]);
		}
	}
}

void Storage::sort_by_name()
{
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = i + 1; j < cnt; j++) {
			//�A���t�@�x�b�g���ɂȂ��Ă��Ȃ����swapFlag��true�ɂ���
			bool swapFlag = foods[j].get_name() < foods[i].get_name();
			if (!swapFlag) continue;
			//����ւ�
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
