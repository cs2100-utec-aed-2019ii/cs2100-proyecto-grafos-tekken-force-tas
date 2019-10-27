#include <iostream>
#include "Node.h"
template <typename T>
class List{
public:
    typedef Node<T> N;
private:
    N* head; 
};
