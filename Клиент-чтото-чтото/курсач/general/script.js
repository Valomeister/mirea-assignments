var minCircleWidth = 1;
var maxCircleWidth = 5;

// Функция для создания круга
function createCircle(startX, endX, startY, endY) {
    const circle = document.createElement('div');
    const size = Math.random() * (maxCircleWidth - minCircleWidth) + minCircleWidth; // Размер круга (от 20 до 70 пикселей)

    // Установка стилей круга
    circle.classList.add('circle');
    circle.style.width = `${size}px`;
    circle.style.height = `${size}px`;

    // Случайные координаты
    const x = startX + (endX - startX) * Math.random();
    const y = startY + (endY - startY) * Math.random();

    circle.style.left = `${x}px`;
    circle.style.top = `${y}px`;
    circle.initialOffset = y;

    // Добавляем круг в документ
    document.body.appendChild(circle);

    return circle;
}

function createCircles() {
    let xCount = 10;
    let yCount = 2;
    let circles = [];
    for (let i = 0; i < xCount; i++) {
        for (let j = 0; j < yCount; j++) {
            let startX = window.innerWidth / xCount * i;
            let endX = window.innerWidth / xCount * (i + 1);
            let startY = window.innerHeight / yCount * j;
            let endY = window.innerHeight / yCount * (j + 1);
            circles.push(createCircle(startX, endX, startY, endY));
        }
    }
    return circles;
}

let circles = createCircles();

window.addEventListener('scroll', () => {
    circles.forEach(circle => {
        const scrollOffset = window.scrollY;
        let curWidth = circle.getBoundingClientRect().width;
        let tanslateYValue = 2 * scrollOffset * curWidth**2 / maxCircleWidth**2;
        let fixedOffset = (document.body.scrollHeight + circle.initialOffset - tanslateYValue) % window.innerHeight;
        circle.style.top = `${fixedOffset}px`;
        
        
    });
});


