
// 528. Random Pick with Weight
// https://leetcode.com/problems/random-pick-with-weight/


class Solution {
private:
    vector<int> indices; // basically a prefixSum
public:
    Solution(vector<int>& w) {
        int n = w.size();
        indices.resize(n);
        indices[0] = w[0];
        for(int i = 1; i < n; ++i)
            indices[i] = indices[i-1] + w[i];

        srand(time(nullptr));
    }

    int pickIndex() {
        // random selection of index
        // probablity of picking up a random index must be proportional to its weight
        // last value of indices is = to sum of weights
        int widx = rand() % indices.back();
        auto it = upper_bound(indices.begin(),indices.end(),widx);
        int idx = it - indices.begin();

        return idx;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
