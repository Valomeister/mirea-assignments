#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

void print(string* arr, int arrSize) {
	for (int i = 0; i < arrSize; i++) {
		cout << i + 1 << ". " << arr[i] << endl;
	}
}

// Helper lambda function to print key-value pairs
auto print_key_value = [](const auto& key, const auto& value) {
	cout << "Key:[" << key << "] Value:[" << value << "]\n";
};

void printMap(unordered_map<char, int>& u) {
	for (const pair<const char, int>& n : u)
		print_key_value(n.first, n.second);
}

int findInString(string T, string W) {  // T - исходный текст, W - образец
	unordered_map<char, int> skip{};
	skip[W.back()] = W.length();
	for (int i = 0; i < W.length() - 1; i++) {
		skip[W[i]] = W.length() - i - 1;
	}
	int indx = 0;
	while (indx + W.length() <= T.length()) {
		bool found = true;
		for (int i = 0; i < W.length(); i++) {
			if (T[indx + W.length() - i - 1] != W[W.length() - i - 1]) {
				if (skip[T[indx + W.length() - i - 1]] == 0) {
					indx += W.length();
				}
				else {
					indx += skip[T[indx + W.length() - i - 1]];
				}
				found = false;
				break;
			}
		}
		if (found) break;

	}
	if (indx + W.length() > T.length()) return -1;
	return indx;
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << findInString("fИва никин", "Ива никин");




	return 0;
}