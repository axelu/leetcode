
// 432. All O`one Data Structure
// https://leetcode.com/problems/all-oone-data-structure/





/* from the constraints:
 *     at most 50000 calls will be made to inc, dec, getMaxKey, and getMinKey
 *     each function must run in O(1) average time complexity
 * unordered_map, unordered_set: search, insertion, and removal of elements have average constant-time complexity
 */
class AllOne {
private:
    struct T;

    // doubly linked list
    struct ListNode {
        int cnt;
        unordered_set<T*> keys;
        ListNode* prev;
        ListNode* next;
        ListNode(int cnt, T* key, ListNode* prev, ListNode* next) : cnt(cnt), keys({key}), prev(prev), next(next) {}
    };

    struct T {
        string key;
        ListNode* listNode;
        T(string key) : key(key), listNode(nullptr) {}
    };

    ListNode* head;
    ListNode* tail;

    unordered_map<string,T*> um;

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

    void printState() {
        ListNode* ln = head;
        while( ln != nullptr ) {
            cout << ln->cnt << endl;
            cout << "    ";
            for(T* t: ln->keys) {
                cout << t->key << " ";
            }
            cout << endl;
            ln = ln->next;
        }
        cout << "tail " << tail->cnt << endl;
        return;
    }

public:
    AllOne() {
        head = nullptr;
        tail = nullptr;
    }

    void inc(string key) {
        auto f = um.find(key);
        if( f == um.end() ) {
            // key does not exist
            T* t = new T(key);
            um.insert({key,t});

            if( head == nullptr ) {
                ListNode* ln = new ListNode(1,t,nullptr,nullptr);
                t->listNode = ln;
                head = ln;
                tail = ln;

            } else {
                // the head must have cnt >= 1
                if( head->cnt == 1 ) {
                    t->listNode = head;
                    head->keys.insert(t);
                } else {
                    ListNode* ln = new ListNode(1,t,nullptr,head);
                    t->listNode = ln;
                    head->prev = ln;
                    head = ln;
                }
            }

        } else {
            // key does exist
            T* t = f->second;
            ListNode* curr_ln = t->listNode;
            if( curr_ln->next == nullptr ) {
                // we need to add a new node that will become the new tail
                ListNode* ln = new ListNode(curr_ln->cnt+1,t,curr_ln,nullptr);
                t->listNode = ln;
                tail = ln;
                curr_ln->next = ln;

            } else if( curr_ln->next->cnt == curr_ln->cnt + 1 ) {
                // we can simply move our 'key' to the next node
                curr_ln->next->keys.insert(t);
                t->listNode = curr_ln->next;

            } else {
                // we need to insert a new node into our list after the current node
                ListNode* ln = new ListNode(curr_ln->cnt+1,t,curr_ln,curr_ln->next);
                t->listNode = ln;
                curr_ln->next = ln;
                ln->next->prev = ln;

            }
            // remove our key from its 'old' list node
            curr_ln->keys.erase(t);
            if( curr_ln->keys.empty() )
                deleteNode(curr_ln);
        }

        // cout << "after inc " << key << endl;printState();
        return;
    }

    void dec(string key) {
        auto f = um.find(key); // it is guaranteed that key exists
        T* t = f->second;
        ListNode* curr_ln = t->listNode;
        if( curr_ln->prev == nullptr ) {
            if( curr_ln->cnt > 1 ) {
                // we need to add a new node that will become the new head
                ListNode* ln = new ListNode(curr_ln->cnt-1,t,nullptr,curr_ln);
                t->listNode = ln;
                head = ln;
                curr_ln->prev = ln;
            } else {
                um.erase(f);
            }

        } else if( curr_ln->prev->cnt == curr_ln->cnt - 1 ) {
            // we can simply move our 'key' to the previous node
            curr_ln->prev->keys.insert(t);
            t->listNode = curr_ln->prev;

        } else {
            // we need to insert a new node into our list before the current node
            ListNode* ln = new ListNode(curr_ln->cnt-1,t,curr_ln->prev,curr_ln);
            t->listNode = ln;
            curr_ln->prev = ln;
            ln->prev->next = ln;

        }
        // remove our key from its 'old' list node
        curr_ln->keys.erase(t);
        if( curr_ln->keys.empty() )
            deleteNode(curr_ln);

        // cout << "after dec " << key << endl;printState();

        return;
    }

    string getMaxKey() {
        if( tail == nullptr )
            return "";
        return (*tail->keys.begin())->key;
    }

    string getMinKey() {
        if( head == nullptr )
            return "";
        return (*head->keys.begin())->key;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
