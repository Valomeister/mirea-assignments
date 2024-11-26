#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <bitset>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

void task1a() {
	// 1.а \\ 
	unsigned char x, maska = 1;
	x = 255; // 11111111
	cout << "Начальное значение х: " << (int)x;
	x = x & (~(maska << 4)); 
	cout << ", х после применения маски: " << (int)x << endl;
	x = 132; // 10000100
	cout << "Начальное значение х: " << (int)x;
	x = x & (~(maska << 4));
	cout << ", х после применения маски: " << (int)x << endl;
}

void task1b() {
	// 1.б \\ 
	unsigned char x, maska = 1;
	x = 255; // 11111111
	cout << "Начальное значение х: " << (int)x;
	x = x | (maska << 6);
	cout << ", х после применения маски: " << (int)x << endl;
	x = 132; // 10000100
	cout << "Начальное значение х: " << (int)x;
	x = x | (maska << 6);
	cout << ", х после применения маски: " << (int)x << endl;
}

void task1c() {
	// 1.c \\ 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned int x = 25;
	const int n = sizeof(int) * 8; // 32 - количество разрядов в числе типа int
	unsigned int maska = (1 << (n - 1)); // 1 в старшем бите 32-разрядной сетки

	cout << "Начальный вид маски: " << bitset<32>(maska) << endl;
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) { // 32 раза - по количеству разрядов
		cout << ((x & maska) >> (n - i));
		maska = maska >> 1; // смещение 1 в маске на разряд вправо
	}

	cout << endl;
	system("pause");
}

void printVector(vector<int>& nums) {
	for (auto x : nums) {
		cout << x << " ";
	}
	cout << endl;
}

vector<int> bitSort8(vector<int>& nums) {
	unsigned char bitSet = 0;
	for (auto x : nums) {
		bitSet = bitSet | (1 << x);
	}
	vector<int> sortedNums;
	cout << "BitSet = ";
	for (int i = 0; i < 8; i++) {
		if (bitSet & (1 << i)) sortedNums.push_back(i);
		cout << ((bitSet & (1 << i)) >> (i));
	}
	cout << endl;
	return sortedNums;
}

vector<int> bitSort64ULL(vector<int>& nums) {
	unsigned long long bitSet = 0;
	for (auto x : nums) {
		bitSet = bitSet | (1ULL << x);
	}
	vector<int> sortedNums;
	cout << "BitSet = ";
	for (int i = 0; i < 64; i++) {
		if (bitSet & (1ULL << i)) sortedNums.push_back(i);
		cout << ((bitSet & (1ULL << i)) >> (i));
	}
	cout << endl;
	return sortedNums;
}

vector<int> bitSort64UC(vector<int>& nums) {
	unsigned char* bitSet = new unsigned char[8] {};
	for (auto x : nums) {
		bitSet[7 - x / 8] = bitSet[7 - x / 8] | (1 << (x % 8));
	}
	vector<int> sortedNums;
	cout << "BitSet = | ";
	for (int i = 0; i < 64; i++) {
		
		if (bitSet[7 - i / 8] & (1 << (i % 8))) sortedNums.push_back(i);
		cout << ((bitSet[7 - i / 8] & (1 << (i % 8))) >> (i % 8));
		if ((i + 1) % 8 == 0) cout << " | ";
	}
	cout << endl;
	return sortedNums;
}

void bitSortFile(const string& sourceFileName, const string& destinationFileName, double& timeSpent, int& memoryUsed) {
	const int MAX_NUMBER = 10'000'000;
	const int ARR_SIZE = (MAX_NUMBER + 1) / 8 + 1;

	vector<unsigned char> bitSet(ARR_SIZE, 0);
	memoryUsed = bitSet.capacity() * sizeof(unsigned char);

	ifstream inFile(sourceFileName); 
	if (!inFile) { 
		cerr << "Не удалось открыть файл для чтения: " << sourceFileName << endl;
		return;
	}

	int num;
	while (inFile >> num) {
		bitSet[ARR_SIZE - num / 8 - 1] = bitSet[ARR_SIZE - num / 8 - 1] | (1 << (num % 8));
	}
	inFile.close();
	
	ofstream outFile(destinationFileName); 
	if (!outFile) {
		cerr << "Не удалось открыть файл для записи: " << destinationFileName << endl;
		return;
	}
	auto start = chrono::high_resolution_clock::now();
	for (int charByte = 0; charByte < ARR_SIZE; charByte++) {
		for (int charBit = 0; charBit < 8; charBit++) {
			if (bitSet[ARR_SIZE - charByte - 1] & (1 << (charBit))) {
				outFile << charByte * 8 + charBit << endl;
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;
	timeSpent = elapsed.count();
	
	outFile.close();
		
}

void generateRandomNumbersToFile(const string& filename, int amount) {
	ofstream outFile(filename);
	if (!outFile) { 
		cerr << "Не удалось открыть файл для записи: " << filename << endl;
		return;
	}

	vector<int> numbers(amount);
	for (int i = 0; i < amount; i++) {
		numbers[i] = i;
	}

	random_device rd;
	mt19937 gen(rd());
	shuffle(numbers.begin(), numbers.end(), gen);

	for (int i = 0; i < amount; ++i) {
		outFile << numbers[i] << endl;
	}

	outFile.close(); 
}

void task2a() {
	int inputSize;
	cout << "Сколько чисел вы хотите ввести? (до 8): ";
	cin >> inputSize;
	vector<int> nums(inputSize);
	cout << "Введите сами числа: ";
	for (int i = 0; i < inputSize; i++) {
		cin >> nums[i];
	}
	cout << "Исходный массив: ";
	printVector(nums);
	vector<int> sortedNums = bitSort8(nums);
	cout << "Отсортированный массив: ";
	printVector(sortedNums);
}

void task2b() {
	int inputSize;
	cout << "Сколько чисел вы хотите ввести? (до 64): ";
	cin >> inputSize;
	vector<int> nums(inputSize);
	cout << "Введите сами числа: ";
	for (int i = 0; i < inputSize; i++) {
		cin >> nums[i];
	}
	cout << "Исходный массив: ";
	printVector(nums);
	vector<int> sortedNums = bitSort64ULL(nums);
	cout << "Отсортированный массив: ";
	printVector(sortedNums);
}

void task2c() {
	int inputSize;
	cout << "Сколько чисел вы хотите ввести? (до 64): ";
	cin >> inputSize;
	vector<int> nums(inputSize);
	cout << "Введите сами числа: ";
	for (int i = 0; i < inputSize; i++) {
		cin >> nums[i];
	}
	cout << "Исходный массив: ";
	printVector(nums);
	vector<int> sortedNums = bitSort64UC(nums);
	cout << "Отсортированный массив: ";
	printVector(sortedNums);
}


void task3() {
	generateRandomNumbersToFile("numbers_unsorted.txt", 5'000'000);
	double timeSpent;
	int memoryUsed;
	bitSortFile("numbers_unsorted.txt", "numbers_sorted.txt", timeSpent, memoryUsed);
	cout << "Время работы: " << timeSpent << " сек" << endl;
	cout << "Использовано места: " << memoryUsed << " байт" << endl;
}



int main(){
	setlocale(LC_ALL, "Russian");

	task2a();
	
	return 0;
}