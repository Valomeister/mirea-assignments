import java.util.LinkedList;
import java.util.Queue;

public class StackOnQueue {
    private Queue<Integer> queueMain; // Основная очередь
    private Queue<Integer> queueTmp; // Вспомогательная очередь

    public StackOnQueue() {
        queueMain = new LinkedList<>();
        queueTmp = new LinkedList<>();
    }

    public void push(int x) {
        queueTmp.offer(x); // Добавляем элемент во вспомогательную очередь
        // Перемещаем все элементы из queue1 в queue2
        while (!queueMain.isEmpty()) {
            queueTmp.offer(queueMain.poll());
        }
        // Меняем ссылки местами: queue2 становится основной
        queueMain = queueTmp;
        queueTmp = new LinkedList<>();
    }

    public int pop() {
        return queueMain.poll();
    }

    public int top() {
        return queueMain.peek();
    }

    public boolean empty() {
        return (queueMain.isEmpty());
    }

    @Override
    public String toString() {
        return queueMain.toString();
    }

}
