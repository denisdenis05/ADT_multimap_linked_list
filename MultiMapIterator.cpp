#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentKeyNode = col.array;
    if (currentKeyNode != nullptr)
        currentElementNode = currentKeyNode->key_value.second;
    else
        currentElementNode = nullptr;
}

TElem MultiMapIterator::getCurrent() const{
    if (valid()) {
        return std::make_pair(currentKeyNode->key_value.first, currentElementNode->value);
    }
    return NULL_TELEM;
}

bool MultiMapIterator::valid() const {
    return currentKeyNode != nullptr && currentElementNode != nullptr;
}

void MultiMapIterator::next() {
    if (currentElementNode->next != nullptr) {
        currentElementNode = currentElementNode->next;
    } else {
        currentKeyNode = currentKeyNode->next;
        while (currentKeyNode != nullptr and currentKeyNode->key_value.second == nullptr)
            currentKeyNode = currentKeyNode->next;

        if (currentKeyNode != nullptr)
            currentElementNode = currentKeyNode->key_value.second;
        else
            currentElementNode = nullptr;
    }
}

void MultiMapIterator::first() {
    currentKeyNode = col.array;
    if (currentKeyNode != nullptr)
        currentElementNode = currentKeyNode->key_value.second;
    else
        currentElementNode = nullptr;
}

