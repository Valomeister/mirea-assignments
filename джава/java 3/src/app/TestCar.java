package app;

import vehicles.Car;
import vehicles.ElectricCar;

public class TestCar {
    public static void main(String[] args) {
        Car car = new Car("Toyota Corolla", "7Y6F321", "red", 2015, "Владислав",
                "A7261812", "ДВС");
        ElectricCar eCar = new ElectricCar("Tesla model x", "6GB32H34", "white", 2020, "Степан",
                "C2372837", 1);

        car.setColor("blue");
        car.setYear(2016);
        eCar.setBatteryCapacity(.96);
        eCar.setModel("Tesla model Y");

        System.out.println(car.toString());
        System.out.println(eCar.toString());
    }
}

