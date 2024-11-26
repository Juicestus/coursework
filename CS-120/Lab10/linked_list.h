# ifndef MY_LIST_H
# define MY_LIST_H

# include <string>
# include <iostream>

struct MyNode {
    public:
        std::string name;
        int score;
        
        MyNode* next;
        MyNode* prev;
        MyNode(const std::string& name, int score);
};

class MyList {
    private:
        size_t _size;
        MyNode* _head;
        MyNode* _tail;
    
    public:
        MyList();
        ~MyList();
        size_t size() const;
        bool empty() const;
        MyNode* head() const;
        void add(const std::string& name, int score);
        void clear();
        bool remove(const std::string& name);
        bool insert(const std::string& name, int score, size_t index);
};

std::ostream& operator<<(std::ostream& os, const MyList& myList);

# endif
