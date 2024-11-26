package vehicles;

public class Car extends Vehicle{


    @Override
    String vehicleType() {
        return "Car";
    }

    @Override
    public String toString() {
        String result = "";
        result += "Информация о машине:\n";
        result += "модель: " + getModel() + "\n";
        result += "Номер: " + getLicense() + "\n";
        result += "цвет: " + getColor() + "\n";
        result += "год: " + getYear() + "\n";
        result += "имя владельца: " + getOwnerName() + "\n";
        result += "номер страхования: " + getInsuranceNumber() + "\n";
        result += "двигатель: " + getEngineType() + "\n";
        return result;
    }

    public Car(String model, String license, String color, int year, String ownerName, String insuranceNumber, String engineType) {
        super(model,license, color, year, ownerName, insuranceNumber, engineType);
    }



}

