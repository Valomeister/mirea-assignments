"use strict"

let lessButtons = document.querySelectorAll('.button_less');
let moreButtons = document.querySelectorAll('.button_more');
lessButtons.forEach(button => {
    button.addEventListener('click', () => {
        let itemCount = button.parentElement.querySelector('#itemCount');
        let raw = itemCount.textContent;
        let match = raw.match(/^\d+/); // Ищем число в начале строки
        let count = match ? parseInt(match[0], 10) : null;
        itemCount.textContent = --count + " шт.";
    });
  });

moreButtons.forEach(button => {
    button.addEventListener('click', () => {
        let itemCount = button.parentElement.querySelector('#itemCount');
        let raw = itemCount.textContent;
        let match = raw.match(/^\d+/); // Ищем число в начале строки
        let count = match ? parseInt(match[0], 10) : null;
        itemCount.textContent = ++count + " шт.";
    });
  });

// const lessButton = document.getElementById("lessButton");
// const moreButton = document.getElementById("moreButton");
// const itemCount = document.getElementById("itemCount");

// let raw = itemCount.textContent;
// let match = raw.match(/^\d+/); // Ищем число в начале строки
// let count = match ? parseInt(match[0], 10) : null;

// lessButton.addEventListener("click", () => {
//     itemCount.textContent = --count + " шт.";
// });

// moreButton.addEventListener("click", () => {
//     itemCount.textContent = ++count + " шт.";
// });