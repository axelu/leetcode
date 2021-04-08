
// 641. Design Circular Deque
// https://leetcode.com/problems/design-circular-deque/



class MyCircularDeque {
private:
    // doubly linked list
    struct ListNode {
        int val;
        ListNode* prev;
        ListNode* next;
        ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
    };

    ListNode* front;
    ListNode* rear;
    int capacity;
    int size;

public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        front = nullptr;
        rear = nullptr;
        capacity = k;
        size = 0;
    }

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if( size == capacity ) return false;
        ++size;
        ListNode* node = new ListNode(value);
        if( front != nullptr ) {
            node->next = front;
            front->prev = node;
        } else {
            rear = node;
        }
        front = node;
        return true;
    }

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if( size == capacity ) return false;
        ++size;
        ListNode* node = new ListNode(value);
        if( rear != nullptr ) {
            node->prev = rear;
            rear->next = node;
        } else {
            front = node;
        }
        rear = node;
        return true;
    }

    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if( size == 0 ) return false;
        --size;
        ListNode* node = front;
        front = node->next;
        if( front != nullptr ) {
            front->prev = nullptr;
        } else {
            rear = nullptr;
        }
        delete node;
        return true;
    }

    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if( size == 0 ) return false;
        --size;
        ListNode* node = rear;
        rear = node->prev;
        if( rear != nullptr ) {
            rear->next = nullptr;
        } else {
            front = nullptr;
        }
        delete node;
        return true;
    }

    /** Get the front item from the deque. */
    int getFront() {
        return front != nullptr ? front->val : -1;
    }

    /** Get the last item from the deque. */
    int getRear() {
        return rear != nullptr ? rear->val : -1;
    }

    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return size == 0;
    }

    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return size == capacity;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
