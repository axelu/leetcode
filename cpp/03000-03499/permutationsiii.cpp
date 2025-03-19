
// 3437. Permutations III
// https://leetcode.com/problems/permutations-iii/





class Solution {
private:
    vector<vector<int>> ans;
    int n;

    void rec(int pos, int state, bool pre_even, vector<int>& t) {
        if( pos == n ) {
            ans.push_back(t);
            return;
        }

        for(int i = 1; i <= n; ++i) {
            if( i % 2 == !pre_even )
                continue;
            if( state & (1<<(i-1)) )
                continue;

            state |= (1<<(i-1));
            t.push_back(i);

            rec(pos+1,state,!pre_even,t);

            // backtrack
            t.pop_back();
            state &= ~(1<<(i-1));
        }

        return;
    }

public:
    vector<vector<int>> permute(int n) {
        // 1 <= n <= 10

       this->n = n;

        vector<int> t;
        for(int i = 1; i <= n; ++i) {
            int state = 1<<(i-1);
            bool even = !(i % 2);
            t.push_back(i);
            rec(1, state, even, t);
            // backtrack
            t.pop_back();
        }

        return ans;
    }
};
