//
// Created by manie on 05/12/2020.
//

#ifndef ED_BST_BST_H
#define ED_BST_BST_H


#include <exception>
#include <string>
#include <iostream>

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

        Node(const T &);

        ~Node();

        T *getData() const;

        Node *&getLeftChild();
        Node *&getRightChild();

        void setDataPtr(T *);
        void setData(T &);

        void setLeftChild(Node *);

        void setRightChild(Node *);
    };
public:
    typedef Node *Position;

private:
    Position root;

    void insertData(Position &, const T &);

    Position& findData(Position& , const T &);

    Position& getLowest(Position& );
    Position& getHighest(Position& );

    void parsePreOrder(Position& );
    void parseInOrder(Position& );
    void parsePostOrder(Position& );

    void copyAll(const BST<T> &);
    void copy(Position &, const Position&);

public:

    BST();
    BST(const BST &);
    ~BST();

    bool isEmpty() const;

    void insertData(const T &);
    void deleteData(Position&);

    T *fetch(Position &);

    int getHeight(Position &);
    int getHeight();
    int getRightHeight();
    int getLeftHeight();

    Position &findaData(const T &);

    Position &getLowest();
    Position &getHighest();

    bool isLeaf(Position &) const;

    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();

    void deleteAll();

    BST &operator=(const BST &);

    class Exception : public std::exception {
    private:
        std::string msg;
    public:
        explicit Exception(const char *message) : msg(message) {}

        explicit Exception(const std::string &message) : msg(message) {}

        virtual ~Exception() throw() {}

        virtual const char *what() const throw() {
            return msg.c_str();
        }
    };

};

template<class T>
BST<T>::BST(): root(nullptr) {}

template<class T>
BST<T>::BST(const BST &arg):root(nullptr) {
    copyAll(arg);
}

template<class T>
BST<T>::~BST() {
    deleteAll();
}

template<class T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

template<class T>
void BST<T>::insertData(const T &arg) {
    insertData(root, arg);
}

template<class T>
void BST<T>::insertData(Position& r, const T &arg) {
    if (r == nullptr) {
        if ((r = new Node(arg)) == nullptr) {
            throw Exception("insertData(.,.): std::bad_alloc");
        }
    } else {
        if (arg < *(r->getData())) {
            insertData(r->getLeftChild(), arg);
        } else {
            insertData(r->getRightChild(), arg);
        }
    }
}


template<class T>
T *BST<T>::fetch(BST::Position &r) {
    return r->getData();
}

template<class T>
typename BST<T>::Position &BST<T>::findaData(const T &arg) {
    return findData(root, arg);
}

template<class T>
typename BST<T>::Position& BST<T>::findData(BST::Position& r, const T &arg) {
    if (r == nullptr || r->getData() == arg) {
        return r;
    }

    if (arg < r->getData()) {
        return findData(r->getLeftChild(), arg);
    }

    return findData(r->getRightChild(), arg);
}

template<class T>
typename BST<T>::Position &BST<T>::getLowest() {
    return getLowest(root);
}

template<class T>
typename BST<T>::Position & BST<T>::getLowest(BST::Position& r) {
    if (r == nullptr || r->getLeftChild() == nullptr) {
        return r;
    }

    return getLowest(r->getLeftChild());
}

template<class T>
typename BST<T>::Position &BST<T>::getHighest() {
    return getHighest(root);
}

template<class T>
typename BST<T>::Position & BST<T>::getHighest(BST::Position &r) {
    if (r == nullptr || r->getRightChild() == nullptr) {
        return r;
    }

    return getHighest(r->getRightChild());
}

template<class T>
bool BST<T>::isLeaf(BST::Position &r) const {
    return r != nullptr && r->getLeftChild() == r->getRightChild();
}

template<class T>
int BST<T>::getHeight() {
    return getHeight(root);
}

template<class T>
int BST<T>::getRightHeight() {
    return getHeight(root->getRightChild());
}

template<class T>
int BST<T>::getLeftHeight() {
    return getHeight(root->getLeftChild());
}

template<class T>
int BST<T>::getHeight(BST::Position &r) {
    if (r == nullptr) {
        return 0;
    }

    int leftHeight(getHeight(r->getLeftChild()));
    int rightHeight(getHeight(r->getRightChild()));

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template<class T>
void BST<T>::parsePreOrder() {
    parsePreOrder(root);
}

template<class T>
void BST<T>::parsePreOrder(BST::Position &r) {
    if (r == nullptr) {
        return;
    }

    std::cout << *(r->getData()) << ", ";
    parsePreOrder(r->getLeftChild());
    parsePreOrder(r->getRightChild());
}

template<class T>
void BST<T>::parseInOrder() {
    parseInOrder(root);
}

template<class T>
void BST<T>::parseInOrder(BST::Position &r) {
    if (r == nullptr) {
        return;
    }

    parseInOrder(r->getLeftChild());
    std::cout << *(r->getData()) << ", ";
    parseInOrder(r->getRightChild());
}

template<class T>
void BST<T>::parsePostOrder() {
    parsePostOrder(root);
}

template<class T>
void BST<T>::parsePostOrder(BST::Position &r) {
    if (r == nullptr) {
        return;
    }

    parsePostOrder(r->getLeftChild());
    parsePostOrder(r->getRightChild());
    std::cout << *(r->getData()) << ", ";
}

template<class T>
BST<T> &BST<T>::operator=(const BST &t) {
    copyAll(t);
    return *this;
}

template<class T>
void BST<T>::deleteData(BST::Position& pos) {
    Position aux;
    if(pos == nullptr){
        return;
    }
    if(isLeaf(pos)){
        delete pos;
        pos = nullptr;
    }else {
        if (pos->getLeftChild() != nullptr) {
            aux = getHighest(pos->getLeftChild());
            pos->setData(*(aux->getData()));
            deleteData(getHighest(pos->getLeftChild()));
        } else {
            aux = getLowest(pos->getRightChild());
            pos->setData(*(aux->getData()));
            deleteData(getLowest(pos->getRightChild()));
        }

    }
}

template<class T>
void BST<T>::deleteAll() {
    while(root != nullptr){
        deleteData(root);
    }
}

template<class T>
void BST<T>::copy(BST::Position &r, const BST::Position &rcpy) {
    r = new Node(*(rcpy->getData()));

    if(rcpy->getLeftChild() != nullptr) {
        copy(r->getLeftChild(), rcpy->getLeftChild());
    }
    if(rcpy->getRightChild() != nullptr) {
        copy(r->getLeftChild(), rcpy->getRightChild());
    }
}

template<class T>
void BST<T>::copyAll(const BST<T> &tree) {
    deleteAll();
    if(tree.root == nullptr){
        return;
    }
    copy(root,tree.root);
}


template<class T>
BST<T>::Node::Node():data(nullptr), leftChild(nullptr), rightChild(nullptr) {}

template<class T>
BST<T>::Node::Node(const T &arg): data(new T(arg)), leftChild(nullptr), rightChild(nullptr) {
    if (data == nullptr) {
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
typename BST<T>::Position &BST<T>::Node::getLeftChild() {
    return leftChild;
}

template<class T>
typename BST<T>::Position &BST<T>::Node::getRightChild() {
    return rightChild;
}

template<class T>
void BST<T>::Node::setData(T &arg) {
    *data = arg;
}

template<class T>
void BST<T>::Node::setDataPtr(T *arg) {
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
