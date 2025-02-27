#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {

    private:

    struct Node {

        Node *next, *prev;
        T data;

        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} { }
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} { }
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {  }
    };


    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() { node = nullptr; };
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            return node->data;
        }
        pointer operator->() const {
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            node = node->next;
            return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            auto it = *this;
            node = node->next;
            return it;
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            node = node->prev;
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            auto it = *this;
            node = node->prev;
            return it;
        }
        bool operator==(const basic_iterator& other) const noexcept {
            return other.node == node;
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            return other.node != node;
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() {
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
    }
    List( size_type count, const T& value ) {
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        for (size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    explicit List( size_type count ) {
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        for (size_type i = 0; i < count; ++i) {
            push_back(T{});
        }
    }

    List( const List& other ) {
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
        for (Node* current = other.head.next; current != &other.tail; current = current->next) {
            push_back(current->data);
        }
    }
    List( List&& other ) {
        head.next = other.head.next;
        head.next->prev = &head;    // <-- 

        tail.prev = other.tail.prev;
        tail.prev->next = &tail;    // <--

        _size = other._size;

        other.head.next = &other.tail;
        other.tail.prev = &other.head;
        other._size = 0;
    }
    ~List() {
        clear();
    }
    List& operator=( const List& other ) {
        if (this == &other) return *this;
        clear();
        for (const auto& value : other) {
            push_back(value);
        }
        return *this;
    }
    List& operator=( List&& other ) noexcept {
        if (this == &other) return *this;
        clear();
        head.next = other.head.next;
        head.next->prev = &head;

        tail.prev = other.tail.prev;
        tail.prev->next = &tail;

        _size = other._size;

        other.head.next = &other.tail;
        other.tail.prev = &other.head;
        other._size = 0;
        return *this;
    }

    reference front() {
        return head.next->data;
    }
    const_reference front() const {
        return head.next->data;
    }
	
    reference back() {
        return tail.prev->data;
    }
    const_reference back() const {
        return tail.prev->data;
    }
	
    iterator begin() noexcept {
        return iterator(head.next);
    }
    const_iterator begin() const noexcept {
        return const_iterator(head.next);
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(head.next);
    }

    iterator end() noexcept {
        return iterator(&tail);
    }
    const_iterator end() const noexcept {
        return const_iterator(&tail);
    }
    const_iterator cend() const noexcept {
        return const_iterator(&tail);
    }

    bool empty() const noexcept {
        return _size == 0;
    }

    size_type size() const noexcept {
        return _size;
    }

    void clear() noexcept {
        Node* current = head.next;
        while (current != &tail) {
            Node* del = current;
            current = current->next;
            delete del;
        }
        head.next = &tail;
        tail.prev = &head;
        _size = 0;
    }

    iterator insert( const_iterator pos, const T& value ) {
        Node* new_node = new Node(value, pos.node->prev, pos.node);
        pos.node->prev->next = new_node;
        pos.node->prev = new_node;
        _size++;
        return iterator(new_node);
    }

    iterator insert( const_iterator pos, T&& value ) {
        Node* new_node = new Node(std::move(value), pos.node->prev, pos.node);
        pos.node->prev->next = new_node;
        pos.node->prev = new_node;
        _size++;
        return iterator(new_node);
    }

    iterator erase( const_iterator pos ) {
        Node* del = pos.node;
        del->prev->next = del->next;
        del->next->prev = del->prev;
        delete del;
        _size--;
        return iterator(del->next);
    }

    void push_back( const T& value ) {
        Node* new_node = new Node(value, tail.prev, &tail);
        tail.prev->next = new_node;
        _size++;
        tail.prev = new_node;
    }

    void push_back( T&& value ) {
        Node* new_node = new Node(std::move(value), tail.prev, &tail);
        tail.prev->next = new_node;
        _size++;
        tail.prev = new_node;
    }

    void pop_back() {
        Node* del = tail.prev;
        tail.prev = del->prev;
        del->prev->next = &tail;
        delete del;
        _size--;
    }
	
    void push_front( const T& value ) {
        Node* new_node = new Node(value, &head, head.next);
        head.next->prev = new_node;
        head.next = new_node;
        _size++;
    }
	void push_front( T&& value ) {
        Node* new_node = new Node(std::move(value), &head, head.next);
        head.next->prev = new_node;
        head.next = new_node;
        _size++;
    }

    void pop_front() {
        Node* del = head.next;
        head.next = del->next;
        del->next->prev = &head;
        delete del;
        _size--;
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}