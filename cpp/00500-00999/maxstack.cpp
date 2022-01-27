
// 716. Max Stack
// https://leetcode.com/problems/max-stack/



class MaxStack {
private:
    // Definition of a doubly-linked list
    struct ListNode {
        int val;
        ListNode *prev;
        ListNode *next;
        ListNode() : val(0), prev(nullptr), next(nullptr) {}
        ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
        ListNode(int x, ListNode *prev) : val(x), prev(prev), next(nullptr) {}
    };
    ListNode* tp;
    map<int,vector<ListNode*>> m;

public:
    /** initialize your data structure here. */
    MaxStack() {
        tp = nullptr;
    }

    void push(int x) {
        ListNode* prev = tp;
        tp = new ListNode(x,tp);
        if( prev != nullptr ) prev->next = tp;
        auto p = m.insert({x,{tp}});
        if( !p.second )
            p.first->second.push_back(tp);
    }

    int pop() {
        ListNode* prev = tp->prev;
        if( prev != nullptr ) prev->next = nullptr;
        int key = tp->val;
        auto f = m.find(key);
        f->second.pop_back();
        if( f->second.empty() ) m.erase(key);
        tp = prev;
        return key;
    }

    int top() {
        return tp->val;
    }

    int peekMax() {
        return m.rbegin()->first;
    }

    int popMax() {
        int ans = m.rbegin()->first;
        ListNode* ln = m.rbegin()->second.back(); // node to delete
        if( ln == tp ) tp = ln->prev;
        if( ln->prev != nullptr )
            ln->prev->next = ln->next;
        if( ln->next != nullptr )
            ln->next->prev = ln->prev;
        m.rbegin()->second.pop_back();
        if( m.rbegin()->second.empty() )
            m.erase(ans);
        return ans;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
