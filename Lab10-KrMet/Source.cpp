#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Gammir {
private:
	string number_key, number_text, C_str, D_str, L_str, R_str;
	vector<string> Key_steps;
	vector<int> Polynom = { 5, 3, 2, 0 };
	vector<char> Alfabet = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };
	string Translate_En(string str, int size_n) {
		vector<char>::iterator it;
		string buf_number = "";
		int buf;
		for (int i = 0; i < size_n; i++) {
			char buf_char = _toupper(str[i]);
			it = find(Alfabet.begin(), Alfabet.end(), buf_char);
			if (it == Alfabet.end()) return "0";
			buf = it - Alfabet.begin();
			if (buf < 16) {
				char buf_itoa[5];
				_itoa_s(buf, buf_itoa, 2);
				string itoa_str(buf_itoa);
				buf_number = buf_number + "1100";
				for (int j = 0; j < 4 - itoa_str.size(); j++) {
					buf_number.push_back('0');
				}
				buf_number = buf_number + itoa_str;
			}
			else {
				buf = buf % 16;
				buf_number = buf_number + "1101";
				char buf_itoa[5];
				_itoa_s(buf, buf_itoa, 2);
				string itoa_str(buf_itoa);
				for (int j = 0; j < 4 - itoa_str.size(); j++) {
					buf_number.push_back('0');
				}
				buf_number = buf_number + itoa_str;
			}
		}
		return buf_number;
	}
	string Translate_Number(int number) {
		string bin_n = "";
		while (number > 0) {
			bin_n = (char)(number % 2 + 48) + bin_n;
			number /= 2;
		}
		while (bin_n.size() < 4) {
			bin_n = "0" + bin_n;
		}
		return bin_n;
	}
	void print_Poly(vector<int> polynom) {
		for (int i = 0; i < polynom.size(); i++) {
			if (polynom[i] == 0) {
				cout << 1;
				break;
			}
			cout << "X^" << polynom[i] << " + ";
		}
		cout << endl;
	}
	vector<int> Search_Px() {
		int max = Polynom[0];
		vector<int> Px = {};
		for (int i = Polynom.size() - 1; i >= 0; i--) {
			Px.push_back(max - Polynom[i]);
		}
		return Px;
	}
	vector<int> Search_Fx() {
		vector<int> Fx = {};
		for (int i = 0; i < Polynom.size(); ++i) {
			if (Polynom[i] == 0) {
				break;
			}
			Fx.push_back(Polynom[i] - 1);
		}
		return Fx;
	}
	string Gamma_Iterations() {
		int it = 0, buf_sum = 0, buf_n;
		string buf_key = number_key, gamma;
		char buf_ch;
		int size = number_key.size();
		while (true) {
			gamma = gamma + number_key[0];
			buf_n = size;
			for (int i = 0; i < Polynom.size(); i++) {
				buf_sum += (int)number_key[buf_n - Polynom[i] - 1] - 48;
			}
			if (buf_sum % 2 == 1) {
				buf_ch = '1';
			}
			else buf_ch = '0';
			buf_sum = 0;
			for (int i = 0; i < number_key.size() - 1; i++) {
				number_key[i] = number_key[i + 1];
			}
			number_key[number_key.size() - 1] = buf_ch;
			cout << number_key << endl;
			it++;
			if (buf_key == number_key) {
				break;
			}
		}
		cout << "Gamma: " << gamma << endl;
		cout << "Iteration: " << it << endl;
		return gamma;
	}
	string Encryption_of_gamma(string gamma) {
		string cipher = "";
		int buf_n;
		for (int i = 0, j = 0; i < number_text.size(); ++i) {
			buf_n = ((int)number_text[i] - 48 + (int)gamma[j] - 48);
			j++;
			if (buf_n % 2 == 1) {
				cipher = cipher + '1';
			}
			else {
				cipher = cipher + '0';
			}
			buf_n = 0;
			if (j == gamma.size() - 1)
				j = 0;
		}
		return cipher;
	}
public:
	void Encryption(string text, int key) {
		if (text.size() < 4) {
			cout << "Invalid text" << endl;
			return;
		}
		if (key < 1) {
			cout << "Invalid key" << endl;
			return;
		}
		number_text = Translate_En(text, text.size());
		if (number_text.size() < 4) {
			cout << "Invalid text" << endl;
			return;
		}
		cout << text << "(2) = " << number_text << endl;
		number_key = Translate_Number(key);
		if (number_key.size() < 4) {
			cout << "Invalid key" << endl;
			return;
		}
		cout << key << "(2) = " << number_key << endl;
		cout << "Polynom: ";
		print_Poly(Polynom);
		Polynom = Search_Px();
		cout << "Px: ";
		print_Poly(Polynom);
		Polynom = Search_Fx();
		cout << "Fx: ";
		cout << "X" << Polynom[0];
		for (int i = 1; i < Polynom.size(); ++i) {
			cout << " + " << "X" << Polynom[i];
		}
		cout << endl;
		string gamma = Gamma_Iterations();
		string cipher_text = Encryption_of_gamma(gamma);
		cout << "Cipher = " << cipher_text << endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}
};

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int task, exit = 1;
	string buf_in;
	string buf_in1;
	string text;
	int key;
	while (exit == 1) {
		Gammir Gam;
		cout << "1.Encryption DES" << endl << "2.Exit" << endl << "Choose a way:" << endl;
		cin.clear();
		cin >> task;
		switch (task)
		{
		case 1:
			cout << "Input top text:" << endl << "text = ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> text;
			cout << "Input key:" << endl << "key = ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> key;
			Gam.Encryption(text, key);
			break;
		case 2:
			exit = 0;
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "This task does not exist" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}
/*
щелкунова
19
*/