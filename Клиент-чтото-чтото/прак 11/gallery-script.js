"use strict"

let cartCount = {
  "Солнце": 0,
  "Венера": 0,
  "Земля": 0, 
  "Марс": 0,
  "Юпитер": 0,
  "Сатурн": 0,
  "Пояс астероидов": 0,
  "Уран": 0,
  }

  let cartPrice = {
    "Солнце": 15,
    "Венера": 5,
    "Земля": 8, 
    "Марс": 7,
    "Юпитер": 13,
    "Сатурн": 11,
    "Пояс астероидов": 8,
    "Уран": 10,
    }

let lessButtons = document.querySelectorAll('.button_less');
let moreButtons = document.querySelectorAll('.button_more');
lessButtons.forEach(button => {
    button.addEventListener('click', () => {
        let thisCartItem = button.parentElement.parentElement.parentElement;
        let descriptionText = thisCartItem.querySelector('.cart_item_description_text').textContent;
        const indexOfDot = descriptionText.indexOf('.');
        let itemName = descriptionText.substring(0, indexOfDot);
        let itemCount = thisCartItem.querySelector('#itemCount');
        itemCount.textContent = --cartCount[itemName] + " шт.";
        let sumPrice = document.getElementById('amount');
        sumPrice.textContent = +sumPrice.textContent - cartPrice[itemName];

        if (cartCount[itemName] == 0) {
          thisCartItem.style.display = "none";
        }
        if (cartCount[itemName] == 1) {
          let removeIcon = thisCartItem.querySelector('.button_less .remove');
          let minusIcon = thisCartItem.querySelector('.button_less .minus');
          removeIcon.style.display = "inline";
          minusIcon.style.display = "none";
        }
    });
  });

moreButtons.forEach(button => {
    button.addEventListener('click', () => {
      let thisCartItem = button.parentElement.parentElement.parentElement;
      let descriptionText = thisCartItem.querySelector('.cart_item_description_text').textContent;
      const indexOfDot = descriptionText.indexOf('.');
      let itemName = descriptionText.substring(0, indexOfDot);
      let itemCount = thisCartItem.querySelector('#itemCount');
      itemCount.textContent = ++cartCount[itemName] + " шт.";
      let sumPrice = document.getElementById('amount');
      sumPrice.textContent = +sumPrice.textContent + cartPrice[itemName];

      if (cartCount[itemName] == 2) {
        let removeIcon = thisCartItem.querySelector('.button_less .remove');
        let minusIcon = thisCartItem.querySelector('.button_less .minus');
        removeIcon.style.display = "none";
        minusIcon.style.display = "inline";
      }
    });
  });

const cartNumber = {
  "Солнце": 0,
  "Венера": 1,
  "Земля": 2, 
  "Марс": 3,
  "Юпитер": 4,
  "Сатурн": 5,
  "Пояс астероидов": 6,
  "Уран": 7,
}

let addToCartButtons = document.querySelectorAll('.add_to_cart_btn');
addToCartButtons.forEach(button => {
  button.addEventListener('click', () => {
    let card = button.parentElement;
    let beforeStyle = window.getComputedStyle(card, '::before');
    let itemName = beforeStyle.getPropertyValue('content');
    itemName = itemName.slice(1, -1)
    let shoppingCart = document.getElementById("shopping_cart");
    let thisCartItem = shoppingCart.children[cartNumber[itemName]];
    let sumPrice = document.getElementById('amount');
    sumPrice.textContent = +sumPrice.textContent + cartPrice[itemName];
    if (cartCount[itemName] == 0) {
      thisCartItem.style.display = "flex";
    }

    let itemCount = thisCartItem.querySelector('#itemCount');
    itemCount.textContent = ++cartCount[itemName] + " шт.";
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