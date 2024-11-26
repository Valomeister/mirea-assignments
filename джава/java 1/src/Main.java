import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        /*
        // constants
        final int CM_PER_METER = 100;
        // input
        double height;
        double weight;
        // output
        double bmi;
        Scanner input = new Scanner(System.in);
        System.out.println("Введите рост в см: ");
        height = input.nextDouble();
        System.out.println("Введите вес в кг: ");
        weight = input.nextDouble();
        bmi = weight / (height / CM_PER_METER * height / CM_PER_METER);
        System.out.println("BMI равен " + bmi);
        if (bmi < 18.5)
            System.out.println("Недостаточный вес");
        else if (bmi < 25)
            System.out.println("Норма");
        else if (bmi < 30)
            System.out.println("Избыточный вес");
        else
            System.out.println("Ожирение =(");
        */

        // TASK 1 //
        /*
        final double RUBLES_PER_YUAN = 11.91;
        int yuans, roubles_ceiled;
        double roubles;
        Scanner input = new Scanner(System.in);
        System.out.println("Введите сумму в юанях: ");
        yuans = input.nextInt();
        roubles = yuans * RUBLES_PER_YUAN;
        roubles_ceiled = (int)Math.ceil(roubles);
        System.out.println("В рублях это будет: " + roubles_ceiled);
        */

        // TASK 2 //
        ///*
        final double RUBLES_PER_YUAN = 11.91;
        int yuans, roubles_ceiled;
        double roubles;
        Scanner input = new Scanner(System.in);
        System.out.println("Введите сумму в юанях: ");
        yuans = input.nextInt();
        if (yuans % 10 == 1)
            System.out.println("Вы внесли " + yuans + " китайский юань");
        else if (2 <= yuans % 10 && yuans % 10 <= 4)
            System.out.println("Вы внесли " + yuans + " китайских юаня");
        else
            System.out.println("Вы внесли " + yuans + " китайских юаней");
        roubles = yuans * RUBLES_PER_YUAN;
        roubles_ceiled = (int) Math.ceil(roubles);
        if (roubles_ceiled % 10 == 1)
            System.out.println("После перевода вы получите " + roubles_ceiled + " российский рубль");
        else if (2 <= roubles_ceiled % 10 && roubles_ceiled % 10 <= 4)
            System.out.println("После перевода вы получите " + roubles_ceiled + " российских рубля");
        else
            System.out.println("После перевода вы получите " + roubles_ceiled + " российских рублей");

        //*/


    }}