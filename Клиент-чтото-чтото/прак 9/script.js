"use strict"

const button = document.getElementById("register");

function doRegistration() {
    let login = prompt("Введите ваш логин:");

    if (login === "Админ") {
    let password = prompt("Введите ваш пароль:");

    if (password === "Я главный") {
        alert("Здравствуйте!");
    } else if (password === "" || password === null) {
        alert("Отменено");
    } else {
        alert("Неверный пароль");
    }
    } else if (login === "" || login === null) {
    alert("Отменено");
    } else {
    alert("Я вас не знаю");
}
}

// Добавляем обработчик события нажатия
button.addEventListener("click", function() {
    let willing = prompt("Желаете пройти регистрацию на сайте?");
    if (willing === "Да" ) {
        alert("Круто!")
        doRegistration()
    } else {
        alert("Попробуй ещё раз")
    }
});




const likeButton = document.getElementById("likeButton");
const likeIcon = document.getElementById("likeIcon");
const likeCount = document.getElementById("likeCount");

let liked = false;
let count = 1;

likeButton.addEventListener("click", () => {
  liked = !liked;

  if (liked) {
    likeButton.classList.add("liked");
    likeIcon.textContent = "❤️";
    likeCount.textContent = ++count;
  } else {
    likeButton.classList.remove("liked");
    likeIcon.textContent = "♡";
    likeCount.textContent = --count;
  }
});



// Режим рисования
const drawButton = document.getElementById("drawButton");
let isDrawing = false;

drawButton.addEventListener("click", () => {
  isDrawing = !isDrawing;
  drawButton.classList.toggle("active");
  drawButton.textContent = isDrawing ? "Отключить рисование" : "Включить рисование";
});

document.addEventListener("mousemove", (event) => {
  if (isDrawing) {
    const dot = document.createElement("div");
    dot.className = "dot";
    dot.style.left = `${event.pageX}px`;
    dot.style.top = `${event.pageY}px`;
    document.body.appendChild(dot);

    // Удаляем точки через 3 секунды для предотвращения переполнения
    setTimeout(() => {
      dot.remove();
    }, 3000);
  }
});