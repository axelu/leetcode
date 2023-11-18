
// 2702. Minimum Operations to Make Numbers Non-positive
// https://leetcode.com/problems/minimum-operations-to-make-numbers-non-positive/





class Solution {
private:

    // binary search
    int search2(int i, long x, long y, int s, int e, int max_steps) {
        if( s > e )
            return -1;

        long mid = s + ((e-s)/2);
        long b = (mid * x) + ((max_steps-mid) * y);
        if( b >= i ) {
            // can we do better?
            int t = search2(i,x,y,s,mid-1,max_steps);
            return t != -1 ? t : mid;
        }

        return search2(i,x,y,mid+1,e,max_steps);
    }

    bool solve(vector<int>& nums, int x, int y, int max_steps) {

        int k = max_steps; // times we have x at our disposal

        for(int i: nums) {
            // do we get away with using only y
            long a = y * (long)max_steps; // integer overflow potential
            if( a >= i )
                continue;

            // we need to utilize x
            if( k == 0 )
                return false;

            // lets find the minimum number of times we have to use x
            int mn_x = search2(i,x,y,1,k,max_steps); // cout << "mn_x " << mn_x << endl;
            if( mn_x == -1 )
                return false;

            k = k - mn_x;
        }

        return true;
    }

    // binary search
    int search(vector<int>& nums, int x, int y, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(nums,x,y,mid);
        if( f ) {
            // can we do better?
            int t = search(nums,x,y,s,mid-1);
            return t != -1 ? t : mid;
        }

        return search(nums,x,y,mid+1,e);
    }


public:
    int minOperations(vector<int>& nums, int x, int y) {
        int n = nums.size();

        // y < x

        /*
        // brute force
        priority_queue<int> pq(nums.begin(),nums.end());
        int target = 0;

        int ans = 0;
        while( pq.top() > target ) {
            ++ans;
            int a = pq.top();
            pq.pop();
            a = a - (x-y);
            pq.push(a);
            target += y;
        }

        return ans;
        */

        return search(nums,x,y,1,1000000000);
    }
};
