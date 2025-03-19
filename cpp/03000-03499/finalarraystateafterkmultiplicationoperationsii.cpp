
// 3266. Final Srray State After K Multiplication Operations II
// https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/






/* example [2,1,3,5,6], k = 5, multiplier = 2
 *     0    2  x1   3   5   6  <- original state
 *    -----------------------
 *     1   x2   2   3   5   6
 *     2    4  x2   3   5   6
 *     3    4   4  x3   5   6
 *     4   x4   4   6   5   6
 *     5    8  x4   6   5   6  <- at this step our min * multiplier (4 * 2) > max (6), so the cycle takes 5 steps
 *     6    8   8   6  x5   6
 *     7    8   8  x6  10   6
 *     8    8   8  12  10  x6
 *     9   x8   8  12  10  12
 *    10   16  x8  12  10  12  <- cycle end
 *    11   16  16  12 x10  12
 *    12   16  16 x12  20  12
 *    13   16  16  24  20 x12
 *    14  x16  16  24  20  24
 *    15   32 x16  24  20  24  <- cycle end
 *    16   32  32  24 x20  24
 *    17
 *
 * worst case
 *     multiplier = 1e6
 *     nums[i] = 1e9
 *     k = 1e9
 *     val = 1e24 1000000000000000000000000
 *     ULLONG_MAX 18446744073709551615
 */
class Solution {
private:
    const long mod = 1000000007L;

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

    // binary search
    int search(long val, int s, int e, long target, long multiplier) {
        if( s > e )
            return -1;

        long mid = s + ((e-s)/2);
        auto exp = pow(multiplier, mid);
        if( exp >= target ) {
            // can we do better?
            int t = search(val, s, mid-1, target, multiplier);
            return t != -1 ? t : mid;
        }
        long val_new = val * exp;
        if( val_new >= target ) {
            // can we do better?
            int t = search(val, s, mid-1, target, multiplier);
            return t != -1 ? t : mid;
        }

        return search(val, mid+1, e, target, multiplier);
    }

public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        if( multiplier == 1 )
            return nums;

        int n = nums.size();
        if( n == 1 ) {
            int aval = ((long)nums[0] * modular_pow(multiplier,k)) % mod;
            return {aval};
        }

        // we need t ofigure out how many times we would multiply
        // each element of nums without doing it k times, as 1 <= k <= 1e9
        // there comes a time when the cycle repeats, meaning when
        // nums_min * multiplier > nums_max

        auto mx = max_element(begin(nums), end(nums));

        // array<int,3> value, pos in nums, number of times multiplied

        auto cmp = [multiplier](const array<int,3>& a, const array<int,3>& b) {
            long aval = (long)a[0];
            if( a[2] > 0 )
                // aval *= (long)multiplier * (long)a[2];
                aval *= pow(multiplier,a[2]);

            long bval = (long)b[0];
            if( b[2] > 0 )
                // bval *= (long)multiplier * (long)b[2];
                bval *= pow(multiplier,b[2]);

            if( aval > bval ) {
                return true;
            } else if( aval == bval ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; ++i)
            pq.push({nums[i], i, 0});


        while( k > 0 ) {

            auto a = pq.top();
            pq.pop();

            // how many ops do we need to apply so that our current val becomes
            // greater than the next smallest value?
            long a_val = (long)a[0] * pow(multiplier,a[2]);
            auto a_nxt = pq.top();
            long a_nxt_val = (long)a_nxt[0] * pow(multiplier, a_nxt[2]);

            long a_val_new;
            // worst case a_val = 1, multiplier = 2, a_nxt_val = 1000000000
            // 2^30 > 1000000000
            int t = search(a_val, 1, min(k,30), a_nxt_val, multiplier);
            // cout << "search a_val " << a_val << " a_pos " << a[1] << " e " << k << " a_nxt_val " << a_nxt_val << " a_nxt_pos " << a_nxt[1] << " t " << t << endl;
            if( t == -1 ) {
                a_val_new = (long)a[0] * pow(multiplier,a[2]+k);
                pq.push({a[0],a[1],a[2]+k});
                k = 0;
            } else {
                a_val_new = (long)a[0] * pow(multiplier,a[2]+t);
                pq.push({a[0],a[1],a[2]+t});
                k -= t;
            }

            if( a_val_new > *mx)
                break;
        }
        // cout << "i " << i << endl;

        vector<int> ans(n);



        // if i == k then we have our answer
        if( k == 0 ) {
            while( !pq.empty() ) {
                auto a = pq.top();
                pq.pop();
                long aval = a[0];
                if( a[2] > 0 )
                    aval = (aval * modular_pow(multiplier,a[2])) % mod;
                ans[a[1]] = aval;
            }
            return ans;
        }

        // we know we have k operations left
        // after this, in every remaining full cycle, the multiplier
        // will be applied once to each element in the order in which
        // they are in the pq
        // we have applied i operations
        // how many more full cycles do we need to apply?
        // for the remainder of ops, we apply them in order
        int rem_k = k;
        // cout << "rem_k " << rem_k << endl;
        int full_cycles = rem_k / n;
        // cout << "full_cycles " << full_cycles << endl;
        int rem_ops = rem_k % n;
        // cout << "rem_ops " << rem_ops << endl;

        while( !pq.empty() ) {
            auto a = pq.top();
            pq.pop();

            long aval = a[0];
            if( a[2] > 0 )
                aval = (aval * modular_pow(multiplier,a[2])) % mod; // val after 1 cycle

            int exp = rem_ops > 0 ? full_cycles + 1 : full_cycles;
            aval = (aval * modular_pow(multiplier,exp)) % mod;
            ans[a[1]] = aval;
            --rem_ops;
        }

        return ans;
    }
};
