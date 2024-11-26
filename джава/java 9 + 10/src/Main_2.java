import java.util.Scanner;

public class Main_2 {
    public static void main(String[] args) {

//        GenericStack<Integer> myStack = new GenericStack<>();
//        System.out.println(myStack.toString());
//        for (int i = 0; i < 20; i++) {
//            myStack.push(i);
//        }
//        System.out.println(myStack.toString());
//        System.out.println("Верхний элемент стека: " + myStack.peek());
//        System.out.println(myStack.toString());
//        System.out.println("Верхний элемент стека: " + myStack.pop());
//        System.out.println(myStack.toString());

        GenericStack<String> myStack = new GenericStack<>();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Введите 5 строк:");

        for (int i = 0; i < 5; i++) {
            System.out.print("Строка " + (i + 1) + ": ");
            myStack.push(scanner.nextLine());
        }
        while(myStack.getSize() > 0){
            System.out.println(myStack.pop());
        }

    }
}
