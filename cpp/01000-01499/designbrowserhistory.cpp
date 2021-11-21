
// 1472. Design Browser History
// https://leetcode.com/problems/design-browser-history/




class BrowserHistory {
private:
    // doubly linked list
    struct ListNode {
        string s;
        ListNode* prev;
        ListNode* next;
        ListNode(string s) : s(s), prev(nullptr), next(nullptr) {}
    };

    ListNode* node;

public:
    BrowserHistory(string homepage) {
        node = new ListNode(homepage);
    }

    void visit(string url) {
        // delete forward history
        ListNode* t;
        ListNode* ln = node->next;
        while( ln != nullptr ) {
            t = ln;
            ln = t->next;
            delete t;
        }
        ln = new ListNode(url);
        node->next = ln;
        ln->prev = node;
        node = ln;
    }

    string back(int steps) {
        int i = 0;
        while( i < steps && node->prev != nullptr ) {
            node = node->prev;
            ++i;
        }
        return node->s;
    }

    string forward(int steps) {
        int i = 0;
        while( i < steps && node->next != nullptr ) {
            node = node->next;
            ++i;
        }
        return node->s;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
