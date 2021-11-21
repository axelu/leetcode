
// 460. LFU Cache
// https://leetcode.com/problems/lfu-cache/


// https://en.wikipedia.org/wiki/Least_frequently_used -> http://dhruvbird.com/lfu.pdf from
class LFUCache {
private:
    int Capacity;
    struct ListNode; // forward declaration

    // doubly linked list
    struct FrequencyNode {
        int val;
        FrequencyNode* prev;
        FrequencyNode* next;
        ListNode* head; // head of node list
        ListNode* tail; // tail of node list
        FrequencyNode(int x) : val(x), prev(nullptr), next(nullptr), tail(nullptr) {}
    };

    // doubly linked list
    struct ListNode {
        int key;
        int val;
        FrequencyNode* frequencyNode;
        ListNode* prev;
        ListNode* next;
        ListNode(int k, int v) : key(k), val(v), frequencyNode(nullptr), prev(nullptr), next(nullptr) {}
    };

    unordered_map<int,ListNode*> listNodes;
    FrequencyNode* frequencyListHead; // head of frequency list
    FrequencyNode* frequencyListTail; // tail of frequency list

    // debug
    void prnt() {
        FrequencyNode* fn = frequencyListHead;
        if( frequencyListHead == nullptr ) cout << "frequencyListHead is null" << endl;
        while( fn != nullptr ) {
            cout << "FrequencyNode " << fn->val << endl;
            fn = fn->next;
        }
    }

    void addListNodeToFrequencyNode(ListNode* listNode, FrequencyNode* frequencyNode, int frequency) {
        // the frequency node provided could be a nullptr
        // if the frequency node provided is not a nullptr, it could be the correct one or not
        //     in case it is not the correct on, it will be greater
        if( frequencyNode == nullptr ) {
            frequencyNode = new FrequencyNode(frequency);
            listNode->frequencyNode = frequencyNode;
            listNode->prev = nullptr;
            listNode->next = nullptr;
            frequencyNode->head = listNode;
            frequencyNode->tail = listNode;
            // add the new frequency node to the frequency list, it must be the tail
            if( frequencyListTail == nullptr ) {
               frequencyListHead = frequencyNode;
               frequencyListTail = frequencyNode;
            } else {
               frequencyListTail->next = frequencyNode;
               frequencyNode->prev = frequencyListTail;
               frequencyListTail = frequencyNode;
            }
        } else if( frequencyNode->val == frequency ) {
            // add list node to end of node list of this frequency
            listNode->frequencyNode = frequencyNode;
            frequencyNode->tail->next = listNode;
            listNode->prev = frequencyNode->tail;
            listNode->next = nullptr;
            frequencyNode->tail = listNode;
        } else {
            // create a new frequency node and insert it before the provided frequency node
            // create a new frequency node
            FrequencyNode* newFrequencyNode = new FrequencyNode(frequency);
            listNode->frequencyNode = newFrequencyNode;
            listNode->prev = nullptr;
            listNode->next = nullptr;
            newFrequencyNode->head = listNode;
            newFrequencyNode->tail = listNode;
            // insert our new frequency node efore the provided frequency node
            FrequencyNode* prev = frequencyNode->prev;
            if( prev != nullptr ) {
                prev->next = newFrequencyNode;
                newFrequencyNode->prev = prev;
                newFrequencyNode->next = frequencyNode;
                frequencyNode->prev = newFrequencyNode;
            } else {
                newFrequencyNode->prev = nullptr;
                frequencyListHead = newFrequencyNode;
                newFrequencyNode->next = frequencyNode;
                frequencyNode->prev = newFrequencyNode;
            }
        }
        // debug
        // prnt();
    }

    void deleteFrequencyNode(FrequencyNode* frequencyNode) {
        // the frequency node maybe the front of the frequency list OR
        // the frequency node maybe the back of the frequency list OR
        // the frequency node maybe somewhere in the middle of the frequency list OR
        // the frequency node maybe the front AND the back of the frequency list
        FrequencyNode* prev = frequencyNode->prev;
        FrequencyNode* next = frequencyNode->next;
        if( prev == nullptr && next != nullptr ) {
            next->prev = nullptr;
            frequencyListHead = next;
        } else if( prev != nullptr && next == nullptr ) {
            prev->next = nullptr;
            frequencyListTail = prev;
        } else if( prev != nullptr && next != nullptr ) {
            prev->next = next;
            next->prev = prev;
        } else {
            // prev == nullptr && next == nullptr
            frequencyListHead = nullptr;
            frequencyListTail = nullptr;
        }
        delete frequencyNode;
    }

    void removeListNodeFromFrequencyNode(ListNode* listNode) {
        FrequencyNode* frequencyNode = listNode->frequencyNode;
        // the list node maybe the front of the node list OR
        // the list node maybe the back of the node list OR
        // the list node maybe somewhere in the middle of the node list OR
        // the list node maybe the front AND the back of the node list
        // in the last case, we will delete the list node AND the frequency node

        ListNode* prev = listNode->prev;
        ListNode* next = listNode->next;
        if( prev == nullptr && next != nullptr ) {
            next->prev = nullptr;
            frequencyNode->head = next;
        } else if( prev != nullptr && next == nullptr ) {
            prev->next = nullptr;
            frequencyNode->tail = prev;
        } else if( prev != nullptr && next != nullptr ) {
            prev->next = next;
            next->prev = prev;
        } else {
            // prev == nullptr && next == nullptr
            // delete the frequency node
            deleteFrequencyNode(frequencyNode);
        }
    }
public:
    LFUCache(int capacity) {
        Capacity = capacity;
        frequencyListHead = nullptr;
        frequencyListTail = nullptr;
    }

    int get(int key) {
        if( Capacity == 0 ) return -1;
        // cout << "get " << key << endl;
        unordered_map<int,ListNode*>::iterator f;
        f = listNodes.find(key);
        if( f == listNodes.end() ) return -1;

        int frequency = f->second->frequencyNode->val;
        FrequencyNode* nextFrequencyNode = f->second->frequencyNode->next; // maybe nullptr
        // remove listNode from its current frequency list
        removeListNodeFromFrequencyNode(f->second);
        // add node to the end of the node list of the next frequency list
        addListNodeToFrequencyNode(f->second,nextFrequencyNode,frequency+1);

       return f->second->val;
    }

    void put(int key, int value) {
        if( Capacity == 0 ) return;
        // cout << "put key " << key << " value " << value << endl;
        unordered_map<int,ListNode*>::iterator f;
        f = listNodes.find(key);
        if( f != listNodes.end() ) {
            // update value of key
            f->second->val = value;

            int frequency = f->second->frequencyNode->val;
            FrequencyNode* nextFrequencyNode = f->second->frequencyNode->next; // maybe nullptr
            // remove listNode from its current frequency list
            removeListNodeFromFrequencyNode(f->second);
            // add node to the end of the node list of the next frequency list
            addListNodeToFrequencyNode(f->second,nextFrequencyNode,frequency+1);
        } else {
            // key does not exist
            if( listNodes.size() < Capacity ) {
                // cout << "put key does not exist below capacity" << endl;
                ListNode* listNode = new ListNode(key,value);
                addListNodeToFrequencyNode(listNode,frequencyListHead,1);
                // insert into list node map
                listNodes.insert({key,listNode});
            } else {
                // cout << "put key does not exist at capacity" << endl;
                // remove the least frequently used key
                // if there is more than one, remove the least recently used key
                ListNode* listNode = frequencyListHead->head;
                // cout << "put key does not exist at capacity evicting " << listNode->val << endl;
                removeListNodeFromFrequencyNode(listNode);
                listNodes.erase(listNode->key);
                // create new list node and add it to frequency node with frequency of 1
                // we will not create a new list node, but instead change the key and value of it
                listNode->key = key;
                listNode->val = value;
                addListNodeToFrequencyNode(listNode,frequencyListHead,1);
                // update list node map
                listNodes.insert({key,listNode});
            }
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
