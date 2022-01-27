
// 706. Design HashMap
// https://leetcode.com/problems/design-hashmap/




// using a Skiplist
// https://leetcode.com/problems/design-skiplist/
class MyHashMap {
private:
    struct Node {
        int key;
        int val;
        int height; // size of next
        Node* next[];
    };

    int h;
    Node* sentinel;
    Node* stack[33];

    Node* newNode(int k, int v, int h) {
        // assuming 8 bytes as size of pointer (64bit architecture)
        Node* node = (Node*)malloc(sizeof(struct Node) + 8 * h);
        node->key = k;
        node->val = v;
        node->height = h;
        for(int i = 0; i < h; ++i) node->next[i] = nullptr;
        return node;
    }

    // picking a random integer, and count the number of
    // trailing 1's in the binary representation of that number
    // 1-33
    int pickHeight() {
        int z = rand();
        int k = 0;
        int m = 1;
        while((z & m) != 0) {
            k++;
            m <<= 1;
        }
        return k+1;
    }

public:
    /** Initialize your data structure here. */
    MyHashMap() {
        h = 0;
        sentinel = newNode(-1,-1,33); // max number of levels 33
        stack[0] = sentinel;
        srand(time(nullptr));
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        Node *u = sentinel;
        int r = h;
        int comp = 0;
        while(r >= 0) {
            while(u->next[r] != nullptr && (comp = u->next[r]->key - key) < 0)
                u = u->next[r];
            if( u->next[r] != nullptr && comp == 0 ) {
                u->next[r]->val = value;
                return;
            }
            stack[r--] = u; // going down, store u
        }
        Node* w = newNode(key,value,pickHeight());
        while(h < w->height)
            stack[++h] = sentinel; // height increased
        for(int i = 0; i < w->height; i++) {
            w->next[i] = stack[i]->next[i];
            stack[i]->next[i] = w;
        }
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        Node* u = sentinel;
        int r = h;
        while(r >= 0) {
            while(u->next[r] != nullptr && u->next[r]->key - key < 0)
                u = u->next[r]; // go right in list r
            r--; // go down into list r-1
        }
        return u->next[0] != nullptr && u->next[0]->key == key ? u->next[0]->val : -1;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        bool erased = false;
        Node *u = sentinel;
        Node* del;
        int r = h;
        int comp = 0;
        while(r >= 0) {
            while(u->next[r] != nullptr && (comp = u->next[r]->key - key) < 0)
                u = u->next[r];
            if( u->next[r] != nullptr && comp == 0 ) {
                erased = true;
                del = u->next[r];
                u->next[r] = u->next[r]->next[r];
                if( u == sentinel && u->next[r] == nullptr )
                    h--; // skiplist height has gone down
            }
            r--;
        }
        if( erased )
            free(del);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
