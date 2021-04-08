

// Implement Stack Using Queues
// https://leetcode.com/problems/implement-stack-using-queues/



class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {}

    /** Push element x onto stack. */
    void push(int x) {
        q.push(x);
        size_t qs = q.size();
        // cout << "qs " << qs << endl;
        if( qs > 1 ) {
            for(size_t p = 1; p < qs; ++p) {
                // cout << "front " << q.front() << endl;
                q.push(q.front());
                q.pop();
            }
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int r = q.front();
        q.pop();
        return r;
    }

    /** Get the top element. */
    int top() {
        return q.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
private:
    queue<int> q;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
