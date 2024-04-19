#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// WC = BC = TC = Theta(1)
MultiMap::MultiMap() {
    this->head = nullptr;
    this->numberOfPairs = 0;
}

/* BC = Theta(1)
 * WC = O(n)
 * TC = O(n)
 */
ElementNode* findLatestElementNode(ElementNode* head){
    ElementNode* node = head;
    while(node->next != nullptr)
        node = node->next;
    return node;
}

/* BC = Theta(1)
 * WC = O(n)
 * TC = O(n)
 */
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

/* BC = Theta(1)
 * WC = O(n)
 * TC = O(n)
 */
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


// WC = BC = TC = Theta(1)
ArrayNode* addNewElementInFront(ArrayNode* head, TKey key){

    ArrayNode* newArrayNode = new ArrayNode;
    std::pair<TKey, ElementNode*> key_value(key, nullptr);
    newArrayNode->key_value = key_value;
    newArrayNode->next = head;
    return newArrayNode;
}

/* BC = Theta(1)
 * WC = O(n)
 * TC = O(n)
 */
void MultiMap::add(TKey c, TValue v) {
    if (this->head == nullptr) {
        ElementNode* newNode = new ElementNode;
        newNode->value = v;
        newNode->next = nullptr;

        ArrayNode* newKeyNode = new ArrayNode;
        std::pair<TKey, ElementNode*> key_value(c, newNode);
        newKeyNode->key_value = key_value;
        newKeyNode->next = nullptr;

        this->head = newKeyNode;
        this->numberOfPairs++;
    }
    else {
        ArrayNode *nodeOfKey = findKey(this->head, c);

        ElementNode *newNode = new ElementNode;
        newNode->value = v;
        newNode->next = nullptr;

        if (nodeOfKey == nullptr) {
            this->head = addNewElementInFront(this->head, c);
            nodeOfKey = this->head;
        }

        if (nodeOfKey->key_value.second == nullptr) {
            std::pair<TKey, ElementNode *> key_value(c, newNode);
            nodeOfKey->key_value = key_value;
            this->numberOfPairs++;
        } else {
            ElementNode* firstValue = nodeOfKey->key_value.second;
            newNode->next = firstValue;
            nodeOfKey->key_value.second = newNode;
            this->numberOfPairs++;
        }
    }

}


/* BC = Theta(1)
 * WC = O(n)
 * TC = O(n)
 */
bool MultiMap::remove(TKey c, TValue v) {
    ArrayNode* nodeOfKey = findKey(this->head, c);

    if (nodeOfKey != nullptr and nodeOfKey->key_value.second != nullptr){
        ElementNode* lastNode = findNodeBeforeValue(nodeOfKey->key_value.second, v);
        if (lastNode != nullptr) {
            ElementNode *nodeToRemove = lastNode->next;
            lastNode->next = nodeToRemove->next;

            delete (nodeToRemove);
            this->numberOfPairs--;
            return true;
        }
        else if(nodeOfKey->key_value.second->value == v){
            ElementNode* nodeToRemove = nodeOfKey->key_value.second;
            if (nodeToRemove->next == nullptr) {
                std::pair<TKey, ElementNode *> key_value(c, nullptr);
                nodeOfKey->key_value = key_value;
            }
            else{
                std::pair<TKey, ElementNode *> key_value(c, nodeToRemove->next);
                nodeOfKey->key_value = key_value;
            }
            delete (nodeToRemove);
            this->numberOfPairs--;
            return true;
        }
    }
	return false;
}


/* BC = Theta(1)
 * WC = O(n)
 * TC = O(n)
 */
vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> valueVector;
    ArrayNode* nodeOfKey = findKey(this->head, c);
    if (nodeOfKey != nullptr and nodeOfKey->key_value.second != nullptr){
        ElementNode* node = nodeOfKey->key_value.second;
        while (node != nullptr){
            valueVector.push_back(node->value);
            node = node->next;
        }
    }
	return valueVector;
}


// WC = BC = TC = Theta(1)
int MultiMap::size() const {
	return this->numberOfPairs;
}


// WC = BC = TC = Theta(1)
bool MultiMap::isEmpty() const {
    return this->numberOfPairs == 0;
}

// WC = BC = TC = Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

/* BC = Theta(1)
 * WC = O(n^2)
 * TC = O(n^2)
 */
int MultiMap::updateValues(MultiMap& m){
    int numberOfModifiedPairs = 0;
    ArrayNode* arrayNode = this->head;
    while(arrayNode != nullptr) {
        TKey key = arrayNode->key_value.first;
        vector<TValue> valueVector = m.search(key);
        if (valueVector.size() > 0) {
            ElementNode *element = arrayNode->key_value.second;
            while (element != nullptr) {
                ElementNode *elementToDelete = element;
                element = element->next;
                delete (elementToDelete);
                this->numberOfPairs--;
            }
            arrayNode->key_value.second = nullptr;

            for (auto element: valueVector) {
                this->add(key, element);
                numberOfModifiedPairs++;
            }
        }
        arrayNode = arrayNode->next;
    }
    return numberOfModifiedPairs;
}


MultiMap::~MultiMap() {
    ArrayNode* arrayNode = this->head;
    while (arrayNode != nullptr){
        ElementNode* element = arrayNode->key_value.second;
        while(element != nullptr){
            ElementNode* elementToDelete = element;
            element = element->next;
            delete(elementToDelete);
        }
        ArrayNode* arrayNodeToDelete = arrayNode;
        arrayNode = arrayNode->next;
        delete(arrayNodeToDelete);
    }
}

