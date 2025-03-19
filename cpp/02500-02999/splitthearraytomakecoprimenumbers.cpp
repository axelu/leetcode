
// 2584. Split the Array to Make Coprime Products
// https://leetcode.com/problems/split-the-array-to-make-coprime-products/





class Solution {
private:
    // prime factorization fills map with count of prime factors
    void primeFactors(long long n, unordered_map<int,int>& um) {
        // um -> key: prime factor, value: count
        // the number of 2s that divide n
        while(n % 2LL == 0LL) {
            // cout << 2 << " ";
            ++um[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2LL) {
            while(n % i == 0LL) {
                // cout << i << " ";
                ++um[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2LL ) {
            // cout << n << " ";
            ++um[n];
        }

        return;
    }

   void primeFactors(long long n, int idx, unordered_map<int,pair<int,int>>& um) {
        // um -> key: prime factor, value: {smallest idx, largest idx}
        // it is guaranteed, that we are called with increasing i
        // the number of 2s that divide n
        while(n % 2LL == 0LL) {
            // cout << 2 << " ";
            auto p = um.insert({2,{idx,idx}});
            if( !p.second )
                p.first->second.second = idx;
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2LL) {
            while(n % i == 0LL) {
                // cout << i << " ";
                auto p = um.insert({i,{idx,idx}});
                if( !p.second )
                    p.first->second.second = idx;
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2LL ) {
            // cout << n << " ";
            auto p = um.insert({n,{idx,idx}});
            if( !p.second )
                p.first->second.second = idx;
        }

        return;
    }

public:
    int findValidSplit(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e4; 1 <= nums[i] <= 1e6
        if( n == 1 )
            return -1;
        if( nums[0] == 1 )
            return 0;

        // brute force
        // worst case product 1000000^10000, so brute force is out
        /*
        long long left  = 1LL;
        long long right = 1LL;
        for(int i = 0; i < n; ++i)
            right *= (long long)nums[i];

        for(int i = 0; i < n-1; ++i) {
            left  *= (long long)nums[i];
            right /= (long long)nums[i];
            if( gcd(left,right) == 1LL )
                return i;
        }
        return -1;
        */

        // what if we prime factor each element
        // the product of one or more elements would have all their prime factors
        // while we are moving from left to right
        // we are moving the prime factors from left to right
        // if the union of left and right is empty, then gcd would be 1
        // example nums = [4,7,8,15,3,5]
        //        left                 right
        // idx 0  2 2                  2 2 2 3 3 5 5 7
        // idx 1  2 2 7                2 2 2 3 3 5 5
        // idx 2  2 2 2 2 2 7          3 3 5 5
        // ans idx 2


        /*
        // unique prime factors for all numbers 2 - 1000000
        set<int> up;
        for(int i = 2; i < 1000001; ++i) {
            auto v = primeFactors(i);
            for(int f: v)
                up.insert(f);
        }
        cout << up.size() << endl;
        cout << *up.rbegin() << endl;
        // there are 78498 unique prime factors, largest 999983
        */

        // for each prime factor we will record the leftmost and rightmost
        // time of its occurence

        // um => key: prime factor, value: {smallest idx, larget idx}
        unordered_map<int,pair<int,int>> um;
        for(int i = 0; i < n; ++i)
            primeFactors(nums[i], i, um);

        // going from left to right, we record the rightmost idx
        // at which a primefactor in window 0...i exists
        vector<int> rightmost_leftwindow(n,0);
        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 ) {
                if( i > 0 )
                    rightmost_leftwindow[i] = max(rightmost_leftwindow[i-1], i);
                else
                    rightmost_leftwindow[i] = 0;
                continue;
            }
            unordered_map<int,int> pf;
            primeFactors(nums[i], pf);
            int mx = 0;
            for(auto& p: pf)
                mx = max(mx, um[p.first].second);
            if( i > 0 )
                rightmost_leftwindow[i] = max(rightmost_leftwindow[i-1], mx);
            else
                rightmost_leftwindow[i] = mx;
        }
        // going from right to left, we record the leftmost idx
        // at which a primefactor in window i...n-1 exists
        vector<int> lefttmost_rightwindow(n,0);
        for(int i = n-1; i >= 0; --i) {
            if( nums[i] == 1 ) {
                if( i < n-1 )
                    lefttmost_rightwindow[i] = min(lefttmost_rightwindow[i+1], i);
                else
                    lefttmost_rightwindow[i] = n-1;
                continue;
            }
            unordered_map<int,int> pf;
            primeFactors(nums[i], pf);
            int mn = n-1;
            for(auto& p: pf)
                mn = min(mn, um[p.first].first);
            if( i < n-1 )
                lefttmost_rightwindow[i] = min(lefttmost_rightwindow[i+1], mn);
            else
                lefttmost_rightwindow[i] = mn;
        }

        for(int i = 0; i < n-1; ++i)
            if( rightmost_leftwindow[i] == i && lefttmost_rightwindow[i+1] == i+1 )
                return i;

        return -1;
    }
};
