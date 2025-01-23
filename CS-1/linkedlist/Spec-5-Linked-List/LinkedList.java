/*
 * Student information for assignment:
 * On my honor, Justus Languell, this programming assignment is my own work
 * and I have not provided this code to any other student.
 * UTEID:
 * jus@gtsbr.org
 * 
 * Note, I am not a student!
 * I am a high school sophomore who is doing these
 * assignments for my own experience and practice.
 */

import java.util.Iterator;

import javax.swing.InputMap;

public class LinkedList<E> implements IList<E> {

    // CS314 students. Add you instance variables here.
    // You decide what instance variables to use.
    // Must adhere to assignment requirements.
    // No ArrayLists or Java LinkedLists.

    private Node<E> head;

    // CS314 students, add constructors here:

    public class Node<T> {
        public T data;
        public Node<T> next;

        public Node(T data) {
            this.data = data;
        }

        public Node(T data, Node<T> next) {
            this.data = data;
            this.next = next;
        }
    }

    public LinkedList() {}

    // CS314 students, add methods here:

    /**
     * add item to the front of the list. <br>
     * pre: item != null <br>
     * post: size() = old size() + 1, get(0) = item
     *
     * @param item the data to add to the front of this list
     */
    public void addFirst(E item) {
        head = new Node<E>(item, head);
    }

    /**
     * add item to the end of the list. <br>
     * pre: item != null <br>
     * post: size() = old size() + 1, get(size() -1) = item
     *
     * @param item the data to add to the end of this list
     */
    public void addLast(E item) {
        if (head == null) {
            head = new Node<E>(item);
            return;
        }
        Node<E> current = head;
        while (current.next != null)
            current = current.next;
        current.next = new Node<E>(item);
    }

    /**
     * remove and return the first element of this list. <br>
     * pre: size() > 0 <br>
     * post: size() = old size() - 1
     *
     * @return the old first element of this list
     */
    public E removeFirst() {
        Node<E> oldHead = head;
        if (head.next == null) head = null;
        else head = head.next;
        return oldHead.data;
    }

    /**
     * remove and return the last element of this list. <br>
     * pre: size() > 0 <br>
     * post: size() = old size() - 1
     *
     * @return the old last element of this list
     */
    public E removeLast() {
        Node<E> current = head;
        Node<E> previous = null;
        while (current.next != null) {
            previous = current;
            current = current.next;
        }
        previous.next = null;
        return current.data;
    }

    @Override
    public void add(E item) {
        addLast(item);
    }

    @Override
    public void insert(int pos, E item) {
        if (pos <= -1) throw new IndexOutOfBoundsException();

        if (pos == 0) {
            addFirst(item);
            return;
        } 
        if (head == null) {
            head = new Node<E>(item);
            return;
        } else if (head.next == null) {
            head.next = new Node<E>(item);
            return;
        }

        Node<E> current = head;
        for (int index = 0; index < pos - 1; index++) {
            if (current.next == null)
                throw new IndexOutOfBoundsException();
            current = current.next;
        }

        current.next = new Node<E>(item, current.next);
    }

    @Override
    public E set(int pos, E item) {
        if (pos <= -1) throw new IndexOutOfBoundsException();

        Node<E> current = head;
        for (int index = 0; index < pos; index++) {
            if (current.next == null)
                throw new IndexOutOfBoundsException();
            current = current.next;
        }

        E old = current.data;
        current.data = item;
        return old;
    }

    @Override
    public E get(int pos) {
        if (pos <= -1) throw new IndexOutOfBoundsException();

        Node<E> current = head;
        for (int index = 0; index < pos; index++) {
            if (current.next == null)
                throw new IndexOutOfBoundsException();
            current = current.next;
        }

        return current.data;
    }

    @Override
    public E remove(int pos)  {
        if (pos <= -1) throw new IndexOutOfBoundsException();

        if (pos == 0) {
            return removeFirst();
        } else if (head.next == null) {
            throw new IndexOutOfBoundsException();
        }

        Node<E> current = head;
        for (int index = 0; index < pos - 1; index++) {
            if (current.next == null)
                throw new IndexOutOfBoundsException();
            current = current.next;
        }

        if (current.next == null)
            throw new IndexOutOfBoundsException();
        E old = current.next.data;
        current.next = current.next.next;
        return old;
    }

    @Override
    public boolean remove(E obj) {
        try {
            E v = remove(indexOf(obj));
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    @Override
    public int indexOf(E item) {
        Node<E> current = head;
        for (int index = 0; current.next != null; index++) {
            if (current.data == item)
                return index;
            current = current.next;
        } 
        return -1;
    }

    @Override
    public int indexOf(E item, int pos) {
        Node<E> current = head;
        for (int index = 0; current.next != null; index++) {
            if (index >= pos)
                if (current.data == item)
                    return index;       
            current = current.next;
        } 
        return -1;
    }

    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("{ ");
        Node<E> current = head;
        while (current != null) {
            sb.append(current.data);
            current = current.next;
            if (current != null) sb.append(", ");
        }
        sb.append(" }");
        return sb.toString();
    }

}