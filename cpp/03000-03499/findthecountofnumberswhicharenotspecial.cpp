
// 3233. Find the Count of Numbers Which Are Not Special
// https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/




/* 4, 9, 25 49, 121, ...
 * 2, 3,  5, 7,  11, ...
 * we can see that the special numbers are squares of primes
 * constraint: 1 <= l <= r <= 1e9
 *
 */
bool init = false;
vector<int> specials;
int n;

class Solution {
private:
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

    int lower_bound(vector<int>& nums, int target) {
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

    int gelttoret(vector<int>& nums, int target) {
       // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s] > target) || s == n )
            --s;

        return s;
    }


public:
    int nonSpecialCount(int l, int r) {
        // 1 <= l <= r <= 1e9

        if( !init ) {
            init = true;
            int i = 2;
            while( i * i <= 1e9 ) {
                if( isPrime(i) )
                    specials.push_back(i*i);
                ++i;
            }
            n = specials.size();
        }

        int lgt = r - l + 1; // numbers between l and r inclusive

        // how many specials between l and r inclusive?
        int lb = lower_bound(specials, l);
        if( lb == n )
            return lgt;
        if( specials[lb] > r )
            return lgt;

        int b = gelttoret(specials, r);

        return lgt - (b - lb + 1);
    }
};
