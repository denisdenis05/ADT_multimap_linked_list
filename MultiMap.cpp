#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    this->array = nullptr;
    this->numberOfPairs = 0;
}


ElementNode* findLatestElementNode(ElementNode* head){
    ElementNode* node = head;
    while(node->next != nullptr)
        node = node->next;
    return node;
}

ElementNode* findNodeBeforeValue(ElementNode* head, TValue value) {
    ElementNode* node = head;
    if (node == nullptr)
        return nullptr;
    while(node->next != nullptr){
        if (node->next->value == value)
            return node;
        node = node->next;
    }
    return nullptr;
}

ArrayNode* findKey(ArrayNode* head, TKey key){

    ArrayNode* node = head;
    while (node != nullptr)
    {
        if (node->key_value.first == key)
            return node;
        node = node->next;
    }
    return nullptr;
}

ArrayNode* addNewElementInFront(ArrayNode* head, TKey key){

    ArrayNode* newArrayNode = new ArrayNode;
    std::pair<TKey, ElementNode*> key_value(key, nullptr);
    newArrayNode->key_value = key_value;
    newArrayNode->next = head;
    return newArrayNode;
}

void MultiMap::add(TKey c, TValue v) {
    if (this->array == nullptr) {
        ElementNode* newNode = new ElementNode;
        newNode->value = v;
        newNode->next = nullptr;

        ArrayNode* newKeyNode = new ArrayNode;
        std::pair<TKey, ElementNode*> key_value(c, newNode);
        newKeyNode->key_value = key_value;
        newKeyNode->next = nullptr;

        this->array = newKeyNode;
        this->numberOfPairs++;
        return;
    }

    ArrayNode* nodeOfKey = findKey(this->array, c);

    ElementNode* newNode;
    newNode->value = v;
    newNode->next = nullptr;

    if (nodeOfKey == nullptr) {
        this->array = addNewElementInFront(this->array, c);
        nodeOfKey = this->array;
    }

    if (nodeOfKey->key_value.second == nullptr){
        std::pair<TKey, ElementNode*> key_value(c, newNode);
        nodeOfKey->key_value = key_value;
    }
    else{
        ElementNode* lastNode = findLatestElementNode(nodeOfKey->key_value.second);
        lastNode->next = newNode;
    }
    this->numberOfPairs++;


}


bool MultiMap::remove(TKey c, TValue v) {
    ArrayNode* nodeOfKey = findKey(this->array, c);

    if (nodeOfKey != nullptr and nodeOfKey->key_value.second != nullptr){
        ElementNode* lastNode = findNodeBeforeValue(nodeOfKey->key_value.second, v);
        if (lastNode != nullptr) {
            ElementNode *nodeToRemove = lastNode->next; // TODO might need to return
            if (nodeToRemove == nodeOfKey->key_value.second)
                nodeOfKey->key_value.second = nullptr;
            else
                lastNode->next = nodeToRemove->next;
            delete (nodeOfKey);
        }
        else if(nodeOfKey->key_value.second->value == c){
            ElementNode* nodeToRemove = nodeOfKey->key_value.second; // TODO might need to return
            nodeOfKey->key_value.second = nullptr;
            delete (nodeToRemove);
        }
        this->numberOfPairs--;
        return true;
    }
	return  false;
}


vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> valueVector;
    ArrayNode* nodeOfKey = findKey(this->array, c);
    if (nodeOfKey != nullptr and nodeOfKey->key_value.second != nullptr){
        ElementNode* node = nodeOfKey->key_value.second;
        while (node != nullptr){
            valueVector.push_back(node->value);
            node = node->next;
        }
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

