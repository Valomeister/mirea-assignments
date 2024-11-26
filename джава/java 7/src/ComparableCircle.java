public class ComparableCircle extends Circle{
    public double getArea() {
        return getRadius() * getRadius() * Math.PI;
    }

    ComparableCircle(double radius) {
        super(radius);
    }

    public int compareTo(ComparableCircle anotherObj) {
        if (this.getArea() == anotherObj.getArea()) return 0;
        else if (this.getArea() > anotherObj.getArea()) return 1;
        else return -1;
    }
}
