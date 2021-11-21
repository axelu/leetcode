
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
        ListNode() : val(0), prev(nullptr), next(nullptr) {}
        ListNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
        ListNode(int k, int v, ListNode *prev) : key(k), val(v), prev(prev), next(nullptr) {}
    };
    map<int,ListNode*> m;
    int Capacity; // total capacity
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
    }

    int get(int key) {
        // cout << "get called: " << key << endl;
        map<int,ListNode*>::iterator f = m.find(key);
        if( f != m.end() ) {
            age(f->second);
            return f->second->val;
        }
        return -1;
    }

    void put(int key, int value) {
        // cout << "put called: " << key << " " << value << endl;
        map<int,ListNode*>::iterator f = m.find(key);
        if( f != m.end() ) {
            ListNode* ln = f->second;
            // update value
            ln->val = value;
            // age
            age(ln);
        } else {
            // cout << "before "; prnt();
            if( m.size() == Capacity ) {
                // evict front
                // cout << "put evicting " << front->key << endl;
                ListNode* nf = front->next;
                if( front == back ) back = nullptr; // Capacity == 1
                m.erase(front->key);
                delete front;
                front = nf;
                if( front != nullptr) front->prev = nullptr;
            }
            // create and insert in back
            ListNode* ln = new ListNode(key,value);
            if( back != nullptr ) {
                back->next = ln;
                ln->prev = back;
            } else {
                front = ln;
            }
            back = ln;
            m.insert({key,ln});
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
