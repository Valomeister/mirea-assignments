public class Triangle extends GeometricObject {
    // Поля данных для трех сторон треугольника
    private double side1 = 1.0;
    private double side2 = 1.0;
    private double side3 = 1.0;

    // Конструктор без аргументов, задающий значения по умолчанию 1.0
    public Triangle() {
    }

    // Конструктор с тремя параметрами для инициализации сторон треугольника
    public Triangle(double side1, double side2, double side3) throws IllegalTriangleException {
        if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
            throw new IllegalTriangleException("Сумма любых двух сторон должна быть больше длины третьей стороны.");
        }
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
    }

    // Getter для side1
    public double getSide1() {
        return side1;
    }

    // Getter для side2
    public double getSide2() {
        return side2;
    }

    // Getter для side3
    public double getSide3() {
        return side3;
    }

    // Метод для вычисления площади треугольника
    public double getArea() {
        double s = getPerimeter() / 2;
        return Math.sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    // Метод для вычисления периметра треугольника
    public double getPerimeter() {
        return side1 + side2 + side3;
    }

    // Метод toString, возвращающий строковое описание треугольника
    @Override
    public String toString() {
        return "Треугольник: сторона1 = " + side1 + " сторона2 = " + side2 +
                " сторона3 = " + side3;
    }
}
