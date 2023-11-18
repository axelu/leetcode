
// 1224. Maximum Equal Frequency
// https://leetcode.com/problems/maximum-equal-frequency/




class Solution {
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
        int key;
        ListNode* listNode;
        T(int key) : key(key), listNode(nullptr) {}
    };

    ListNode* head;
    ListNode* tail;
    int list_sz;

    unordered_map<int,T*> um;

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

    void inc(int key) {
        auto f = um.find(key);
        if( f == um.end() ) {
            // key does not exist
            T* t = new T(key);
            um.insert({key,t});

            if( head == nullptr ) {
                ListNode* ln = new ListNode(1,t,nullptr,nullptr);
                ++list_sz;
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
                    ++list_sz;
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
                ++list_sz;
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
                ++list_sz;
                t->listNode = ln;
                curr_ln->next = ln;
                ln->next->prev = ln;

            }
            // remove our key from its 'old' list node
            curr_ln->keys.erase(t);
            if( curr_ln->keys.empty() ) {
                deleteNode(curr_ln);
                --list_sz;
            }
        }

        return;
    }

public:
    int maxEqualFreq(vector<int>& nums) {
        int n = nums.size();

        // as we move left to right through nums, we will keep track
        // of the frequency of the values in 'frequency buckets'
        // at every step we check if we have only two frequency buckets
        // case 1
        //     freq a and freq b = a + 1, and in freq b bucket is only one value
        // case 2
        //     freq a = 1 and freq b, and in freq a bucket is only one value
        // case 3
        //     freq a = 1 with however many elements
        // case 4
        //     freq a, and in freq a bucket is only one value

        int ans = 0;

        head = nullptr;
        tail = nullptr;
        list_sz = 0;

        for(int i = 0; i < n; ++i) {
            inc(nums[i]);

            if( list_sz == 1 ) {
                if( head->cnt == 1 ) { // case 3
                    ans = i+1;
                } else if( head->keys.size() == 1 ) { // case 4
                    ans = i+1;
                }
            } else if( list_sz == 2 ) {
                if( head->cnt + 1 == tail->cnt && tail->keys.size() == 1 ) { // case 1
                    ans = i+1;
                } else if( head->cnt == 1 and head->keys.size() == 1 ) { // case 2
                    ans = i+1;
                }
            }
        }

        return ans;
    }
};
