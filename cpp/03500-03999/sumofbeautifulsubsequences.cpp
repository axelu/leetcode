
// 3671. Sum of Beautiful Subsequences
// https://leetcode.com/problems/sum-of-beautiful-subsequences/



// initialize once
vector<int> divisors[70001]; // sorted set of divisors
bool init = false;

class Solution {
private:
    void calc_divisors(int a) {
        // will include 1 as a divisor
        // will include a as a divisor
        // if( !divisors[a].empty() )
        //     return;

        int square_root = (int) sqrt(a) + 1;
        for(int i = 2; i < square_root; ++i) {
            if( a % i == 0 && i*i!= a ) {
                divisors[a].push_back(i);
                divisors[a].push_back(a/i);
            }
            if( a % i == 0 && i*i== a )
                divisors[a].push_back(i);
        }
        divisors[a].push_back(1);
        divisors[a].push_back(a);
        sort(divisors[a].begin(),divisors[a].end());
    }

    // binary search lower_bound
    int lower_bound(vector<int>& nums, int target) {
        int n = nums.size();

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

    const long mod = 1000000007L;

    long sum(vector<long>& bit, int r) {
        long ret = 0L;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = (ret + bit[r]) % mod;
        return ret;
    }

    void add(vector<long>& bit, int idx, long delta) {
        int n = bit.size();
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = (bit[idx] + delta) % mod;
    }

/*
    int count_increasing(int x) {
        // x is key into ss
        // return number of strictly increasing subsequences in ss[x]

        vector<int> uniques = ss[x];
        sort(begin(uniques), end(uniques));
        // remove duplicates
        for(auto it = next(uniques.begin()); it != uniques.end(); ) {
            if( *prev(it) == *it )
                it = uniques.erase(it);
            else
                ++it;
        }

        n = uniques.size();
        bit.assign(n+1, 0);

        long total = 0;
        for(int v : ss[x]) {
            int r = lower_bound(uniques, v) + 1;
            // how many have we seen ending at values
            // less than us?
            long less = sum(r - 1);
            long add_here = (less + 1L) % mod;
            add(r, add_here);
            total = (total + add_here) %mod;
        }

        return total;
    }
*/
public:
    int totalBeauty(vector<int>& nums) {
        if( !init ) {
            init = true;
            divisors[1].push_back(1);
            // for(int i = 2; i <= 70000; ++i)
            //     calc_divisors(i);
        }

        int n = nums.size(); // 1 <- n <= 1e4; 1 <= nums[i] <= 7 * 1e4

        // rephrasing the problem
        // pick a g
        // find all strictly increasing subsequences of nums whose greatest common divisor (GCD) is exactly g

        // step 1 pick a g and extract the subsequence from nums
        //        with all elements being multiples of g
        // step 2 count all strictly increasing subsequences in each
        //        subsequence extracted in step 1 (multiple with g and running sum)

        map<int,vector<int>> ss; // key: x; value: subsequence of nums with multiples of x only
        int mx = 0;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            mx = max(mx, x);
            if( divisors[x].empty() )
                calc_divisors(x);
            for(int j = 0; j < divisors[x].size(); ++j)
                ss[divisors[x][j]].push_back(x);
        }

        /*
        // debug
        for(int i = 0; i < ss[9].size(); ++i)
            cout << ss[9][i] << " ";
        cout << endl;
        */

        long num_inc[70001];memset(num_inc,0,sizeof num_inc);
        for(auto& p: ss) {
            int x = p.first;

            /*
            // debug
            cout << "x " << x << " ss[x]       ";
            for(int i: p.second)
                cout << i << " ";
            cout << endl;
            */

            // extract sorted unique values from our subsequence
            vector<int> uniques = p.second;
            sort(begin(uniques), end(uniques));
            // remove duplicates
            for(auto it = next(uniques.begin()); it != uniques.end(); ) {
                if( *prev(it) == *it )
                    it = uniques.erase(it);
                else
                    ++it;
            }

            /*
            // debug
            cout << "x " << x << " uniques asc ";
            for(int i: uniques)
                cout << i << " ";
            cout << endl;
            */

            int uniques_sz = uniques.size();
            vector<long> bit(uniques_sz, 0);  // binary indexed tree, 0 indexed, point update, range query (sum)

            long runing_total = 0L;
            for(int i = 0; i < p.second.size(); ++i) {
                int val = p.second[i];

                // index of our current val in uniques
                int idx = lower_bound(uniques, val);

                long num_inc_ss = 1L; // 1 because val itself is a subsequence ending at i
                // how many strictly increasing subsequences have we seen ending at values less than us?
                // those we will need to carry
                if( idx > 0 )
                    num_inc_ss = (num_inc_ss + sum(bit, idx-1)) % mod;

                add(bit, idx, num_inc_ss);
                runing_total = (runing_total +  num_inc_ss) %mod;
            }

            num_inc[x] = runing_total;
            // cout << "x " << x << " count " << num_inc[x] << endl;
        }

        // don't double count !!!
        long dp[70001]; memset(dp, 0, sizeof dp);
        for(int x = mx; x >= 1; --x) {
            long num_inc_ss = num_inc[x];
            // we need to discount all higher multiple ss counts
            // as we are looking for the once for gcd
            for(int mulx = 2*x; mulx <= mx; mulx += x) {
                num_inc_ss = num_inc_ss - dp[mulx];
                if( num_inc_ss < 0 )
                    num_inc_ss += mod;
            }
            dp[x] = num_inc_ss;
        }

        long ans = 0L;
        for(int x = 1; x <= mx; ++x) {
            if( dp[x] ) {
                ans = (ans + x * dp[x]) % mod;
            }
        }

        return ans;
    }
};
