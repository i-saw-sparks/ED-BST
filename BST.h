//
// Created by manie on 05/12/2020.
//

#ifndef ED_BST_BST_H
#define ED_BST_BST_H


#include <exception>
#include <string>

template<class T>
class BST {
private:
    class Node {
    private:
        T *data;
        Node *leftChild;
        Node *rightChild;
    public:
        Node();
        Node(const T&);
        ~Node();

        T* getData() const;
        Node* getLeftChild();
        Node* getRightChild();

        void setData(T*);
        void setLeftChild(Node*);
        void setRightChild(Node*);
    };

    Node* root;
    void insertData(Node*&, const T&);
    Node*& findData(Node*&, const T&);

    Node*& getLowest(Node*&);
    Node*& getHighest(Node*&);

    void parsePreOrder(Node*&);
    void parseInOrder(Node*&);
    void parsePostOrder(Node*&);

    void copyAll(const BST<T>&);

public:
    typedef Node* Position;

    BST();
    BST(const BST&);
    ~BST();

    bool isEmpty() const;
    void insertData(const T&);
    void deleteData(const T&);
    T* fetch(Position&);

    int getHeight(Position&);

    Position& findaData(const T&);

    Position& getLowest();
    Position& getHighest();

    bool isLeaf(Position&) const;

    int getHeight();

    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();

    void deleteAll();

    BST& operator = (const BST&);

    class Exception : public std::exception {
    private:
        std::string msg;
    public:
        explicit Exception(const char *message) : msg(message) {}

        explicit Exception(const std::string &message) : msg(message) {}

        virtual ~Exception() throw() {}

        virtual const char *what() const throw(){
            return msg.c_str();
        }
    };

};

template<class T>
BST<T>::BST(): root(nullptr) { }

template<class T>
BST<T>::BST(const BST &arg):root(nullptr) {
    copyAll(arg);
}

template<class T>
BST<T>::Node::Node():data(nullptr), leftChild(nullptr), rightChild(nullptr) { }

template<class T>
BST<T>::Node::Node(const T &arg): data(new T(arg)), leftChild(nullptr), rightChild(nullptr) {
    if(data == nullptr){
        throw Exception("Node(): std::bad_alloc");
    }
}

template<class T>
BST<T>::Node::~Node() {
    delete data;
}

template<class T>
T *BST<T>::Node::getData() const {
    return data;
}

template<class T>
typename BST<T>::Node *BST<T>::Node::getLeftChild() {
    return leftChild;
}

template<class T>
typename BST<T>::Node *BST<T>::Node::getRightChild() {
    return rightChild;
}

template<class T>
void BST<T>::Node::setData(T *arg) {
    data = arg;
}

template<class T>
void BST<T>::Node::setLeftChild(BST::Node *arg) {
    leftChild = arg;
}

template<class T>
void BST<T>::Node::setRightChild(BST::Node *arg) {
    rightChild = arg;
}


#endif //ED_BST_BST_H
