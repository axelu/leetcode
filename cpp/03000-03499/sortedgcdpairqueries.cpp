
// 3312. Sorted GCD Pair Queries
// https://leetcode.com/problems/sorted-gcd-pair-queries/

// I had come up with the second part, meaning once knowing
// how many times a given GCD occurs, how to process the
// queries by having a prefixSum and binary search.
// However, I could not come up with how to count a given GCD
// other than brute force, and then the other option
// to precalc per value the divisors, then processing from 
// large to small, knowing that each element has to be used in 
// n-1 pairs, if not all are used, pushing the remainder to the 
// next smaller divisor till all are consumed, but the issue
// was with doublecounting, my non-working implementation
// is at the end.
// The clue needed was here:
// https://leetcode.com/problems/sorted-gcd-pair-queries/discuss/5883785/ACTUAL-EXPLANATIONS-and-DRY-RUN-of-what-we-do-and-WHY-WE-DO-IT-THIS-WAY
// which was that one needs to look for multiples, after that it
// became clear how to get to number of occurences of each GCD



class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
         int n = nums.size();

        // with that, our worst case is that we have n * (n-1)/2 pairs => 4999950000 pairs

        // 1 <= nums[i] <= 50000
        // with that though, in reality, and because order does not matter,
        // our worst case is 1249975000 unique pairs
        // also, our GCDs are between 1 and 50000 max only, we just need to know how many of each

        // a given nums[i] can be the GCD if there is a nother number it is a multiple off

        int cnt[50001]; memset(cnt,0,sizeof cnt);
        int mx = 0;
        for(int x: nums) {
            ++cnt[x];
            mx = max(mx, x);
        }

        vector<long long> gcd_pairs(mx+1); // divisor, cnt
        for(int i = mx; i >= 1; --i) { // divisor

            // count us and every multiple
            long long freq = 0LL;
            for(int j = i; j <= mx; j = j + i)
                freq += (long long)cnt[j];

            // how many pairs can we make?
            gcd_pairs[i] = freq * (freq - 1) / 2;

            // we must not doublecount !!!
            for(int j = 2 * i; j <= mx; j = j + i)
                gcd_pairs[i] -= gcd_pairs[j];
        }
        /*
        for(int i = 1; i <= mx; ++i)
            cout << i << ":" << gcd_pairs[i] << " ";
        cout << endl;
        */

        // we now know how many pairs we have per GCD

        vector<long long> prefixSum(mx+1); // zero based index, because 0 is not a divisor
        prefixSum[0] = 0LL;
        for(int i = 1; i <= mx; ++i)
            prefixSum[i] = prefixSum[i-1] + gcd_pairs[i];
        /*
        for(int i = 0; i <= mx; ++i)
            cout << prefixSum[i] << " ";
        cout << endl;
        */

        // binary search to process queries
        // example [4,4,2,1]
        //                   0 1 2 3 4 5
        // we have GCD pairs 1,1,1,2,2,4 when sorted
        // meaning from index 0..2 GCD 1, index 3..4 GCD 2, index 5..5 GCD 4
        // with that our prefixSum will now be as follows
        // 0 1 2 3 4
        // 0 3 5 5 6
        // if we are asked for the GCD at index 4, we look for the 1st position where
        // our prefixSum is greater (upper bound)

        int q_sz = queries.size();
        vector<int> ans(q_sz);

        for(int i = 0; i < q_sz; ++i) {
            long long target = queries[i];

            // returns 'n' if nums[n-1] <= target
            // returns  0  if nums[0] > target
            // binary search upper bound while loop
            // upper bound -> greater than target
            int s = 1;
            int e = mx+1; // n = nums.size()
            int mid;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( target >= prefixSum[mid] )
                    s = mid + 1;
                else
                    e = mid;
            }
            if( s < n && prefixSum[s] <= target )
                ++s;

            ans[i] = s;



        }

        return ans;
    }
};


// not complete and not working attempt

// initialize once
vector<int> divisors[500001]; // sorted set of divisors
bool init = false;


class Solution {
private:
    // int mem[50001][50001];
    /*
    int gcd(int a, int b) {
        if( mem[a][b] != -1 )
            return mem[a][b];
        if (a == 0)
            return b;
        return mem[a][b] = gcd(b % a, a);
    }
    */

    void calc_divisors(int a) {
        // will include 1 as a divisor
        // will include a as a divisor
        if( !divisors[a].empty() )
            return;

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

    // binary search
    int geltt(int a, int target) {

        int n = divisors[a].size();

        // binary search greatest element less than target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( divisors[a][mid] < target )
                s = mid+1;
            else
                e = mid;
        }
        if( (s < n && divisors[a][s] >= target) || s == n )
            --s;

        return s;
    }

public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        if( !init ) {
            init = true;
            divisors[1].push_back(1);
            for(int i = 2; i <= 50000; ++i)
                calc_divisors(i);
        }

        int n = nums.size();

        // with that, our worst case is that we have n * (n-1)/2 pairs => 4999950000 pairs

        // 1 <= nums[i] <= 50000
        // with that though, in reality, and because order does not matter,
        // our worst case is 1249975000 unique pairs
        // also, our GCDs are between 1 and 50000 max only, we just need to know how many of each

        vector<vector<int>> divisors_mul[50001]; // key: divisor value: {val, cnt, idx_divisor}
        // initially the value itself is the greatest divisor
        for(int val: nums)
            divisors_mul[val].push_back({val, n-1, (int)divisors[val].size()-1});


        long long divisors_cnt[50001]; memset(divisors_cnt,0,sizeof divisors_cnt);
        // for(int i = 50000; i >= 1; --i) {
        for(int i = 4; i >= 1; --i) {
            cout << "i " << i << endl;

            int t = divisors_mul[i].size(); cout << "nbr of elements with i as the divisor " << t << endl;
            if( t == 0 )
                continue;

            if( t == 1 ) {
                // we cannot make a pair, move val to its next smallest divisor
                int val = divisors_mul[i][0][0];
                int cnt = divisors_mul[i][0][1];
                int idx_divisor = divisors_mul[i][0][2];

                int nxt_smaller_divisor = divisors[val][idx_divisor-1]; // we should always have a smaller one

                divisors_mul[nxt_smaller_divisor].push_back({val, cnt, idx_divisor -1});
                continue;
            }

            // we can make pairs
            // with each one we make t-1 pairs
            long long cnt = t * (t-1)/2;
            divisors_cnt[i] += cnt;

            // move them
            for(int j = 0; j < t; ++j) {
                int val = divisors_mul[i][j][0];
                int cnt = divisors_mul[i][j][1];
                int idx_divisor = divisors_mul[i][j][2];

                // subtract the number of pairs we made from cnt
                cnt -= (t-1);
                if( cnt > 0 ) {
                    int nxt_smaller_divisor = divisors[val][idx_divisor-1]; // we should always have a smaller one

                    divisors_mul[nxt_smaller_divisor].push_back({val, cnt, idx_divisor -1});
                }
            }


        }

        for(int i = 1; i <= 4; ++i)
            cout << i << ":" << divisors_cnt[i] << " ";
        cout << endl;






        /*
        memset(mem,-1,sizeof mem);
        for(int i = 0; i <=50000; ++i) {
            for(int j = i; j <= 50000; ++j) {
                gcd(i,j);

            }
        }
        */

        return {};
    }
};


