
// 2818. Apply Operations to Maximize Score
// https://leetcode.com/problems/apply-operations-to-maximize-score/





/* number of non-empty arryas for an array of length n: n * (n + 1)/2
 * brute force not feasiable
 * let us look at each element and determine its prime score
 * let us determine for which subarrays to its left and right it is the highest prime score
 * we then know how often we can use it as a factor
 * if we sort the elements by there value and know how often we can use that element
 * ensure we don't double count, same concept as
 * 2281. Sum of Total Strength of Wizards
 * https://leetcode.com/problems/sum-of-total-strength-of-wizards/
 * but the added challenge is:
 *    Choose an element x of nums[l, ..., r] with the highest prime score.
 *    If multiple such elements exist, choose the one with the smallest index.
 *    But that one may not be the larger nums[i], but we want the larger nums[i]
 * so....
 * example
 * index      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
 * nums       2  2  4  2  2  6  2  2  4  2  2  4  2  2  4  2  2 15
 * primescore 1  1  2  1  1  2  1  1  2  1  1  2  1  1  2  1  1  2
 *
 * to the left:  if we encounter a position at which the prime score is equal or greater, we stop
 * to the right: if we encounter a position at which the prime score is greater, we stop
 *
 * we can then greedily go starting with the element and use it max times,
 * then go to the next use it max times till we have have used them k times
 */

// initialize once
int primescore[100001];
bool init = false;

class Solution {
private:
    // prime factorization
    int primeFactors(int n) {
        // returns number of distinct prime factors
        unordered_set<int> us;

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            us.insert(2);
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                us.insert(i);
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            us.insert(n);
        }

        return us.size();
    }

    const long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

public:
    int maximumScore(vector<int>& nums, int k) {
        // 1 <= nums[i] <= 1e5
        if( !init ) {
            init = true;
            primescore[1] = 0;
            for(int i = 2; i <= 100000; ++i)
                primescore[i] = primeFactors(i);
        }

        int n = nums.size();
        if( n == 1 )
            return nums[0];

        // get the first index to the right j-1 with j > i where nums_primescore[j].first > nums_primescore[i].first.
        stack<pair<int,int>> stck; // primescore, index
        int r[n];
        for(int i = n-1; i >= 0; --i) {
            while( !stck.empty() && stck.top().first <= primescore[nums[i]] )
                stck.pop();

            if( stck.empty() )
                r[i] = n-1;
            else
                r[i] = stck.top().second - 1;

            stck.push({primescore[nums[i]],i});
        }
        // clear the stck for reuse
        while( !stck.empty() )
            stck.pop();

        // get the first index to the left j+1 with j < i where nums_primescore[j].first >= nums_primescore[i].first
        int l[n];
        for(int i = 0; i < n; ++i) {
            while( !stck.empty() && stck.top().first < primescore[nums[i]] )
                stck.pop();

            if( stck.empty() )
                l[i] = 0;
            else
                l[i] = stck.top().second + 1;

            stck.push({primescore[nums[i]],i});
        }

        vector<pair<int,int>> nums_index(n);
        for(int i = 0; i < n; ++i)
            nums_index[i] = {nums[i],i};
        sort(nums_index.begin(),nums_index.end(),[](const pair<int,int>& a, const pair<int,int>& b){
           return a.first > b.first;
        });

        long ans = 1L;
        for(int j = 0; j < n && k > 0; ++j) {

            int x = nums_index[j].first;
            int i = nums_index[j].second;
            // how many subarrays can we form around x
            long L = i - l[i] + 1;
            long R = r[i] - i + 1;

            long number_subarrays = L * R;
            number_subarrays = min((long)k, number_subarrays);
            k = k - number_subarrays;

            long f = modular_pow(x, number_subarrays);
            ans = (ans * f) % mod;
        }

        return ans;
    }
};
