#include "cstack.hpp"
#include <stdexcept>

CStack::CStack() {
    ptop = nullptr;
}

CStack::~CStack() {
    if (!cleared) {  
        clear();
    }
}

void CStack::pop() {
    if (!empty()) {
        Node* temp = ptop;
        ptop = ptop->next;
        delete temp;
    }
}

void CStack::clear() {
    while (!empty()) {
        pop();
    }
    cleared = true;  
}

void CStack::push(uint32_t val) {
    Node* newNode = new Node;
    newNode->info = val;
    newNode->next = ptop;
    ptop = newNode;
}

uint32_t CStack::top() {
    if (ptop != nullptr) {
        return ptop->info;
    }
    return 0;
}

bool CStack::empty() {
    return ptop == nullptr;
}

void CStack::operator*=(uint32_t multiplier) {
    Node* current = ptop;
    while (current != nullptr) {
        current->info *= multiplier;
        current = current->next;
    }
}

CStack& CStack::operator=(const CStack& other) {
    if (this == &other) {
        return *this;
    }

    CStack tempStack;
    Node* current = other.ptop;
    while (current != nullptr) {
        tempStack.push(current->info);
        current = current->next;
    }
    clear();
    current = tempStack.ptop;
    while (current != nullptr) {
        push(current->info);
        current = current->next;
    }

    return *this;
}


uint32_t CStack::operator[](size_t index) const {
    Node* current = ptop;
    size_t currentIndex = 0;
    while (current != nullptr) {
        if (currentIndex == index) {
            return current->info;
        }
        currentIndex++;
        current = current->next;
    }
    throw std::out_of_range("Попытка доступа к несуществующему элементу стека");
}
