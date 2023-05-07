
// 2672. Number of Adjacent Elements With the Same Color
// https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color/




class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        int q_sz = queries.size();
        vector<int> ans(q_sz);

        vector<int> v(n,0);

        int t = 0; // running answer
        for(int i = 0; i < q_sz; ++i) {
            int idx = queries[i][0];
            int clr = queries[i][1];

            // before change
            if( idx - 1 >= 0 && v[idx-1] != 0 )
                if( v[idx-1] == v[idx] )
                    --t;
             if( idx + 1 < n && v[idx] != 0 )
                if( v[idx] == v[idx+1] )
                    --t;

            // change
            v[idx] = clr;

            // after change
            if( idx - 1 >= 0 && v[idx-1] != 0 )
                if( v[idx-1] == v[idx] )
                    ++t;
             if( idx + 1 < n )
                if( v[idx] == v[idx+1] )
                    ++t;

            ans[i] = t;
        }

        return ans;
    }
};
