
// 519. Random Flip Matrix
// https://leetcode.com/problems/random-flip-matrix/





class Solution {
private:
    int m,n;
    int k;

    unordered_map<int,int> um;

public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        k = m * n;

        srand(time(nullptr));
    }

    vector<int> flip() {
        int rdm = rand() % k; // random in the range 0 and k-1

        int idx;
        auto f = um.find(rdm);
        if( f != um.end() ) {
            idx = f->second;
            um.erase(f);
        } else {
            idx = rdm;
        }

        // k-1 becomes unreachable in the next round
        // hence swap
        if( rdm != k-1 ) {
            f = um.find(k-1); // skipping erase, it becomes unreachable
            if( f != um.end() ) {
                um[rdm] = f->second;
            } else {
                um[rdm] = k-1;
            }
        }

        --k;

        // translate index to row and col
        int i = idx / n;
        int j = idx % n;
        return {i,j};
    }

    void reset() {
        k = m * n;
        um.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */
