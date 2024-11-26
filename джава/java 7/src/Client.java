import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        GeometricObject[] objects = new GeometricObject[5];
        objects[0] = new Circle(4);
        objects[1] = new ComparableCircle(3);
        objects[2] = new Rectangle(2, 6);
        objects[3] = new Triangle(3, 2, 3);
        objects[4] = new Square(5);

        for (GeometricObject x : objects) {
            System.out.println("Площадь равна " + x.getArea());
            if (x instanceof Colorable) {
                ((Colorable) x).howToColor();
            }
            System.out.println("- - - - -");
        }
    }
}
