public class Circle implements Comparable<Circle> {
    private double radius;

    @Override
    public int compareTo(Circle o) {
        if (this.radius > o.radius) return 1;
        else if (this.radius == o.radius) return 0;
        else return -1;
    }

    Circle(double radius) {
        this.radius = radius;
    }

    public double getRadius() {
        return radius;
    }
}
