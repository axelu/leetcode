
// 2350. Shortest Impossible Sequence of Rolls
// https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/




class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        int n = rolls.size(); // number of rolls

        // for each 1 <= i <= k record at which index i occurs
        vector<vector<int>> v(k);
        for(int i = 0; i < n; ++i) {
            v[rolls[i]-1].push_back(i);
        }

        // for each k, we have to find a greater one, I want the greatest, if I don't find -> end
        int ans = 1;
        int mx = -1;
        while( true ) {

            int mx_new = -1;
            for(int i = 0; i < k; ++i) {
                vector<int>::iterator f = upper_bound(v[i].begin(),v[i].end(),mx);
                if( f == v[i].end() )
                    return ans;
                mx_new = max(mx_new,*f);
            }
            ++ans;
            mx = mx_new;
        }

        return ans;
    }
};
