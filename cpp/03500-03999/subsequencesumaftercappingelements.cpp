
// 3685. Subsequence Sum After Capping Elements
// https://leetcode.com/problems/subsequence-sum-after-capping-elements/


// while this solution passes, it is slow
// idea to improve: in our loop instead of decrementing x, we could
// increment x from 1..n
// then the moment we know we can make k with the uncapped elements in nums
// we know the rest of the answer will be true

class Solution {
private:
    int lower_bound(vector<int>& nums, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
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

    set<int> seen;

    bool rec(vector<int>& nums, int n, int pos, int k, int i, int x) {
        // cout << "rec pos " << pos << " k " << k << endl;
        if( k == 0 )
            return true;
        if( pos == n )
            return false;

        // we have a choice
        //     don't pick the element at pos OR
        //     pick element at pos if we can

        int val = nums[pos];
        if( pos >= i )
            val = x;

        if( val > k ) // anything after us is equal or greater us
            return false;

        // pos == i
        // we don't need to go any further!
        // we know we can make only multiples of x from here on out
        // we can make 1..(n-pos) multiples of x
        // if k is a multiple of x and we have enough x ( n-i >= k / x )
        // then we know we can make k 
        if( pos == i ) {
            if( k % x != 0 )
                return false;

            if( n-i >= k / x )
                return true;

            return false;
        }

        int key = (pos<<12) + k;
        if( !seen.insert(key).second )
            return false;

        if( rec(nums, n, pos+1, k, i, x) )
            return true;

        return rec(nums, n, pos+1, k - val, i, x);
    }

    // set<int> tt1[4001];
    bool a[4001][4001];

    void rec2(vector<int>& nums, int n, int pos, int k) {
        // cout << "rec pos " << pos << " k " << k << endl;
        if( k > 4000 )
            return;

        if( pos == n ) {
            a[pos][k] = true;
            return;
        }

        // we have a choice
        //     don't pick the element at pos OR
        //     pick element at pos if we can

        if( a[pos][k] )
            return;
        a[pos][k] = true;

        rec2(nums, n, pos+1, k);
        rec2(nums, n, pos+1, k + nums[pos]);

        return;
    }




public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        // 1 <= n == nums.length <= 4000
        // 1 <= nums[i] <= n
        // 1 <= k <= 4000

        int n = nums.size(); // cout << "n " << n << endl;

        vector<bool> ans(n); // default false

        sort(begin(nums), end(nums));
        /*
        for(int i = 0; i < n; ++i)
            cout << nums[i] << " ";
        cout << endl;
        */

        int prefixSum[4001];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        // cout << "original sum " << prefixSum[n] << endl;
        if( prefixSum[n] < k )
            return ans;

        // debug
        // rec(nums, n, 0, k, 76, 77);
        // bool tt1 = rec(nums, n, 0, k, 3, 2); cout << tt1 << endl;
        // return {};

        // for each position calculate the subsequence sums up to 4000 we could make
        memset(a, false, sizeof a);
        rec2(nums, n, 0, 0);

        // debug
        /*
        for(int i = 0; i <= min(4000, prefixSum[n]); ++i) {
            cout << i << " ";
            for(int j = 1; j <= n; ++j) {
                cout << a[j][i] << " ";
            }
            cout << endl;
        }
        */

        int prev_i = n-1;
        for(int x = n; x >= 1; --x) {
            // cout << "x " << x << endl;
            // our array is sorted ascending
            // we will cap at x
            // let as find the left most index i 
            //    where nums[i] >= x
            // example
            //    let x be 3
            // 5           x x
            // 4         x
            // 3     x x
            //   --------------
            // 2   x
            // 1 x
            //   0 1 2 3 4 5 6
            // in our exmple i = 2
            // which divides our array into left 0..1 and right 2..6

            int i = lower_bound(nums, prev_i + 1, x); // cout << "  i " << i << endl;

            // if i == n : all elements smaller x, we only have left
            // if i == 0 : all elements equal or greter x, we only have right

            // early determination
            // if the total we can make < k then there is no answer
            // if k is a multiple of x and we have enough x ( n-i >= k / x )
            // then we know we can make k
             
            if( prefixSum[i] + ((n-i) * x) == k ) {
                ans[x-1] = true;
            
            } else if( prefixSum[i] + ((n-i) * x) > k ) { 
                
                if( k % x == 0 &&  n-i >= k / x ) {
                        ans[x-1] = true;

                } else {
                    // cout << "  calling rec i " << i << endl;
                    // seen.clear();
                    // ans[x-1] = rec(nums, n, 0, k, i, x);

                    int f = n-i; // number times we can pick x 0..f
                    for(int j = 0; j <= f && j*x < k; ++j) {
                        int sh = j * x;     
                        int fh = k - sh;    
                        if( a[i][fh] ) {
                            ans[x-1] = true;
                            break;
                        }
                    }
                }
            }
        }

        return ans;
    }
};



// passes 745/794 test cases as of 9/16/2025, then TLE
// test case 746 also locally times out


class Solution {
private:
    int lower_bound(vector<int>& nums, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
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

    set<int> seen;

    bool rec(vector<int>& nums, int n, int pos, int k, int i, int x) {
        // cout << "rec pos " << pos << " k " << k << endl;
        if( k == 0 )
            return true;
        if( pos == n )
            return false;

        // we have a choice
        //     don't pick the element at pos OR
        //     pick element at pos if we can

        int val = nums[pos];
        if( pos >= i )
            val = x;

        if( val > k ) // anything after us is equal or greater us
            return false;

        // pos == i
        // we don't need to go any further!
        // we know we can make only multiples of x from here on out
        // we can make 1..(n-pos) multiples of x
        // if k is a multiple of x and we have enough x ( n-i >= k / x )
        // then we know we can make k
        if( pos == i ) {
            if( k % x != 0 )
                return false;

            if( n-i >= k / x )
                return true;

            return false;
        }

        int key = (pos<<12) + k;
        if( !seen.insert(key).second )
            return false;

        if( rec(nums, n, pos+1, k, i, x) )
            return true;

        return rec(nums, n, pos+1, k - val, i, x);
    }

public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        // 1 <= n == nums.length <= 4000
        // 1 <= nums[i] <= n
        // 1 <= k <= 4000

        int n = nums.size(); // cout << "n " << n << endl;

        vector<bool> ans(n); // default false

        sort(begin(nums), end(nums));

        int prefixSum[4001];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        // cout << "original sum " << prefixSum[n] << endl;
        if( prefixSum[n] < k )
            return ans;


        // debug
        // rec(nums, n, 0, k, 76, 77);
        // bool tt1 = rec(nums, n, 0, k, 3, 2); cout << tt1 << endl;
        // return {};


        int prev_i = n-1;
        for(int x = n; x >= 1; --x) {
            // cout << "x " << x << endl;
            // our array is sorted ascending
            // we will cap at x
            // let as find the left most index i
            //    where nums[i] >= x
            // example
            //    let x be 3
            // 5           x x
            // 4         x
            // 3     x x
            //   --------------
            // 2   x
            // 1 x
            //   0 1 2 3 4 5 6
            // in our exmple i = 2
            // which divides our array into left 0..1 and right 2..6

            int i = lower_bound(nums, prev_i + 1, x); // TODO we can set n to prior i+1
            // if i == n : all elements smaller x, we only have left
            // if i == 0 : all elements equal or greter x, we only have right

            // early determination
            // if the total we can make < k then there is no answer
            // if k is a multiple of x and we have enough x ( n-i >= k / x )
            // then we know we can make k

            if( prefixSum[i] + ((n-i) * x) == k ) {
                ans[x-1] = true;

            } else if( prefixSum[i] + ((n-i) * x) > k ) {
                if( k % x == 0 ) {
                    if( n-i >= k / x ) {
                        ans[x-1] = true;
                    } else {
                        // cout << "  calling rec i " << i << endl;
                        seen.clear();
                        ans[x-1] = rec(nums, n, 0, k, i, x);
                    }
                } else {
                    // cout << "  calling rec i " << i << endl;
                    seen.clear();
                    ans[x-1] = rec(nums, n, 0, k, i, x);
                }
            }
        }

        return ans;
    }
};
