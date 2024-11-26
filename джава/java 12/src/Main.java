public class Main {
    public static void main(String[] args) {
        System.out.println("- - - - Круг - - - -");
        Circle myCircle = new Circle(2.3);
        Circle myCircleCopy = myCircle.clone();
        System.out.println("До изменения радиуса у копии:");
        System.out.println("Изначальный круг: " + myCircle.toString());
        System.out.println("Копия круга: " + myCircleCopy.toString());
        myCircleCopy.setRadius(4.6);
        System.out.println("После изменения радиуса у копии:");
        System.out.println("Изначальный круг: " + myCircle.toString());
        System.out.println("Копия круга: " + myCircleCopy.toString());
        System.out.println("- - - - Прямоугольник - - - -");
        Rect myRect = new Rect(2.3, 2.4);
        Rect myRectCopy = myRect.clone();
        System.out.println("До изменения сторон копии прямоугольника:");
        System.out.println("Изначальный прямоугольник: " + myRect.toString());
        System.out.println("Копия прямоугольника: " + myRectCopy.toString());
        myRectCopy.setWidth(4.6);
        myRectCopy.setHeight(4.8);
        System.out.println("После изменения сторон копии прямоугольника:");
        System.out.println("Изначальный прямоугольник: " + myRect.toString());
        System.out.println("Копия прямоугольника: " + myRectCopy.toString());
    }
}
