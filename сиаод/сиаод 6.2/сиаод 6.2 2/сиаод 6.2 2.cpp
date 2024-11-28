#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

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

// алгоритм Бойера-Мура-Хорспула.
int findInString(string T, string W) {  // T - исходный текст, W - образец
	// хеш-таблица сдвигов
	unordered_map<char, int> skip{};
	// заполняем хеш-таблицу
	skip[W.back()] = W.length();
	for (int i = 0; i < W.length() - 1; i++) {
		skip[W[i]] = W.length() - i - 1;
	}
	// индекс поиска
	int indx = 0;
	// пока поиск не вышел за границы текста
	while (indx + W.length() <= T.length()) {
		// флаг
		bool found = true;
		// перебираем символы в образце
		for (int i = 0; i < W.length(); i++) {
			// справа налево проверяем совпадение с текстом
			if (T[indx + W.length() - i - 1] != W[W.length() - i - 1]) {
				// если не совпадает символ. которого нет в хеш-таблице
				if (skip[T[indx + W.length() - i - 1]] == 0) {
					// значит этого символа в принципе нет в образце W 
					// и можно делать сдвиг поиска на всю длину образца
					indx += W.length();
				}
				// если не совпадает символ. котороый есть в хеш-таблице
				else {
					// то сдвигаем на соответствующую велчину
					indx += skip[T[indx + W.length() - i - 1]];
				}
				// обновляем флаг
				found = false;
				break;
			}
		}
		// нашли первое вхождение?
		if (found) break;

	}
	// Если поиск вышел за пределы текста, возвращаем -1 (образец не был найден в тексте)
	if (indx + W.length() > T.length()) return -1;
	// Иначе поиск был успешен. Возвращаем индекс поиска
	return indx;
}

void findInStringTest(string T, string W) {  // T - исходный текст, W - образец
	int comps = 0;
	unordered_map<char, int> skip{};
	skip[W.back()] = W.length();
	for (int i = 0; i < W.length() - 1; i++) {
		skip[W[i]] = W.length() - i - 1;
		comps++;
	}; comps++;
	int indx = 0;
	while (indx + W.length() <= T.length()) {
		comps++;
		bool found = true;
		for (int i = 0; i < W.length(); i++) {
			comps++;
			if (T[indx + W.length() - i - 1] != W[W.length() - i - 1]) {

				if (skip[T[indx + W.length() - i - 1]] == 0) {
					indx += W.length();
				}
				else {
					indx += skip[T[indx + W.length() - i - 1]];
				}; comps++;
				found = false;
				break;
			}; comps++;
		}; comps++;
		comps++;
		if (found) break;


	}; comps++;
	comps++;
	cout << " - В Тексте T: - " << endl << T << endl << " - Был поиск образца W: - " << endl << W << endl;
	if (indx + W.length() > T.length()) {
		cout << "Поиск безуспешный, W не входит в T" << endl;
	}
	else {
		cout << "Поиск безуспешный, W входит в T начиная с индекса " << indx << endl;
	}
	cout << "Количество сравнений = " << comps << endl;
	cout << "Размер текста T = " << T.length() << endl;
	cout << "Размер образца W = " << W.length() << endl;

}

// Функция поиска колиества вхождений W в T
int countOccurances(string T, string W) {
	// Счётчик
	int count = 0;
	// Индекс поиска
	int searchStart = 0;
	// Если в оставшемся куске текста ещё есть вхождения
	while (findInString(T.substr(searchStart), W) != -1) {
		// обновляем счётчик
		count++;
		// обновляем индекс поиска
		searchStart += findInString(T.substr(searchStart), W) + 1;
	}
	// возвращаем результат
	return count;
}

void readKeywordsFromFile(const string& filename, vector<string>& keywords) {
	ifstream file(filename); // Открытие файла
	if (!file) { // Проверка на успешное открытие файла
		cerr << "Ошибка при открытии файла!" << endl;
		return;
	}

	string word;
	// Чтение слов из файла
	while (file >> word) {
		keywords.push_back(word); // Добавление слова в вектор
	}

	file.close(); // Закрытие файла
}

void bubbleSortKeywords(vector<string>& keywords) {
	int n = keywords.size();
	// Внешний цикл по всем элементам
	for (int i = 0; i < n - 1; ++i) {
		// Внутренний цикл для сравнения соседних элементов
		for (int j = 0; j < n - i - 1; ++j) {
			// Если текущий элемент больше следующего, меняем их местами
			if (keywords[j] > keywords[j + 1]) {
				swap(keywords[j], keywords[j + 1]);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");

	// Открытие файла для чтения
	ifstream inputFile("oblomov.txt"); // Укажите путь к вашему файлу

	if (!inputFile) {
		cout << "Ошибка при открытии файла!" << endl;
		return 1;
	}

	string oblomovParagraph;

	// Считывание одной длинной строки
	getline(inputFile, oblomovParagraph); // Считывает всю строку, включая пробелы

	// Закрытие файла
	inputFile.close();

	// Количество вхождений
	if (1) {
		// Выводим считанную строку
		cout << " - Образец текста: -  " << endl << oblomovParagraph << endl << endl;;

		vector<string> targets{ "без", "шире", "все", ",", "сиаод" };
		for (auto target : targets) {
			cout << "- Подстрока '" << target << "' входит в отрывок " << countOccurances(oblomovParagraph, target) << " раз(a)." << endl;
		}
	}

	// Нахождение образца в строке
	if (0) {
		findInStringTest(oblomovParagraph, "халат");
		cout << endl;
		findInStringTest(oblomovParagraph, "мирэа");
		cout << endl;
		findInStringTest("Поиск строки формально определяется следующим образом.", "предел");
		cout << endl;
		findInStringTest("Поиск строки формально определяется следующим образом.", "космос");
	}

	// сортировка ключевых слов
	if (0) {
		vector<string> keywords; // Вектор для хранения ключевых слов

		readKeywordsFromFile("keywords-css.txt", keywords);

		bubbleSortKeywords(keywords);

		// Вывод отсортированных ключевых слов
		int count = 1;
		cout << "Перемешанные ключевые слова: " << endl;
		for (const auto& kw : keywords) {
			cout << count++ << ") " << kw << endl;
		}
	}

	return 0;
}