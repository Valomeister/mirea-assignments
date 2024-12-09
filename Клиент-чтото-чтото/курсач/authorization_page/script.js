const logInBtn = document.querySelector('.need_log_in');
const registerBtn = document.querySelector('.need_register');
logInBtn.addEventListener('click', () => {
    const fromHeader = document.querySelector('.container h2');
    const submitBtn = document.querySelector('.submit');
    const emailLabel = document.querySelector('.email_label');
    const emailInput = document.querySelector('#email');
    const container = document.querySelector('.container');
    fromHeader.textContent = 'Вход';
    submitBtn.textContent = "Войти";
    logInBtn.style.display = "none";
    registerBtn.style.display = "block";
    emailLabel.style.display = "none";
    emailInput.style.display = "none";
    emailInput.required = false;
    container.style.width = '400px';
})

registerBtn.addEventListener('click', () => {
    const fromHeader = document.querySelector('.container h2');
    const submitBtn = document.querySelector('.submit');
    const emailLabel = document.querySelector('.email_label');
    const emailInput = document.querySelector('#email');
    const container = document.querySelector('.container');
    fromHeader.textContent = 'Регистрация';
    submitBtn.textContent = "Зарегистрироваться";
    logInBtn.style.display = "block";
    registerBtn.style.display = "none";
    emailLabel.style.display = "block";
    emailInput.style.display = "block";
    emailInput.required = true;
    container.style.width = '400px';
})