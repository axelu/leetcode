
// 2226. Maximum Candies Allocated to K Children
// https://leetcode.com/problems/maximum-candies-allocated-to-k-children/



class Solution {
private:
    bool solve(vector<int>& candies, int d, long long k) {

        long long t = 0;

        for(int& x: candies) {
            t += x/d;
            if( t >= k )
                return true;
        }

        return false;
    }

    // binary search
    int search(vector<int>& candies, long long k, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(candies,mid,k);
        if( f ) {
            // can we do better?
            int t = search(candies,k,mid+1,e);
            return t != -1 ? t : mid;
        }
        return search(candies,k,s,mid-1);
    }

public:
    int maximumCandies(vector<int>& candies, long long k) {
        // sum of candies <  k        => 0
        // sum of candies == k        => 1
        // sum of candies / k >= min  => min

        long long sum = 0;
        int mn = 10000001;

        for(int& x: candies) {
            mn = min(mn,x);
            sum += x;
        }

        if( sum < k )
            return 0;
        if( sum == k )
            return 1;

        // our answer is between [1,sum/k] inclusive
        return search(candies,k,1,sum/k);
    }
};
