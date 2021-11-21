
// 155. Min Stack
// https://leetcode.com/problems/min-stack/


class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {}

    void push(int x) {
        t = new P(x,t);
        min = ::min(min,x);
    }

    void pop() {
        P* old = t;
        t = t->next;
        delete old;
        min = INT_MAX;
        _setMin(t);
    }

    int top() {
        return t->val;
    }

    int getMin() {
        return min;
    }
private:
    struct P {
        int val;
        P* next;
        P(int x, P* n) : val(x), next(n) {}
    };
    P* t = nullptr;
    int min = INT_MAX;
    void _setMin(P* p) {
        if ( p == nullptr ) return;
        min = ::min(min,p->val);
        _setMin(p->next);
        return;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
