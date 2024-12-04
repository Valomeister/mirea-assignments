#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <thread>

using namespace std;

// Структура для записи налогоплательщика
struct Taxpayer {
    char inn[11];      // ИНН (10 символов + '\0')
    char surname[21];  // Фамилия (20 символов + '\0')
    char phone[16];    // Телефон (15 символов + '\0')
};

// Линейный поиск по бинарному файлу
bool linearSearch(const string& binaryFilename, const string& targetINN, Taxpayer& foundRecord) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть файл: " << binaryFilename << endl;
        return false;
    }

    Taxpayer record;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(Taxpayer))) {
        if (targetINN == record.inn) { // Сравниваем ИНН
            foundRecord = record;
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false; // Запись с указанным ключом не найдена
}

// Измерение времени выполнения поиска
void evaluateSearchPerformance(const string& binaryFilename, const string& targetINN) {
    Taxpayer foundRecord;

    auto start = chrono::high_resolution_clock::now();
    bool found = linearSearch(binaryFilename, targetINN, foundRecord);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    if (found) {
        cout << "Запись найдена: ИНН: " << foundRecord.inn
            << ", Фамилия: " << foundRecord.surname
            << ", Телефон: " << foundRecord.phone << endl;
    }
    else {
        cout << "Запись с ИНН " << targetINN << " не найдена." << endl;
    }

    cout << "Время поиска: " << elapsed.count() << " секунд.\n";
}

// Генерация случайного 10-значного ИНН
string generateINN(set<string>& usedINNs) {
    string inn;
    do {
        inn = to_string(rand() * rand() % 9000000000 + 1000000000); // 10-значное число
    } while (usedINNs.find(inn) != usedINNs.end());
    usedINNs.insert(inn);
    return inn;
}

// Генерация случайного телефона
string generatePhone() {
    return "+7" + to_string((rand() * rand()) % 9000000000 + 1000000000); // Формат: +7XXXXXXXXXX
}

// Генерация текстового файла
void generateTextFile(const string& filename, int count) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    set<string> usedINNs; // Для уникальных ИНН
    vector<string> surnames = { "Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов" };

    for (int i = 0; i < count; ++i) {
        string inn = generateINN(usedINNs);
        string surname = surnames[rand() % surnames.size()];
        string phone = generatePhone();

        outFile << inn << " " << surname << " " << phone << endl;
    }

    outFile.close();
    cout << "Текстовый файл успешно создан: " << filename << endl;
}

// Преобразование текстового файла в двоичный
void convertToBinary(const string& textFilename, const string& binaryFilename) {
    ifstream inFile(textFilename);
    if (!inFile) {
        cerr << "Не удалось открыть текстовый файл: " << textFilename << endl;
        return;
    }

    ofstream outFile(binaryFilename, ios::binary);
    if (!outFile) {
        cerr << "Не удалось открыть двоичный файл: " << binaryFilename << endl;
        return;
    }

    string inn, surname, phone;
    while (inFile >> inn >> surname >> phone) {
        Taxpayer record;

        // Заполняем структуру
        strncpy_s(record.inn, sizeof(record.inn), inn.c_str(), _TRUNCATE);
        record.inn[10] = '\0'; // Завершающий символ

        strncpy_s(record.surname, sizeof(record.inn), surname.c_str(), _TRUNCATE);
        record.surname[20] = '\0'; // Завершающий символ

        strncpy_s(record.phone, sizeof(record.inn), phone.c_str(), _TRUNCATE);
        record.phone[15] = '\0'; // Завершающий символ

        // Запись структуры в файл
        outFile.write(reinterpret_cast<const char*>(&record), sizeof(Taxpayer));
    }

    inFile.close();
    outFile.close();
    cout << "Двоичный файл успешно создан: " << binaryFilename << endl;
}

// Чтение двоичного файла (для проверки)
void readBinaryFile(const string& binaryFilename) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть двоичный файл: " << binaryFilename << endl;
        return;
    }

    Taxpayer record;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(Taxpayer))) {
        cout << "ИНН: " << record.inn
            << ", Фамилия: " << record.surname
            << ", Телефон: " << record.phone << endl;
    }

    inFile.close();
}


struct IndexEntry {
    string inn;  // Ключ
    streampos offset;  // Смещение записи в файле
};

vector<IndexEntry> buildIndexTable(const string& binaryFilename) {
    vector<IndexEntry> indexTable;
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть файл" << endl;
        return indexTable;
    }

    Taxpayer record;
    streampos offset = 0;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(Taxpayer))) {
        IndexEntry entry;
        entry.inn = record.inn;
        entry.offset = offset;
        indexTable.push_back(entry);
        offset = inFile.tellg();
    }

    inFile.close();
    sort(indexTable.begin(), indexTable.end(), [](const IndexEntry& a, const IndexEntry& b) {
        return a.inn < b.inn;
        });
    
    return indexTable;
}


streampos interpolationSearch(const vector<IndexEntry>& indexTable, const string& targetINN) {
    int low = 0;
    int high = indexTable.size() - 1;

    while (low <= high && targetINN >= indexTable[low].inn && targetINN <= indexTable[high].inn) {
        int pos = low + (float)(stoi(targetINN) - stoi(indexTable[low].inn)) * (high - low) /
            (stoi(indexTable[high].inn) - stoi(indexTable[low].inn));

        if (indexTable[pos].inn == targetINN) {
            return indexTable[pos].offset;
        }

        if (indexTable[pos].inn < targetINN) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }

    return -1;  // Если не найдено
}

Taxpayer readRecord(const string& binaryFilename, streampos offset) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть файл" << endl;
        return Taxpayer();  // Возвращаем пустую структуру
    }

    Taxpayer record;
    inFile.seekg(offset);
    inFile.read(reinterpret_cast<char*>(&record), sizeof(Taxpayer));

    inFile.close();
    return record;
}

void evaluateSearchPerformanceWithIndex(const string& binaryFilename, const string& targetINN) {
    // Строим таблицу индексов
    vector<IndexEntry> indexTable = buildIndexTable(binaryFilename);
    
    auto start = chrono::high_resolution_clock::now();

    // Выполняем интерполяционный поиск
    streampos offset = interpolationSearch(indexTable, targetINN);

    if (offset != -1) {
        // Если найдено, считываем запись
        Taxpayer foundRecord = readRecord(binaryFilename, offset);
        cout << "Запись найдена: ИНН: " << foundRecord.inn << ", Фамилия: " << foundRecord.surname
            << ", Телефон: " << foundRecord.phone << endl;
    }
    else {
        cout << "Запись с ИНН " << targetINN << " не найдена." << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Время поиска: " << elapsed.count() << " секунд." << endl;
}



int main() {
    setlocale(LC_ALL, "Russian");

    /*
    srand(time(nullptr));

    string textFilename = "taxpayers.txt";
    string binaryFilename = "taxpayers.bin";

    // Шаг 1. Генерация текстового файла
    generateTextFile(textFilename, 100);

    // Шаг 2. Преобразование текстового файла в двоичный
    convertToBinary(textFilename, binaryFilename);

    // Шаг 3. Чтение двоичного файла для проверки
    readBinaryFile(binaryFilename);
    */




    /*
    // Создание тестовых файлов
    generateTextFile("taxpayers_100.txt", 100);
    convertToBinary("taxpayers_100.txt", "taxpayers_100.bin");
    generateTextFile("taxpayers_1000.txt", 1000);
    convertToBinary("taxpayers_1000.txt", "taxpayers_1000.bin");
    generateTextFile("taxpayers_10000.txt", 10000);
    convertToBinary("taxpayers_10000.txt", "taxpayers_10000.bin");

    // Указание целевого ИНН для поиска
    string targetINN = "1234567890";

    // Поиск в файле на 100 записей
    cout << "\n=== Поиск в файле на 100 записей ===\n";
    evaluateSearchPerformance("taxpayers_100.bin", targetINN);

    // Поиск в файле на 1000 записей
    cout << "\n=== Поиск в файле на 1000 записей ===\n";
    evaluateSearchPerformance("taxpayers_1000.bin", targetINN);

    // Поиск в файле на 10,000 записей
    cout << "\n=== Поиск в файле на 10,000 записей ===\n";
    evaluateSearchPerformance("taxpayers_10000.bin", targetINN);
    */

    generateTextFile("taxpayers_100.txt", 100);
    convertToBinary("taxpayers_100.txt", "taxpayers_100.bin");
    generateTextFile("taxpayers_1000.txt", 1000);
    convertToBinary("taxpayers_1000.txt", "taxpayers_1000.bin");
    generateTextFile("taxpayers_10000.txt", 1000);
    convertToBinary("taxpayers_10000.txt", "taxpayers_10000.bin");
    cout << "Оценивание скорости интерполяционного поиска для файла из " << 100 << " записей" << endl;
    evaluateSearchPerformanceWithIndex("taxpayers_100.bin", "1234567890");
    cout << "Оценивание скорости интерполяционного поиска для файла из " << 1000 << " записей" << endl;
    evaluateSearchPerformanceWithIndex("taxpayers_1000.bin", "1234567890");
    cout << "Оценивание скорости интерполяционного поиска для файла из " << 10000 << " записей" << endl;
    evaluateSearchPerformanceWithIndex("taxpayers_10000.bin", "1234567890");


    return 0;
}
