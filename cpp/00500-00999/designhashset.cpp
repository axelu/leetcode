
// 705. Design HashSet
// https://leetcode.com/problems/design-hashset/




// using a Skiplist
// https://leetcode.com/problems/design-skiplist/
class MyHashSet {
private:
    struct Node {
        int val;
        int height; // size of next
        Node* next[];
    };

    int h;
    Node* sentinel;
    Node* stack[33];

    Node* newNode(int x, int h) {
        // assuming 8 bytes as size of pointer (64bit architecture)
        Node* node = (Node*)malloc(sizeof(struct Node) + 8 * h);
        node->val = x;
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
    MyHashSet() {
        h = 0;
        sentinel = newNode(-1,33); // max number of levels 33
        stack[0] = sentinel;
        srand(time(nullptr));
    }

    void add(int key) {
       Node *u = sentinel;
        int r = h;
        int comp = 0;
        while(r >= 0) {
            while(u->next[r] != nullptr && (comp = u->next[r]->val - key) < 0)
                u = u->next[r];
            if( u->next[r] != nullptr && comp == 0 ) {
                return;
            }
            stack[r--] = u; // going down, store u
        }
        Node* w = newNode(key,pickHeight());
        while(h < w->height)
            stack[++h] = sentinel; // height increased
        for(int i = 0; i < w->height; i++) {
            w->next[i] = stack[i]->next[i];
            stack[i]->next[i] = w;
        }
    }

    void remove(int key) {
        bool erased = false;
        Node *u = sentinel;
        Node* del;
        int r = h;
        int comp = 0;
        while(r >= 0) {
            while(u->next[r] != nullptr && (comp = u->next[r]->val - key) < 0)
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

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        Node* u = sentinel;
        int r = h;
        while(r >= 0) {
            while(u->next[r] != nullptr && u->next[r]->val - key < 0)
                u = u->next[r]; // go right in list r
            r--; // go down into list r-1
        }
        return u->next[0] != nullptr && u->next[0]->val == key;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
