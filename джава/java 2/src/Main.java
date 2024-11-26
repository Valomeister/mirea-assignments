public class Main {
    public static void main(String[] args) {

        Car a = new Car();
        Car b = new Car("Volvo xc90", "А031ББ | 77", "black", 2013);
        Car c = new Car("Toyota Corolla",2015);

        b.To_String();
        b.setYear(2000);
        b.setLicense("И498ПП | 66");
        b.To_String();
        System.out.println("Возраст автомобиля \"c\": " + c.getAge());

    }
}