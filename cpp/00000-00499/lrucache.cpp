
// 146. LRU Cache
// https://leetcode.com/problems/lru-cache/

class LRUCache {
private:
    // Definition of a doubly-linked list
    struct ListNode {
        int key;
        int val;
        ListNode *prev;
        ListNode *next;
        ListNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
        ListNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
        ListNode(int k, int v, ListNode *prev) : key(k), val(v), prev(prev), next(nullptr) {}
    };
    ListNode* la[10001];
    int Capacity; // total capacity
    int c; // current count
    ListNode* front;
    ListNode* back;
    
    void prnt() {
        ListNode* ln = front;
        cout << "cache: ";
        while( ln != nullptr ) {
            cout << ln->val << " ";
            ln = ln->next;
        }
        cout << endl;        
    }
    
    void age(ListNode* ln) {
        // cout << "age called: " << ln->val << endl;
        // cout << "before "; prnt();
        if( ln == back ) return;
        if( ln == back && ln == front ) return; // Capacity == 1
        ListNode* prev = ln->prev;
        ListNode* next = ln->next;
        if( prev != nullptr ) prev->next = next;
        next->prev = prev;
        if( ln == front ) front = next;
        ln->prev = back;
        back->next = ln;
        back = ln;
        ln->next = nullptr;
        // cout << "after "; prnt();
    }

public:
    LRUCache(int capacity) {
        Capacity = capacity;
        front = nullptr;
        back = nullptr;
        for(int i = 0; i < 10001; ++i)
           la[i] = nullptr;
        c = 0;
    }
    
    int get(int key) {
        // cout << "get called: " << key << endl;
        if( la[key] != nullptr ) {
            age(la[key]);
            return la[key]->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        // cout << "put called: " << key << " " << value << endl;
        // map<int,ListNode*>::iterator f = m.find(key);
        ListNode* ln;
        if( la[key] != nullptr ) {
            ln = la[key];
            // update value
            ln->val = value;
            // age
            age(ln);
        } else {
            // cout << "before "; prnt();
            if( c == Capacity ) {
                // evict front
                // cout << "put evicting " << front->key << endl;
                ListNode* nf = front->next;
                if( front == back ) back = nullptr; // Capacity == 1
                la[front->key] = nullptr;
                // delete front;
                ln = front;
                front = nf;
                if( front != nullptr) front->prev = nullptr;
            } else {
                ln = new ListNode();
                ++c;
            }
            // create and insert in back
            // ListNode* ln = new ListNode(key,value);
            ln->key = key;ln->val = value;
            if( back != nullptr ) {
                back->next = ln;
                ln->prev = back;
            } else {
                front = ln;
            }
            back = ln;
            la[key] = ln;
            // cout << "after "; prnt();
        }
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
