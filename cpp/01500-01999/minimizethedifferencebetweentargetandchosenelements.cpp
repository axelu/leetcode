
// 1981. Minimize the Difference Between Target and Chosen Elements
// https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/





class Solution {
private:
    int m,n,mn,mx,ans;

    void rec(vector<set<int>>& mat, int row, int currSum, int target, int seen[]) {
        // cout << "rec row " << row << " currSum " << currSum << endl;
        if( row == m-1 ) {
            // currSum is less than target
            int diff = target-currSum;
            auto f = mat[row].lower_bound(diff);
            if( f == mat[row].end() ) {
                ans = min(ans,target-(currSum + *(mat[row].rbegin())));
            } else if( *f != diff ) {
                if( f == mat[row].begin() ) {
                    ans = min(ans,currSum + *(mat[row].begin()) - target);
                } else {
                    ans = min({ans,currSum + *f - target,target - (currSum + *(prev(f)))});
                }
            } else {
                ans = 0;
            }
            return;
        }


        int seenIdx = row*mx+currSum;
        if( seen[seenIdx] ) {
            // cout << "hit" << endl;
            return;
        }

        seen[seenIdx] = 1;


        int sum;
        for(auto it = mat[row].begin(); it != mat[row].end(); ++it) {
            sum = currSum + *it;
            if( sum >= target ) {
                for(int i = row+1; i < m; ++i) {
                    sum += *(mat[i].begin());
                }
                ans = min(ans,sum-target);
                return;
            } else {
                rec(mat,row+1,sum,target,seen);
                if( ans == 0 )
                    return;
            }
        }
    }


public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        m = mat.size();
        n = mat[0].size();

        vector<set<int>> v(m);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                v[i].insert(mat[i][j]);

        mn = 0, mx = 0;
        for(int i = 0; i < m; ++i) {
            mn += *(v[i].begin());
            mx += *(v[i].rbegin());
        }
        if( mn >= target )
            return mn-target;
        if( mx <= target )
            return target-mx;

        if( n == 1 )
            return abs(mn-target);

        if( m == 1 ) {
            auto f = v[0].lower_bound(target);
            if( f == v[0].end() ) {
                return target - *(v[0].rbegin());
            } else if( *f != target ) {
                if( f != v[0].begin() )
                    return min(*f - target,target-*(prev(f)));
                else
                    return *f - target;
            } else {
                return 0;
            }
        }

        // our solution space is between mn and mx
        // cout << "mn " << mn << " mx " << mx << endl;

        int seen[m*mx];memset(seen,0,sizeof seen);

        ans = INT_MAX;
        rec(v,0,0,target,seen);

        return ans;
    }
};
