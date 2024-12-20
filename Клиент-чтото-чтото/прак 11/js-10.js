const captchaContainer = document.getElementById("captchaContainer");
const captchaInput = document.getElementById("captchaInput");
const submitCapchaButton = document.getElementById("submitCapchaButton");
const submitButton = document.getElementById("submitButton");
const errorMessage = document.getElementById("errorMessage");

let captchaValue;
let isNumberCaptcha = false;

// Функция проверки пустого ввода
function isEmpty(value) {
  return value.trim() === "";
}

// Генерация капчи с буквами
function generateLetterCaptcha() {
  const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  captchaValue = Array.from({ length: 5 }, () =>
    chars.charAt(Math.floor(Math.random() * chars.length))
  ).join("");
  captchaContainer.textContent = `Введите: ${captchaValue}`;
  isNumberCaptcha = false;
}

// Генерация капчи с числами
function generateNumberCaptcha() {
    console.log("generating new captcha");
  const num1 = Math.floor(Math.random() * 10) + 1;
  const num2 = Math.floor(Math.random() * 10) + 1;
  captchaValue = num1 + num2;
  captchaContainer.textContent = `Решите пример: ${num1} + ${num2}`;
  isNumberCaptcha = true;
}

// Проверка капчи
function validateCaptcha() {
  const userInput = captchaInput.value;

  if (isEmpty(userInput)) {
    errorMessage.textContent = "Ошибка: ввод не может быть пустым!";
    errorMessage.style.display = "block";
    return -1;
  }

  if (isNumberCaptcha) {
    if (parseInt(userInput, 10) === captchaValue) {
      errorMessage.style.display = "none";
      submitButton.disabled = false;
      return 1;
    }
  } else {
    if (userInput === captchaValue) {
      errorMessage.style.display = "none";
      submitButton.disabled = false;
      return 2;
    }
  }

  errorMessage.textContent = "Ошибка: неправильный ввод!";
  errorMessage.style.display = "block";
  submitButton.disabled = true;
  return 0;
}

// Генерация первой капчи
generateLetterCaptcha();

// Обработчики событий
submitCapchaButton.addEventListener("click", () => {
    let captchaResult = validateCaptcha();
    if (captchaResult == 0) {
        generateNumberCaptcha(); // Переход к числовой капче при ошибке
    }
});










function Accumulator(startingValue) {
  // Инициализируем свойство value с начальным значением
  this.value = startingValue;

  // Метод для считывания нового числа и добавления его к value
  this.read = function() {
      // Читаем новое число через prompt
      let input = prompt("Введите число: ");
      
      // Преобразуем введённое значение в число
      let number = Number(input);
      
      // Проверяем, является ли введённое значение числом
      if (!isNaN(number)) {
          // Если это число, добавляем его к текущему значению
          this.value += number;
      } else {
          alert("Это не число. Пожалуйста, введите корректное значение.");
      }
  };
}

// Пример использования:

// Создаем экземпляр Accumulator с начальным значением 10
let accumulator = new Accumulator(10);

// Проводим несколько операций с методом read
accumulator.read();  // Пользователь вводит число
accumulator.read();  // Второй ввод

// Выводим текущее значение
console.log(accumulator.value);  // Выводит общее значение