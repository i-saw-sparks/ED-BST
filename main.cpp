#include <iostream>
#include <random>
#include <chrono>
#include <functional>

#include "BST.h"

int main() {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, 100000);
    auto dice = bind(distribution, generator);

    BST<int> arbol;
    int value, cantidad;

    std::cout<<"Ingrese la cantidad de numeros que desea ingresar: ";
    std::cin>>cantidad;
    std::cout<<std::endl<<std::endl;

    for (int i = 0; i < cantidad; ++i) {
        value = dice();
        std::cout << "Insertando: " << value << std::endl;
        arbol.insertData(value);
    }
    
    std::cout << std::endl << std::endl;

    std::cout << "Recorrido en PreOrder: " << std::endl;
    arbol.parsePreOrder();
    std::cout << std::endl << std::endl;

    std::cout << "Recorrido en InOrder: " << std::endl;
    arbol.parseInOrder();
    std::cout << std::endl << std::endl;

    std::cout << "Recorrido en PostOrder"<<std::endl;
    arbol.parsePostOrder();
    std::cout<<std::endl<<std::endl;

    std::cout<<"Altura del subarbol izquierdo:  "<<arbol.getLeftHeight()<<std::endl;
    std::cout<<"Altura del subarbol derecho:  "<<arbol.getRightHeight();
}
