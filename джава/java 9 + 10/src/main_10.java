

public class main_10 {
    public static void main(String[] args) {
        MyStack myStack = new MyStack();
        myStack.push(1);
        myStack.push(2);
        myStack.push(3);
        MyStack stackCopy = (MyStack)myStack.clone();
        System.out.println("Исходный стек: " + myStack.toString());
        System.out.println("Копия стека: " + stackCopy.toString());
        System.out.println("Вызываем pop() исходного стека: " + myStack.pop());
        System.out.println("Исходный стек: " + myStack.toString());
        System.out.println("Копия стека: " + stackCopy.toString());
    }
}
