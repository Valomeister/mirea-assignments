

import java.util.ArrayList;
import java.util.Arrays;

public class GenericStack<E> {
    private Object[] arr;
    private int capacity;
    private int size;

    public GenericStack() {
        this.arr = new Object[3];
        this.capacity = 3;
        this.size = 0;
    }

    public int getSize() {
        return size;
    }
    public E peek() {
        return (E) arr[size - 1];
    }
    public void push(E o) {
        if (capacity == size) {
            expandCapacity();
        }
        arr[size++] = o;
    }

    public void expandCapacity() {
        Object[] newArr = new Object[capacity * 2];
        System.arraycopy(this.arr, 0, newArr, 0, capacity);
        capacity *= 2;
        this.arr = newArr;
    }

    public E pop() {
        E o = (E)arr[--size];
        return o;
    }
    public boolean isEmpty() {
        return (size == 0);
    }
    @Override
    public String toString() {
        return "стек: " + Arrays.toString(Arrays.copyOfRange(arr, 0, Math.max(size, 0)));
    }
}

//import java.util.ArrayList;
//
//public class GenericStack<E> extends ArrayList<E> {
//
//    GenericStack () {
//        super();
//    }
//
//    public int getSize() {
//        return size();
//    }
//
//    public E peek() {
//        return get(size() - 1);
//    }
//
//    public E pop() {
//        return remove(size() - 1);
//    }
//
//    public void push(E o) {
//        add(o);
//    }
//
//    public boolean isEmpty() {
//        return super.isEmpty();
//    }
//
//    @Override
//    public String toString() {
//        return "стек: " + super.toString();
//    }
//}
