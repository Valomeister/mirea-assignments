public class Rect implements Shape{
    private double width, height;
    Rect(double width, double height) {
        this.width = width;
        this.height = height;
    }
    public void setWidth(double val) { this.width = val; }
    public void setHeight(double val) { this.height = val; }

    @Override
    public String toString() {
        return "width = " + width + ", height = " + height;
    }
    {}
    @Override
    public Rect clone() {
        try {
            return (Rect) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new RuntimeException(e);
        }
    }
}
