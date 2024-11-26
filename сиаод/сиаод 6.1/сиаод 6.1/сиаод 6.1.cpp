// сиаод 6.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct tableItem {
    bool taken = false; // занята ли ячейка таблицы
    bool removed = false; // была ли ячейка удалена
    int key = -1; // кдюч (номер счёта)
    string name = "", adress = ""; // имя и адрес клиента
};

class hashTable {
    tableItem* items; // массив строк / ячеек хеш-таблицы
    int m; // размер таблицы
    int n = 0; // занятые ячейки

public:
    // метод добавления элемента в таблицу
    void addItem(int key, string name, string adress) {
        // ищём свободную ячейку методом линейного пробирования
        int probe = key % m;
        while ((this->items)[probe].taken && probe < this->m) probe = (probe + 1) % this->m;
        // осуществляем вставку
        (this->items)[probe].taken = true;
        (this->items)[probe].key = key;
        (this->items)[probe].name = name;
        (this->items)[probe].adress = adress;
        this->n++;
        cout << "элемент добавлен" << endl;
        if (this->n / (float)this->m > 0.7) {
            cout << "требуется увеличение таблицы и рехеширование" << endl;
            this->expandTable();
        }

        
    }

    // метод поиска элемента в таблице по ключу
    tableItem* findItem(int key) {
        // ищем ячейку по ключу
        int probe = key % m;
        int attempts = 0;
        while ((this->items)[probe].key != key && attempts++ < m) probe = (probe + 1) % this->m;
        // если ячейка найдена и не была удалена
        if ((this->items)[probe].key == key && !(this->items)[probe].removed) {
            return &((this->items)[probe]);
        }
        // если ячейка не была найдена или же была удалена
        else {
            return nullptr;
        }

    }

    // метод удаления учейки из таблицы по ключу
    void removeItem(int key) {
        // ищем ячейку по ключу
        int probe = key % m;
        int attempts = 0;
        while ((this->items)[probe].key != key && attempts++ < m) probe = (probe + 1) % this->m;
        // если элемент был найден
        if ((this->items)[probe].key == key && !(this->items)[probe].removed) {
            (this->items)[probe].removed = true;
            cout << "элемент был успешно удален" << endl;
        }
        // если элемент не был найден
        else {
            cout << "элемент не был найден " << endl;
        }
    }

    // метод расширения и рехеширования таблицы
    void expandTable() {
        // создаём временную копию текущей таблицы
        tableItem* itemsCopy = new tableItem[this->m];
        copy(this->items, this->items + this->m, itemsCopy);
        delete[] this->items;
        // расширяем хеш-таблицу в 2 раза
        this->items = new tableItem[2 * this->m];
        this->m *= 2;
        this->n = 0;
        // рехешируем данные
        for (int i = 0; i < this->m / 2; i++) {
            if (!itemsCopy[i].taken || itemsCopy[i].removed) continue;
            this->addItem(itemsCopy[i].key, itemsCopy[i].name, itemsCopy[i].adress);
        }
        
    }

    // метод вывода содержимого таблицы
    void printTable() {
        cout << left << setw(8) << "index" << setw(11) << "key" << setw(40) << "name" << setw(40) << "adress" 
            << setw(8) << "removed" << setw(8) << "taken" << endl;
        for (int i = 0; i < this->m; i++) {
            cout << setw(8) << i << setw(11) << (this->items)[i].key << setw(40) << (this->items)[i].name << 
                setw(40) << (this->items)[i].adress << setw(8) << (this->items)[i].removed << 
                setw(8) << (this->items)[i].taken << endl;
        }
        cout << endl;
    }

    // конструктор
    hashTable (int size) {
        this->m = size;
        this->items = new tableItem[m];
    }
};

hashTable* table = nullptr;

void processCommand(const std::string& command) {
    istringstream iss(command);
    string action;
    iss >> action; // Считываем первое слово (команду)

    if (action == "fill") {
        string subCommand;
        iss >> subCommand; // Считываем подкоманду (randomly или manually)

        if (subCommand == "randomly") {
            int count;
            if (iss >> count) {
                // Вызвать функцию заполнения случайными данными
                string names[20] = {
                    "Иванов Иван Иванович",
                    "Петров Петр Петрович",
                    "Сидоров Сидор Сидорович",
                    "Кузнецов Алексей Николаевич",
                    "Смирнов Андрей Викторович",
                    "Михайлов Михаил Андреевич",
                    "Попов Сергей Сергеевич",
                    "Семенов Семен Семенович",
                    "Васильев Василий Васильевич",
                    "Соловьев Артем Владимирович",
                    "Зайцев Дмитрий Юрьевич",
                    "Лебедев Олег Александрович",
                    "Григорьев Илья Павлович",
                    "Борисов Антон Артемович",
                    "Федоров Арсений Вячеславович",
                    "Александров Игорь Станиславович",
                    "Романов Алексей Павлович",
                    "Николаев Валерий Борисович",
                    "Тихонов Денис Андреевич",
                    "Козлов Николай Ильич"
                };
                string adresses[20] = {
                    "Москва, ул. Тверская, д. 10",
                    "Санкт-Петербург, Невский пр., д. 25",
                    "Екатеринбург, ул. Либкнехта, д. 15",
                    "Новосибирск, ул. Красная, д. 30",
                    "Казань, ул. Баумана, д. 5",
                    "Нижний Новгород, ул. Минина, д. 7",
                    "Челябинск, пр. Победы, д. 20",
                    "Самара, ул. Ленинградская, д. 12",
                    "Уфа, ул. Комсомольская, д. 8",
                    "Ростов-на-Дону, ул. Садовая, д. 50",
                    "Краснодар, ул. Красной, д. 40",
                    "Тюмень, ул. Республики, д. 4",
                    "Тольятти, ул. Гагарина, д. 1",
                    "Ижевск, ул. Удмуртская, д. 24",
                    "Барнаул, пр. Ленина, д. 33",
                    "Воронеж, ул. Карла Маркса, д. 11",
                    "Саратов, ул. Московская, д. 19",
                    "Ярославль, ул. Свободы, д. 3",
                    "Тверь, ул. Советская, д. 18",
                    "Кострома, ул. Ленина, д. 21"
                };
                cout << "Заполнение таблицы " << count << " случайными записями.\n";
                for (int i = 0; i < count; i++) {
                    int randKey = 1'000'000 + rand() % 1'000'000;
                    string randName = names[rand() % 20];
                    string randAdress = adresses[rand() % 20];
                    table->addItem(randKey, randName, randAdress);
                }
            }
            else {
                cout << "Ошибка: не указано количество записей.\n";
            }
        }
        else if (subCommand == "manually") {

            int accountNumber;
            string name, adress;
            if (iss >> accountNumber && iss >> name && iss >> adress) {
                // Вызвать функцию для добавления записи
                cout << "Добавление записи: " << accountNumber << ", " << name << ", " << adress << '\n';
                table->addItem(accountNumber, name, adress);
            }
            else {
                cout << "Ошибка: некорректный ввод для ручного заполнения.\n";
            }
        }
        else {
            cout << "Ошибка: неизвестная подкоманда 'fill'.\n";
        }
    }
    else if (action == "find") {
        int accountNumber;
        if (iss >> accountNumber) {
            // Вызвать функцию для поиска
            cout << "Поиск записи с номером счёта: " << accountNumber << '\n';
            tableItem* target = table->findItem(accountNumber);
            if (target) {
                cout << "Запись была найдена: " << target->name << "; " << target->adress << endl;
            }
            else {
                cout << "Запрашиваемая запись не была найдена" << endl;
            }
        }
        else {
            cout << "Ошибка: не указан номер счёта для поиска.\n";
        }
    }
    else if (action == "remove") {
        int accountNumber;
        if (iss >> accountNumber) {
            // Вызвать функцию для удаления
            cout << "Удаление записи с номером счёта: " << accountNumber << '\n';
            table->removeItem(accountNumber);
        }
        else {
            cout << "Ошибка: не указан номер счёта для удаления.\n";
        }
    }
    else if (action == "print") {
        // Вызвать функцию для вывода содержимого таблицы
        cout << "Вывод содержимого таблицы.\n";
        table->printTable();
    }
    else {
        cout << "Ошибка: неизвестная команда.\n";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string tableSize;
    cout << "Хэш-таблица. Создание таблицы. Введите желаемый размер таблицы: ";
    getline(cin, tableSize);
    
    table = new hashTable(stoi(tableSize));
    cout << "Таблица создана." << endl;
    cout << "Список команд: " << endl << 
        " * fill randomly [число] - внесёт в таблицу [число] случайных записей" << endl << 
        " * fill manually [номер счёта] [ФИО] [адрес] - внесёт одну запись с введённым данными" << endl << 
        " * find [номер счёта] - найдёт в таблице запись с соотв. номером счёта" << endl <<
        " * remove [номер счёта] - удалит в таблице запись с соотв. номером счёта" << endl << 
        " * print - вывод содержимого таблицы на экран" << endl <<
        " * exit - завершение программы" << endl;

    string command;
    while (true) {
        cout << "> ";
        getline(cin, command);
        if (command == "exit") {
            break; // Завершение программы
        }
        processCommand(command);
    }
}