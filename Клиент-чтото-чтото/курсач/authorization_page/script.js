const logInBtn = document.querySelector('.need_log_in');
const registerBtn = document.querySelector('.need_register');
logInBtn.addEventListener('click', () => {
    const fromHeader = document.querySelector('.container h2');
    const submitBtn = document.querySelector('.submit');
    const passwordLabel = document.querySelector('.password_label');
    const passwordInput = document.querySelector('#password');
    const container = document.querySelector('.container');
    fromHeader.textContent = 'Вход';
    submitBtn.textContent = "Войти";
    logInBtn.style.display = "none";
    registerBtn.style.display = "block";
    passwordLabel.style.display = "none";
    passwordInput.style.display = "none";
    passwordInput.required = false;
    container.style.width = '400px';
})

registerBtn.addEventListener('click', () => {
    const fromHeader = document.querySelector('.container h2');
    const submitBtn = document.querySelector('.submit');
    const passwordLabel = document.querySelector('.password_label');
    const passwordInput = document.querySelector('#password');
    const container = document.querySelector('.container');
    fromHeader.textContent = 'Регистрация';
    submitBtn.textContent = "Зарегистрироваться";
    logInBtn.style.display = "block";
    registerBtn.style.display = "none";
    passwordLabel.style.display = "block";
    passwordInput.style.display = "block";
    passwordInput.required = true;
    container.style.width = '400px';
})