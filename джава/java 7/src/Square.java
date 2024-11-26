public class Square extends GeometricObject implements Colorable{
    private double side;

    Square() {
        this.side = 0;
    }

    Square(double side) {
        this.side = side;
    }

    // Геттер для side
    public double getSide() {
        return side;
    }

    // Сеттер для side
    public void setSide(double side) {
        this.side = side;
    }

    @Override
    public void howToColor() {
        System.out.println("Раскрасьте все четыре стороны");
    }

    @Override
    public double getArea() {
        return this.side * this.side;
    }
}
