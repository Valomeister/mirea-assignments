public class Car {
    final int CurrentYear = 2024;
    private String model = "unknown", license = "unknown", color = "unknown";
    private int year = 0;

    public Car() {

    };
    public Car(String myModel, String myLicense, String myColor, int myYear) {
        model = myModel;
        license = myLicense;
        color = myColor;
        year = myYear;
    }
    public Car(String myModel, int myYear){
        model = myModel;
        year = myYear;
    }
    public String getModel() {
        return model;
    }

    public void setModel(String myModel) {
        this.model = myModel;
    }

    public String getLicense() {
        return license;
    }

    public void setLicense(String myLicense) {
        this.license = myLicense;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String myColor) {
        this.color = myColor;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int myYear) {
        this.year = myYear;
    }

    public int getAge() {
        return CurrentYear - year;
    }
    public void To_String() {
        System.out.println("Информация о машине:");
        System.out.println("Модель: " + model);
        System.out.println("Номер: " + license);
        System.out.println("Цвет: " + color);
        System.out.println("Год выпуска: " + year);
        System.out.println("- - - - - - - -");
    }
}