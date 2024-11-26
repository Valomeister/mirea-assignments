import java.util.Scanner;

public class task_3 {
    public static void main(String[] args) {
        String[] months = {"январь", "февраль", "март", "апрель", "май",
                "июнь", "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь"};
        int[] dom = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Введите номер месяца (от 1 до 12): ");
            int monthNumber = scanner.nextInt();
            System.out.println("Месяц: " + months[monthNumber - 1]);
            if (monthNumber == 2) {
                System.out.print("Количество дней в феврале зависит от года. Введите год: ");
                int year = scanner.nextInt();
                if (year % 4 == 0) {
                    System.out.println("Количество дней: " + (dom[monthNumber - 1] + 1));
                }
                else {
                    System.out.println("Количество дней: " + dom[monthNumber - 1]);
                }
            }
            else {
                System.out.println("Количество дней: " + dom[monthNumber - 1]);
            }
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Недопустимое число");
        } catch (Exception e) {
            System.out.println("Ошибка ввода! Введено нецелое число");
        } finally {
            scanner.close();
        }

    }
}
