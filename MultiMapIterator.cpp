#include <stdexcept>
#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    current = col.head;
}

TElem MultiMapIterator::getCurrent() const{
    if (valid()) {
        return current->key_value;
    }
    throw std::runtime_error("Iterator not valid (getCurrent)");
}

bool MultiMapIterator::valid() const {
    return current != nullptr;

}

void MultiMapIterator::next() {
    if (current != nullptr) {
        current = current->next;
    } else {
        throw std::runtime_error("Iterator end");
    }
}

void MultiMapIterator::first() {
    current = col.head;
}

