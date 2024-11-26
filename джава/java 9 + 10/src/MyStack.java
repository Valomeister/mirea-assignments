public class MyStack<E> implements Cloneable {
    private java.util.ArrayList<E> list = new java.util.ArrayList<>();
    public int getSize() {
        return list.size();
    }


    public E peek() {
        return list.get(getSize() - 1);
    }
    public void push(E o) {
        list.add(o);
    }
    public E pop() {
        E o = list.get(getSize() - 1);
        list.remove(getSize() - 1);
        return o;
    }
    public boolean isEmpty() {
        return list.isEmpty();
    }
    @Override
    public String toString() {
        return "стек: " + list.toString();
    }
    public Object clone() {
        MyStack stackClone = new MyStack();
        stackClone.list = (java.util.ArrayList) list.clone();
        return stackClone;
    }
}