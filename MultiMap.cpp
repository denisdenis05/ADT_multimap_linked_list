#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    this->head = nullptr;
    this->numberOfPairs = 0;
}


ArrayNode* findBeforeKeyValue(ArrayNode* head, TKey key, TValue value){
    ArrayNode* node = head;
    while (node != nullptr and node->next != nullptr)
    {
        if (node->next->key_value.first == key && node->next->key_value.second == value)
            return node;
        node = node->next;
    }
    return nullptr;
}

ArrayNode* findKeyValue(ArrayNode* head, TKey key, TValue value){
    ArrayNode* node = head;
    while (node != nullptr)
    {
        if (node->key_value.first == key && node->key_value.second == value)
            return node;
        node = node->next;
    }
    return nullptr;
}

ArrayNode* addNewElementInFront(ArrayNode* head, TKey key, TValue value){
    ArrayNode* newArrayNode = new ArrayNode;
    std::pair<TKey, TValue> key_value(key, value);
    newArrayNode->key_value = key_value;
    newArrayNode->next = head;
    return newArrayNode;
}

void MultiMap::add(TKey c, TValue v) {
    this->head = addNewElementInFront(this->head, c, v);
    this->numberOfPairs++;
}


bool MultiMap::remove(TKey c, TValue v) {
    ArrayNode* nodeOfKey = findBeforeKeyValue(this->head, c, v);
    if (nodeOfKey != nullptr) {
        ArrayNode* nodeToRemove = nodeOfKey->next;
        nodeOfKey->next = nodeToRemove->next;
        delete nodeToRemove;
        this->numberOfPairs--;
        return true;
    }
    else if (this->head != nullptr and this->head->key_value.first == c and this->head->key_value.second == v){
        if (this->head->next == nullptr) {
            delete this->head;
            this->head = nullptr;
            this->numberOfPairs--;
            return true;
        }
        else{
            ArrayNode* nextNode = this->head->next;
            delete this->head;
            this->head = nextNode;
            this->numberOfPairs--;
            return true;
        }
    }
	return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> valueVector;
    ArrayNode* node = this->head;
    while (node != nullptr) {
        if (node->key_value.first == c)
            valueVector.push_back(node->key_value.second);
        node = node->next;
    }
    return valueVector;
}


int MultiMap::size() const {
	return this->numberOfPairs;
}


bool MultiMap::isEmpty() const {
    return this->numberOfPairs == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	//TODO - Implementation
}

