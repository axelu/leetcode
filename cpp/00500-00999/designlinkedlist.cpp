
// 707. Design Linked List
// https://leetcode.com/problems/design-linked-list/



class MyLinkedList {
private:
    // doubly linked list
    struct ListNode {
        int val;
        ListNode* prev;
        ListNode* next;
        ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
    };

    ListNode* tail;
    ListNode* head;
    int size;

    ListNode* getNode(int index) {
        ListNode* node;
        if( index < size/2 ) {
            node = head;
            for(int i = 0; i < index; ++i)
                node = node->next;
        } else {
            node = tail;
            for(int i = 0; i < size-1-index; ++i)
                node = node->prev;
        }
        return node;
    }

    void deleteHead() {
        --size;
        ListNode* node = head;
        head = node->next;
        if( head != nullptr ) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;
    }

    void deleteTail() {
        --size;
        ListNode* node = tail;
        tail = node->prev;
        if( tail != nullptr ) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;
    }

public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        tail = nullptr;
        head = nullptr;
        size = 0;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if( size == 0 ) return -1;
        if( index < 0 || index >= size ) return -1;
        return getNode(index)->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        ++size;
        ListNode* node = new ListNode(val);
        if( head != nullptr ) {
            node->next = head;
            head->prev = node;
        } else {
            tail = node;
        }
        head = node;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
       ++size;
        ListNode* node = new ListNode(val);
        if( tail != nullptr ) {
            node->prev = tail;
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if( index < 0 || index > size ) return;
        if( index == 0 ) {
            addAtHead(val);
        } else if( index == size ) {
            addAtTail(val);
        } else {
            ListNode* currNode = getNode(index);
            ListNode* newNode = new ListNode(val);
            currNode->prev->next = newNode;
            newNode->prev = currNode->prev;
            newNode->next = currNode;
            currNode->prev = newNode;
            ++size;
        }
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if( size == 0 ) return;
        if( index < 0 || index >= size ) return;
        if( index == 0 ) {
            deleteHead();
        } else if( index == size-1 ) {
            deleteTail();
        } else {
            ListNode* node = getNode(index);
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            --size;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
