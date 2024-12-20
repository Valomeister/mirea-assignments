
# Практическое занятие №1

## Задача 1

### Постановка задачи

Вывести отсортированный в алфавитном порядке 
список имен пользователей в файле passwd 
(вам понадобится grep).

### Решение

Имена пользователей находятся в файле /etc/passwd. 
Данные разделены двоеточием, а само имя пользователя 
находится в самом начале строки.

```bash
awk -F: '{print $1}' /etc/passwd
```

Если нужно проигнорировать псевдопользователей, 
то оставляем только пользователей с UID >= 1000 и UID == 0 (root)

```bash
awk -F: '$3 >= 1000 || $3 == 0 {print $1}' /etc/passwd
```

## Задача 2

### Постановка задачи

Вывести данные /etc/protocols в отформатированном и 
отсортированном порядке для 5 наибольших портов, как 
показано в примере ниже:

```
[root@localhost etc]# cat /etc/protocols ...
142 rohc
141 wesp
140 shim6
139 hip
138 manet
```

### Решение

Получим данные о сетевых протоколах при помощи cat, 
отсортируем в обратном порядке по 2-му столбцу, 
возьмем первые 5 строк и через awk выведем сначала 
2й столбец, а затем 1й, в соответствии с требуемым 
форматированием.

```bash
cat /etc/protocols | sort -n -k 2 -r | head -n 5 | awk '{print $2, $1}'
```

## Задача 3

### Постановка задачи

Написать программу banner средствами bash для вывода 
текстов, как в следующем примере (размер баннера должен 
меняться!):

```
[root@localhost ~]# ./banner "Hello from RTU MIREA!"  
+-----------------------+  
| Hello from RTU MIREA! |  
+-----------------------+  
```

Перед отправкой решения проверьте его в ShellCheck на предупреждения.

### Решение

Создадим файл banner.sh в домашней директории и 
откроем его в редакторе при помощи nano.

```bash
nano banner.sh
```

Затем напишем на bash сам скрипт

```bash
#!/bin/bash

# Проверяем, что текст передан в качестве аргумента
if [ -z "$1" ]; then
  echo "Usage: $0 <text>"
  exit 1
fi

# Сохраняем текст в переменную
text="$1"

# Вычисляем длину текста
text_length=${#text}

# Строим рамку: добавляем 2 символа для отступов по бокам
border_length=$((text_length + 2))

# Печатаем верхнюю рамку
echo "+$(head -c $border_length < /dev/zero | tr '\0' '-')+"

# Печатаем строку с текстом
echo "| $text |"

# Печатаем нижнюю рамку
echo "+$(head -c $border_length < /dev/zero | tr '\0' '-')+"
```

Далее сделаем файл banner.sh исполнимым и протетсируем его работу

```bash
chmod +x banner.sh
./banner.sh
```

## Задача 4

### Постановка задачи

Написать программу для вывода всех идентификаторов 
(по правилам C/C++ или Java) в файле (без повторений).

Пример для hello.c:

```
h hello include int main n printf return stdio void world
```

### Решение

Идентификаторы начинаются с буквы любого регистра или "_", 
а за которыми следуют такие же символы либо цифры

При помощи grep, учитывая правила идентификатором, 
выбираем нужные части текста, сортируем и удаляем 
дубликаты, затем используем paste для вывода в одну 
строку (grep обычно разбивает вывод на множество строк)

```bash
grep -o '\b[a-zA-Z_][a-zA-Z0-9_]*\b' hello.c | sort | uniq | paste -s -d ' ' -
```

## Задача 6

### Постановка задачи

Написать программу для проверки наличия комментария 
в первой строке файлов с расширением c, js и py.

### Решение

При помощи nano создаем и открываем файл checkcomment.sh

```bash
nano checkcomment.sh
```

В редакторе пишем саму программу, которая имеет следующий вид:

```bash
#!/bin/bash

# Проверка, что файл передан в качестве аргумента
if [ -z "$1" ]; then
    echo "Ошибка: укажите имя файла."
    exit 1
fi

# Проверка, что файл существует
if [ ! -f "$1" ]; then
    echo "Ошибка: файл '$1' не найден."
    exit 1
fi

# Получаем расширение файла
extension="${1##*.}"

# Чтение первой строки файла
first_line=$(head -n 1 "$1")

# Проверка по расширению файла
case "$extension" in
    c|cpp)
        # Для файлов C/C++ проверяем комментарий в первой строке
        if [[ "$first_line" =~ ^[[:space:]]*// || "$first_line" =~ ^[[:space:]]*/\* ]]; then
            echo "Комментарий найден в первой строке файла '$1'."
        else
            echo "Комментарий отсутствует в первой строке файла '$1'."
        fi
        ;;
    js)
        # Для файлов JavaScript проверяем комментарий в первой строке
        if [[ "$first_line" =~ ^[[:space:]]*// || "$first_line" =~ ^[[:space:]]*/\* ]]; then
            echo "Комментарий найден в первой строке файла '$1'."
        else
            echo "Комментарий отсутствует в первой строке файла '$1'."
        fi
        ;;
    py)
        # Для файлов Python проверяем комментарий в первой строке
        if [[ "$first_line" =~ ^[[:space:]]*# ]]; then
            echo "Комментарий найден в первой строке файла '$1'."
        else
            echo "Комментарий отсутствует в первой строке файла '$1'."
        fi
        ;;
    *)
        echo "Ошибка: неподдерживаемое расширение файла '$extension'. Поддерживаются только .c, .js и .py."
        exit 1
        ;;
esac
```

Выходим из редактора, делаем файл .sh исполнимым и создаем тестируем программу на разных файлах.
```bash
chmod +x checkcomment.sh
echo "print(52)" > test1.py
echo "#comment" > test2.py
echo "cout << 52 << endl;" > test1.c
echo "//comment" > test2.c
./checkcomment.sh test1.py
./checkcomment.sh test2.py
./checkcomment.sh test1.c
./checkcomment.sh test2.c
```