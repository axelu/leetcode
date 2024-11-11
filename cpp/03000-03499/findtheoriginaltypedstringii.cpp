
// 3333. Find the Original Typed String II
// https://leetcode.com/problems/find-the-original-typed-string-ii/




class Solution {
private:
    const long mod = 1000000007;

    unordered_map<long,long> mem;

    long rec(vector<int>& bins, int i, int mn, int sum, long suffixProduct[], int suffixSum[]) {
        // cout << "rec i "<< i << " sum " << sum << endl;

        if( i == bins.size() )
            return sum >= mn;

        // shortcut the calculation when we have reached mn
        if( sum >= mn )
            return suffixProduct[i];

        // if we would take all of us and after us and we cannot reach mn,
        // then there is no solution
        if( sum + suffixSum[i] < mn )
            return 0L;


        // cout << mn - sum << endl;

        long key = ((long)i<<18) + (long)sum;
        auto f = mem.find(key);
        if( f != mem.end() ) {
            // cout << "hit" << endl;
            return f->second;
        }



        long ret = 0L;

        // we could also figure out based on the mn-sum and knowing how many
        // objects are after us, how many we need to take minimum from our bucket
        // so that we don't start at 0 if we could know that we need to pick > 0
        // from our current bucket
        // at this point sum < mn, but we know that
        // sum + suffixSum[i] >= mn, meaning we can make it

        int t = mn - sum; // we still need t to reach mn
        if( t - suffixSum[i+1] >= bins[i] )
            return mem[key] = rec(bins, i+1, mn, sum + bins[i], suffixProduct, suffixSum);

        int j_min = max(0,t - suffixSum[i+1]);
        // int j = 0;
        // for(; j <= bins[i]; ++j) {
        for(int j = bins[i]; j >= j_min; --j) {
            ret = (ret + rec(bins, i+1, mn, sum + j, suffixProduct, suffixSum)) % mod;

        }

        return mem[key] = ret;
    }


    unordered_map<long,long> mem2;

    long rec2(vector<int>& bins, int i, int mx, int sum) {
        cout << "rec2 i " << i << " sum " << sum << endl;
        if( sum == mx )
            return 1L;

        if( sum > mx )
            return 0L;

        if( i == bins.size() - 1 ) {
            int t = mx - sum;
            return min(t+1,bins[i]+1);
        }

        long key = ((long)i<<18) + (long)sum;
        auto f = mem2.find(key);
        if( f != mem2.end() ) {
            // cout << "hit" << endl;
            return f->second;
        }


        long ret = 0L;

        for(int j = 0; j <= bins[i] && sum + j <= sum + mx; ++j) {
            ret = (ret + rec2(bins, i+1, mx, sum+j)) % mod;
        }

        return mem2[key] = ret;
    }

public:
    int possibleStringCount(string word, int k) {
        int n = word.size();
        if( n < k )
            return 0;
        if( n == 1 || n == k )
            return 1;

        // each substring with consecutive letters is a bucket aka bin
        // if there are cnt consecutive letters in a given substring, then
        //     our bin can hold 0...(cnt-1) of those
        // the sum of the letters must be >=

        // example
        // abbbcdeeeefghiii n = 16
        //  ---  ----   ---
        // we have 3 buckets to hold 0..2, 0..3 and 0..2 respectively
        // so the shortest string would be 16 - (2 + 3 + 2) = 9
        // meaning we keep only 1 of the chars of each char in each bucket (we need to keep at minimum 1)
        // ab  cde   fghi   n = 9  respectively abcdefghi
        // let k be 11
        // that means the sum of our 3 buckets has to be at least 2
        //        bucket 0    bucket 1    bucket 3
        //         0..2        0..3        0..2
        // ----------------------------------------------
        //         0           0           0         not valid
        //         0           0           1         not valid
        //         0           0           2         valid
        //         0           1           0         not valid
        //         0           1           1         valid
        //         0           1           2         valid
        //         0           2           0         valid
        //         0           2           1         valid
        //         0           2           2         valid
        //         0           3           0         valid
        //         0           3           1         valid
        //         0           3           2         valid
        //         1           0           0         not valid
        //         1           0           1         valid
        //         1           0           2         valid
        //         1           1           0         valid
        //         1           1           1         valid
        //         1           1           2         valid
        //         1           2           0         valid
        //         1           2           1         valid
        //         1           2           2         valid
        //         1           3           0         valid
        //         1           3           1         valid
        //         1           3           2         valid
        //         2           0           0         valid
        //         2           0           1         valid
        //         2           0           2         valid
        //         2           1           0         valid
        //         2           1           1         valid
        //         2           1           2         valid
        //         2           2           0         valid
        //         2           2           1         valid
        //         2           2           2         valid
        //         2           3           0         valid
        //         2           3           1         valid
        //         2           3           2         valid
        // anwer = 32
        // let k <= 9  => answer = 36
        // meaning that the problem is not well defined as it does not talk to this in its constraints

        // 1 <= n <= 500000
        // at max we have 250000 buckets 0..     1 char, our k_min would be 250000
        // at min we have      1 bucket  0..249999 char, our k_min would be      1


        int sum_consecutive = 0;
        vector<int> bins;
        int consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( word[i] != word[i-1] ) {
                if( consecutive > 1 ) {
                    sum_consecutive += (consecutive - 1);
                    bins.push_back(consecutive - 1);
                }
                consecutive = 1;
            } else {
                ++consecutive;
            }
        }
        // finish up
        if( consecutive > 1 ) {
            bins.push_back(consecutive - 1);
            sum_consecutive += (consecutive - 1);
        }

        k = max(k, n - sum_consecutive);

        // if we leave 1 of the consecutive chars each, the string length = n - sum_consecutive long
        // so the min sum of our bins must then be k - (n - sum_consecutive)
        int mn = k - (n - sum_consecutive);

        // if mn == 0 then
        //  ans = 1
        //  for x in buckets ans = ans * (x+1)

        // calc solution from buckets backwards
        // so that our rec reaches mn, we can shortcut the calculation

        long suffixProduct[bins.size()];memset(suffixProduct,0,sizeof suffixProduct);
        suffixProduct[bins.size()-1] = bins.back()+1;
        int suffixSum[bins.size()+1];memset(suffixSum,0,sizeof suffixSum);
        suffixSum[bins.size()] = 0;
        suffixSum[bins.size()-1] = bins.back();

        for(int i = bins.size()-2; i >= 0; --i) {
            suffixProduct[i] = (suffixProduct[i+1] * (long)(bins[i]+1)) % mod;
            suffixSum[i] = suffixSum[i+1] + bins[i];
        }

        // cout << "suffixProduct[0] " << suffixProduct[0] << endl;
        // cout << "nbr bins " << bins.size() << endl;
        // cout << "mn " << mn << endl;

        if( mn == 0 )
            return suffixProduct[0];
        if( mn == 1 ) {
            return suffixProduct[0] - 1 < 0 ? 0 : suffixProduct[0] - 1;
        }

        int mx = mn - 1;
        // cout << "mx " << mx << endl;

        long ans;

        /*
        // top down using max number of chars up to which we have no solution, meaning we have to pick at minimum max+1 across all bins
        long a = rec2(bins, 0, mx, 0);
        cout << "a " << a << endl;
        ans = suffixProduct[0] - a;
        if( ans < 0 )
            ans += mod;

        return ans;
        */

        // bottom up
        // buckets aka bins from right to left
        // mx from 0 to mx, cummulative aka prefixSum
        long _pre[mx+1];long * pre = _pre;
        long _cur[mx+1];long * cur = _cur;

        // keep a prefixSum also for fast lookup
        pre[0] = 1L; // always, same for cur
        cur[0] = 1L;
        for(int j = 1; j <= mx; ++j)
            pre[j] = pre[j-1] + min(j+1, bins[bins.size()-1]+1);

        /*
        // debug
        for(int j = 0; j <= mx; ++j)
            cout << j << ":" << pre[j] << " ";
        cout << endl;
        */

        for(int i = bins.size()-2; i >= 0; --i) {
            for(int j = 1; j <= mx; ++j) {
                int o = j - bins[i];
                int offset = o > 0 ? pre[o-1]: 0;
                cur[j] = (cur[j-1] + pre[j] - offset) % mod;
                if( cur[j] < 0 )
                    cur[j] += mod;
            }

            /*
            cout << "i " << i << endl;
            for(int j = 0; j <= mx; ++j)
                cout << j << ":" << cur[j] << " ";
            cout << endl;
            */

            // swap
            long * t = pre;
            pre = cur;
            cur = t;

        }
        // ans in pre[mx] - pre[mx-1]
        long b = pre[mx] - pre[mx-1];
        if( b < 0 )
            b += mod;
        // cout << "b " << b << endl;

        ans = suffixProduct[0] - b;
        if( ans < 0 )
            ans += mod;

        return ans;


        // top down using min number of chars we have to pick acrcoss all bins
        // return rec(bins, 0, mn, 0, suffixProduct, suffixSum);
    }
};
