package app;

import vehicles.Car;
import vehicles.ElectricCar;

public class TestCar {
    public static void main(String[] args) {
        Car car = new Car("Toyota Corolla", "7Y6F321", "red", 2015, "Владислав",
                "A7261812", "Combustion");
        ElectricCar eCar = new ElectricCar("Tesla model x", "6GB32H34", "white", 2020, "Степан",
                "C2372837", "Electric");

        car.setYear(2021);
        eCar.setYear(2016);
        car.setOwnerName("Андрей");
        eCar.setOwnerName("Михаил");
        car.setInsuranceNumber("B12387913");
        eCar.setInsuranceNumber("D392713831");
        eCar.setBatteryCapacity(0.99);
        System.out.println("емкость аккумулятора: " + eCar.getBatteryCapacity());
        System.out.println(car.toString());
        System.out.println(eCar.toString());
    }
}

