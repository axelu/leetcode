
// 1381. Design a Stack With Increment Operation
// https://leetcode.com/problems/design-a-stack-with-increment-operation/



class CustomStack {
private:
    // doubly linked list
    struct ListNode {
        int val;
        ListNode* prev;
        ListNode* next;
        ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
    };

    ListNode* head;
    ListNode* tail;
    int maxSize;
    int size;

public:
    CustomStack(int maxSize) {
        head = nullptr;
        tail = nullptr;
        this->maxSize = maxSize;
        size = 0;
    }

    void push(int x) {
        if( size == maxSize ) return;

        ListNode* node = new ListNode(x);
        if( tail != nullptr ) {
            tail->next = node;
            node->prev = tail;
        } else {
            head = node;
        }
        tail = node;
        ++size;
    }

    int pop() {
        if( size == 0 ) return -1;

        int ans = tail->val;
        ListNode* node = tail;
        if( tail->prev != nullptr ) {
            tail = node->prev;
            tail->next = nullptr;
        } else {
            tail = nullptr;
            head = nullptr;
        }
        delete node;
        --size;
        return ans;
    }

    void increment(int k, int val) {
        if( size == 0 ) return;

        ListNode* node = head;
        int i = 0;
        while( node != nullptr && i < k) {
            node->val += val;
            ++i;
            node = node->next;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
