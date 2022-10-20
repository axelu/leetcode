
// 825. Friends Of Appropriate Ages
// https://leetcode.com/problems/friends-of-appropriate-ages/




/*
 * A Person x will NOT send a friend request to a person y (x != y)
 * if any of the following conditions is true:
 * condition 1:    age[y] <= 0.5 * age[x] + 7
 * condition 2:    age[y] > age[x]
 * condition 3:    age[y] > 100 && age[x] < 100
 * in other words:
 * any person below 15 will not emit any friend request.
 * condition 1 gives us the start
 * condition 2 gives us the end: age[y] <= age[x]
 * condition 3 is meaningless, it is part of condition 2
*/
class Solution {
private:
    // binary search
    int ub(vector<int>& nums, int n, int target) {
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;

        return s;
    }

public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(),ages.end());
        int n = ages.size();

        int ans = 0;

        for(int x: ages) {
            if( x < 15 )
                continue;
            int s = 0.5 * x + 7;

            // binary search upper bound
            int l = ub(ages,n,s);
            if( l == n )
                continue;

            int r = ub(ages,n,x);

            ans += r-l-1;
        }

        return ans;
    }
};
