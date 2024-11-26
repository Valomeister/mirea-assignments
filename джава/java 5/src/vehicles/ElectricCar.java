package vehicles;

public class ElectricCar extends Car implements ElectricVehicle {
    private double batteryCapacity;

    public ElectricCar(String model, String license, String color, int year, String ownerName, String insuranceNumber, String engineType) {
        super(model,license, color, year, ownerName, insuranceNumber, engineType);
        this.engineType = "Electric";
    }
    public double getBatteryCapacity() {
        return batteryCapacity;
    }
    public void setBatteryCapacity(double batteryCapacity) {
        this.batteryCapacity = batteryCapacity;
    }

    @Override
    String vehicleType() {
        return "Electric Car";
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
        result += "емкость аккумулятора: " + getBatteryCapacity() + "\n";
        return result;
    }

}

