
// 1429. First Unique Number
// https://leetcode.com/problems/first-unique-number/




class FirstUnique {
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

    ListNode* addAtTail(int val) {
        ListNode* node = new ListNode(val);
        if( tail != nullptr ) {
            node->prev = tail;
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
        return node;
    }

    void deleteNode(ListNode* node) {
        if( node == head && node == tail ) {
            head = nullptr;
            tail = nullptr;
        } else if( node == head ) {
            head = node->next;
            head->prev = nullptr;
        } else if( node == tail ) {
            tail = node->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        delete node;
    }

    unordered_map<int,ListNode*> um;

public:
    FirstUnique(vector<int>& nums) {
        head = nullptr;
        tail = nullptr;
        for(int i = 0; i < nums.size(); ++i)
            add(nums[i]);
    }

    int showFirstUnique() {
        return head == nullptr ? -1 : head->val;
    }

    void add(int value) {
        auto f = um.find(value);
        if( f == um.end() ) {
            ListNode* node = addAtTail(value);
            um.insert({value,node});
        } else if( f->second != nullptr ) {
            deleteNode(f->second);
            f->second = nullptr;
        }
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
