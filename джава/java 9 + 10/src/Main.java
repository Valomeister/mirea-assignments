import java.lang.reflect.Array;
import java.util.ArrayList;

public class Main {
    public static <T> int findInArr(T[] arr, T target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    public static <T extends Comparable<T>> T findMax(T[] array) {

        T max = array[0];

        for (T element : array) {
            if (element.compareTo(max) > 0) {
                max = element;
            }
        }

        return max;
    }

    public static <T extends Comparable<T>> T findMax(T[][] array) {
        T max = array[0][0];

        for (T[] row : array) {
            for (T element : row) {
                if (element.compareTo(max) > 0) {
                    max = element;
                }
            }
        }

        return max;
    }

    public static <T> ArrayList<T> removeDuplicates(ArrayList<T> list) {
        ArrayList<T> result = new ArrayList<>();

        for (T element : list) {
            if (!result.contains(element)) {
                result.add(element);
            }
        }

        return result;
    }
    public static void main(String[] args) {

        Integer[][] numbers = {
                {3, 5, 9},
                {7, 1, 4},
                {2, 8, 6}
        };

        System.out.println("Наибольший элемент: " + findMax(numbers));


//        Circle[] arr = new Circle[5];
//        arr[0] = new Circle(1);
//        arr[1] = new Circle(2.2);
//        arr[2] = new Circle(1.7);
//        arr[3] = new Circle(3.1);
//        arr[4] = new Circle(2.9);
//        Circle biggest = findMax(arr);
//        System.out.println("Наибольший круг - это круг срадиусом " + biggest.getRadius());
    }
}