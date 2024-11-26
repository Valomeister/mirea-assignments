public class Main {
    public static void main(String[] args) {
        StackOnQueue stack = new StackOnQueue();

        stack.push(42);
        stack.push(84);

        System.out.println("Вершина стека (top): " + stack.top());
        System.out.println("Удаляем вершину стека (pop): " + stack.pop());
        System.out.println("Стек пуст? " + stack.empty());
        System.out.println("Текущие элементы стека: " + stack);
    }
}