
// 1206. Design Skiplist
// https://leetcode.com/problems/design-skiplist/




// inspired by
// http://opendatastructures.org/ods-cpp/4_Skiplists.html
class Skiplist {
private:
    struct Node {
        int val;
        int cnt;
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
        node->cnt = 1;
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
    Skiplist() {
        h = 0;
        sentinel = newNode(-1,33); // max number of levels 33
        stack[0] = sentinel;
        srand(time(nullptr));
    }

    bool search(int target) {
        Node* u = sentinel;
        int r = h;
        while(r >= 0) {
            while(u->next[r] != nullptr && u->next[r]->val - target < 0)
                u = u->next[r]; // go right in list r
            r--; // go down into list r-1
        }
        return u->next[0] != nullptr && u->next[0]->val == target;
    }

    void add(int num) {
        Node *u = sentinel;
        int r = h;
        int comp = 0;
        while(r >= 0) {
            while(u->next[r] != nullptr && (comp = u->next[r]->val - num) < 0)
                u = u->next[r];
            if( u->next[r] != nullptr && comp == 0 ) {
                ++u->next[r]->cnt;
                return;
            }
            stack[r--] = u; // going down, store u
        }
        int t = pickHeight();
        Node* w = newNode(num,t);
        while(h < w->height)
            stack[++h] = sentinel; // height increased
        for(int i = 0; i < w->height; i++) {
            w->next[i] = stack[i]->next[i];
            stack[i]->next[i] = w;
        }
    }

    bool erase(int num) {
        bool erased = false;
        Node *u = sentinel;
        Node* del;
        int r = h;
        int comp = 0;
        while(r >= 0) {
            while(u->next[r] != nullptr && (comp = u->next[r]->val - num) < 0)
                u = u->next[r];
            if( u->next[r] != nullptr && comp == 0 ) {
                if( u->next[r]->cnt != 1 ) {
                    --u->next[r]->cnt;
                    return true;
                }
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
        return erased;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */
