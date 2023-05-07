
// 2033. Minimum Operations to Make a Uni-Value Grid
// https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/



class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        if( m*n == 1 )
            return 0;

        // collect all elements of the grid into a sorted vector
        vector<int> arr(m*n);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                arr[i*n+j] = grid[i][j];
        sort(arr.begin(),arr.end());

        // pair: unique element, left most idx in sorted vector
        vector<pair<int,int>> t;
        t.push_back({arr[0],0});
        for(int i = 1; i < m*n; ++i) {
            if( arr[i-1] != arr[i] ) {
                // the difference between elements
                // must be a multiple of x
                if( (arr[i] - arr[i-1]) % x != 0 )
                    return -1;

                t.push_back({arr[i],i});
            }
        }
        int t_sz = t.size();

        // edge cases
        if( t_sz == 1 ) {           // one unique element
            return 0;
        } else if( t_sz == 2 ) {    // two unique elements
            // right side subtract
            int r = (m*n - t[1].second) * (t[1].first - t[0].first)/x;
            // left side add
            int l = t[1].second * (t[1].first - t[0].first)/x;

            return l < r ? l : r;
        }

        /*
        for(int i = 0; i < t_sz; ++i)
            cout << t[i].first << "," << t[i].second << " ";
        cout << endl;
        */

        // let us calculate what it takes to add x to each unique element
        // to bring it up to the next unique element going left to right
        int add[t_sz];
        add[0] = t[1].second * (t[1].first-t[0].first)/x;
        for(int i = 1; i < t_sz-1; ++i)
            add[i] = add[i-1] + t[i+1].second * (t[i+1].first-t[i].first)/x;

        /*
        cout << "add ";
        for(int i = 0; i < t_sz; ++i)
            cout << i << ":" << add[i] << " ";
        cout << endl;
        */

        // let us calculate what it takes to subtract x from each unique element
        // to bring it down to the next unique element going right to left

        int sub[t_sz];
        sub[t_sz-1] = (m*n - t[t_sz-1].second) * (t[t_sz-1].first-t[t_sz-2].first)/x;
        for(int i = t_sz-2; i >= 1; --i)
            sub[i] = sub[i+1] + (m*n - t[i].second) * (t[i].first-t[i-1].first)/x;

        /*
        cout << "sub ";
        for(int i = 0; i < t_sz; ++i)
            cout << i << ":" << sub[i] << " ";
        cout << endl;
        */

        // now we can find the smallest combination of adding and subtracting
        // to equalize all elements
        // initialize ans to as if we would bring all elements up to the largest element
        //     or bring all elements down to the smallest element respectively
        int ans = min(add[t_sz-2],sub[1]);

        for(int i = 0; i < t_sz - 2; ++i)
            ans = min(ans,add[i]+sub[i+2]);

        return ans;
    }
};
