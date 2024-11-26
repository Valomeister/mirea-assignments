public class Circle implements Shape{
    private double radius;
    Circle(double radius) {
        this.radius = radius;
    }
    public void setRadius(double val) { this.radius = val; }
    @Override
    public String toString() {
        return "radius = " + radius;
    }

    @Override
    public Circle clone() {
        try {
            return (Circle) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new RuntimeException(e);
        }
    }
}
