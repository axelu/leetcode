
// 3009. Maximum Number of Intersections on the Chart
// https://leetcode.com/problems/maximum-number-of-intersections-on-the-chart/




class Solution {
public:
    int maxIntersectionCount(vector<int>& y) {
        // 2 <= y.length <= 1e5
        // 1 <= y[i] <= 1e9

        // get all unique y's, worst case 100000 unique y's
        set<int> uniquey;
        for(int x: y)
            uniquey.insert(x);

        // let us assign the  smallest y an index of 0, the next one an index of 2, and so on
        int idx = 0;
        unordered_map<int,int> y_idx; // y, idx
        for(int x: uniquey) {
            y_idx[x] = idx;
            idx += 2;
        }
        /*
        for(auto p: y_idx)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */

        // line sweep
        vector<int> line(idx,0);
        int a = y[0]; // cout << a << " ";  // begin y of a line
        vector<int> idx_cnt(idx,0); // we need to count at each idx how many lines begin and end to avoid double counting
        int b;          // end y of a line
        for(int i = 1; i < y.size(); ++i) {
            // if y[i] is a local min or a local max,
            // then y[i] is the endpoint of our line
            // this works as it is guruanteed that y[i] != y[i + 1]
            if( i == y.size() - 1 ||                   // last element of y has to be the end of a line
                (y[i-1] < y[i] && y[i] > y[i+1]) ||    // local max
                (y[i-1] > y[i] && y[i] < y[i+1]) ) {   // local min

                b = y[i];
                if( a > b ) { // swap
                    int t = a;
                    a = b;
                    b = t;
                }
                // cout << "processing " << a << " -> " << b << endl;
                int idx_a = y_idx[a];
                ++line[idx_a];
                if( i != y.size() - 1 || y[i] != a )
                    ++idx_cnt[idx_a];
                int idx_b = y_idx[b];
                --line[idx_b + 1];
                if( i != y.size() - 1 || y[i] != b )
                    ++idx_cnt[idx_b];

                a = y[i]; // cout << a << " ";
            }
        }
        // cout << endl;

        int ans = 0;
        int cur = 0;
        for(int i = 0; i < idx; ++i) {
            // cout << "line[" << i << "]" << line[i] << " ";
            // cout << "i " << i << " idx_cnt[i] " << idx_cnt[i] << endl;
            cur += line[i];
            //if( i % 2 )
                ans = max(ans, cur - idx_cnt[i]/2);
        }
        // cout << endl;

        return ans;
    }
};
