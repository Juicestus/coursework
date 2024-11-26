# include "linked_list.h"
# include <iostream>
# include <string>

using std::cout, std::endl, std::string, std::ostream;

void MyList::add(const std::string& name, int score) {
    MyNode* new_node = new MyNode(name, score);
    if (_head == nullptr) {
        _head = new_node;
        _tail = new_node;
    } else {
        _tail->next = new_node;
        new_node->prev = _tail;
        _tail = new_node;
    }
    _size++;
}

void MyList::clear() {
    MyNode* current = _head;
    while (current != nullptr) {
        MyNode* next_node = current->next;
        delete current;
        current = next_node;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

bool MyList::remove(const std::string& name) {
    MyNode* current = _head;
    while (current != nullptr) {
        if (current->name == name) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                _head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                _tail = current->prev;
            }
            delete current;
            _size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool MyList::insert(const std::string& name, int score, size_t index) {
    if (index > _size) {
        return false;
    }

    MyNode* new_node = new MyNode(name, score);

    if (index == 0) {
        new_node->next = _head;
        if (_head != nullptr) {
            _head->prev = new_node;
        }
        _head = new_node;
        if (_tail == nullptr) {
            _tail = new_node;
        }
    } else if (index == _size) {
        _tail->next = new_node;
        new_node->prev = _tail;
        _tail = new_node;
    } else {
        MyNode* current = _head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        new_node->next = current->next;
        new_node->prev = current;
        current->next->prev = new_node;
        current->next = new_node;
    }

    _size++;
    return true;
}

MyList::MyList() : _size(0), _head(nullptr), _tail(nullptr) {}

MyList::~MyList() {
    clear();
}

size_t MyList::size() const {
    return _size;
}

bool MyList::empty() const {
    return _head == nullptr;
}

MyNode* MyList::head() const {
    return _head;
}

ostream& operator<<(ostream& os, const MyList& myList) {
    MyNode* _current = myList.head();
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ " << _current->name << ", " << _current->score << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " --> [ " << _current->name << ", " << _current->score << " ]";
        _current = _current->next;
    }
    
    return os;
}

MyNode::MyNode(const std::string& name, int score) : name{name}, score{score}, next{nullptr}, prev{nullptr} {}
