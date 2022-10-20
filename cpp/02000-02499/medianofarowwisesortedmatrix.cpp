
// 2387. Median of a Row Wise Sorted Matrix
// https://leetcode.com/problems/median-of-a-row-wise-sorted-matrix/



class Solution {
private:
    vector<int> merge(vector<int>& a, vector<int>& b) {
        int i = 0, j = 0, k = 0;
        vector<int> res(a.size()+b.size());
        while( i < a.size() && j < b.size() ) {
            if( a[i] < b[j] ) {
                res[k] = a[i];
                ++i;
            } else {
                res[k] = b[j];
                ++j;
            }
            ++k;
        }
        while( i < a.size() ) {
            res[k] = a[i];
            ++i;
            ++k;
        }
        while( j < b.size() ) {
            res[k] = b[j];
            ++j;
            ++k;
        }

        return res;        
    }
       
    // binary search lower bound
    int search2(vector<int>& nums, int n, int target) {
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;
        return s;
    }
    
    // binary search greatest element less than target or equal target
    int search1(int s, int e, vector<vector<int>>& grid, int n, int m) {
        if( s > e )
            return -1;
                
        int target = (m*n)/2;  // count of elements to the left [and right] of median
        
        int mid = s + ((e-s)/2);
        
        // solve
        bool f = false;
        int cnt = 0;            // count of elements to the left of mid
        for(auto& nums: grid) {
            int t = search2(nums,n,mid);
            if( t != n && nums[t] == mid )
                f = true;
            cnt += t;
        }
        
        if( cnt == target && f )
            return mid;
        
        if( cnt == target && !f )
            return search1(mid+1,e,grid,n,m);
        
        if( cnt < target && f ) {
            // can we do better?
            int t = search1(mid+1,e,grid,n,m);
            return t != -1 ? t : mid;
        }

        if( cnt < target && !f )
            return search1(mid+1,e,grid,n,m);
        
        return search1(s,mid-1,grid,n,m);
    }
    
public:
    int matrixMedian(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if( m == 1 )
            return grid[0][n/2];
        
        /*
        // merge
        // passes all test cases but took too long
        vector<int> a = grid[0];
        for(int i = 1; i < m; ++i)
            a = merge(a,grid[i]);
        
        return a[(m*n)/2];
        */
        
        // we know that we have n*m elements, n*m = odd
        // we know our answer will be the (n*m)/2 th element if we sort them all
        // we know 1 <= grid[i][j] <= 10^6
        // so we could binary search [1,10^6] inclusive
        // and count numbers to the left of it, depending on the result
        // we search higher or lower
        
        return search1(0,1000000,grid,n,m);
    }
};


