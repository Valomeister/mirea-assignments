function truncate(str, maxlength) {
    // Проверяем, требуется ли усечение
    if (str.length > maxlength) {
        // Укорачиваем строку и добавляем "…"
        return str.slice(0, maxlength - 3) + '…';
   }
    // Возвращаем исходную строку, если усечение не требуется
    return str;
}

// Примеры использования
console.log(truncate('Пример строки, которая слишком длинная', 20)); // "Пример строки, кото…"
console.log(truncate('Короткая строка', 5)); // "Короткая строка"

let p = document.getElementById('footer-about-txt');
// p.textContent = truncate(p.textContent, 400);