
// 622. Design Circular Queue
// https://leetcode.com/problems/design-circular-queue/




class MyCircularQueue {
private:
    // linked list
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* front;
    ListNode* rear;
    int capacity;
    int size;

public:
    MyCircularQueue(int k) {
        front = nullptr;
        rear = nullptr;
        capacity = k;
        size = 0;
    }

    bool enQueue(int value) {
        if( size == capacity ) return false;
        ++size;
        ListNode* node = new ListNode(value);
        if( rear != nullptr )
            rear->next = node;
        else
            front = node;
        rear = node;
        return true;
    }

    bool deQueue() {
        if( size == 0 ) return false;
        --size;
        ListNode* node = front;
        front = node->next;
        if( front == nullptr )
            rear = nullptr;
        delete node;
        return true;
    }

    int Front() {
        return front != nullptr ? front->val : -1;
    }

    int Rear() {
        return rear != nullptr ? rear->val : -1;
    }

    bool isEmpty() {
       return size == 0;
    }

    bool isFull() {
       return size == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
