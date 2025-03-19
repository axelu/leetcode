
// 3395. Subsequences with a Unique Middle Mode I
// https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/





/* there are 2 conditions a subsequence needs to meet
 * the sequence contains a unique mode AND
 * the middle element seq[2] is the unique mode
 *
 * what if we fix seq[2] and construct/count left and right
 * we easily know how many pairs we can make on the left and right
 * the product of that is the number of all subsequences
 * but we can only count the ones that have at least one more
 * of the same as seq[2] and each other less than two or
 * if we have three of us
 * number pairs n * (n-1)/2


*/
class Solution {
private:
    const long mod = 1000000007;

    long double_pair_cnt(unordered_map<int,long>& um, int sq2) {
        long ret = 0;
        for(auto& p: um) {
            int x = p.first;
            if( x == sq2 )
                continue;
            long t = p.second * (p.second-1L)/2L;
            ret = ret + t;
        }
        return ret;
    }

    long lft_rgt_cnt(unordered_map<int,long>& cnt_a, unordered_map<int,long>& cnt_b, int sq2) {
        long ret = 0;
        long f = cnt_a[sq2];

        long lb = 0L;
        for(auto& p: cnt_b) {
            int x = p.first;
            if( x == sq2 )
                continue;
            lb = lb + p.second;
        }

        for(auto& p: cnt_a) {
            int x = p.first;
            if( x == sq2 )
                continue;
            ret = ret + (f * p.second * cnt_b[x] * (lb - cnt_b[x]));
        }
        return ret;
    }


public:
    int subsequencesWithMiddleMode(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,long> cnt_lft;
        unordered_map<int,long> cnt_rgt;
        for(int x: nums)
            ++cnt_rgt[x];

        // nums[0]
        --cnt_rgt[nums[0]];
        ++cnt_lft[nums[0]];
        // nums[1]
        --cnt_rgt[nums[1]];
        ++cnt_lft[nums[1]];

        long ans = 0L;

        for(int i = 2; i <= n-3; ++i) {
            // cout << "i " << i << " nums[i] " << nums[i] << endl;
            int x = nums[i];
            --cnt_rgt[x];

            long l_lft = i;
            // total pairs we can make on the left
            long t_lft = l_lft * (l_lft-1L)/2L;

            long l_rgt = (n-1) - i;
            // total pairs we can make on the right
            long t_rgt = l_rgt * (l_rgt-1L)/2L;


            /*     left x right
                    - x x - -
                    x x x - -
                    - - x x -
                    - - x x x
                    - x x x -
                    - x x x x
                    x x x x -
                    x x x x x
            */

            // pick another x on the left and no x on the right
            if( cnt_lft[x] > 0 ) {
                // number pairs to the left with 1 x in it
                long a = (l_lft - cnt_lft[x]) * cnt_lft[x];

                // number pairs on the right w/o x
                long t = (l_rgt - cnt_rgt[x]);
                long b = t * (t-1L)/2L;
                // we need to discount where we picked 2 of the same on the right
                long c = double_pair_cnt(cnt_rgt, x);

                long d = a * (b - c);

                // we need to discount where we picked for our pair on the right the same we had picked on the left
                long e = lft_rgt_cnt(cnt_lft, cnt_rgt, x);

                // cout << "1 x 0 " << max(0L, (d-e)) << endl;
                ans = ans + max(0L, (d-e));
            }
            // pick 2 x on the left and no x on the right
            if( cnt_lft[x] > 1 ) {
                // number pairs to the left with 2 x in it
                long a = cnt_lft[x] * (cnt_lft[x] - 1L)/2L;

                // number pairs on the right w/o x
                long t = (l_rgt - cnt_rgt[x]);
                long b = t * (t-1L)/2L;

                // cout << "2 x 0 " << a*b << endl;
                ans = ans + (a * b);
            }
            // pick another x on the right and no x on the left
            if( cnt_rgt[x] > 0 ) {
                // number pairs to the right with 1 x in it
                long a = (l_rgt - cnt_rgt[x]) * cnt_rgt[x];

                // number pairs on the left w/o x
                long t = (l_lft - cnt_lft[x]);
                long b = t * (t-1L)/2L;
                // we need to discount where we picked 2 of the same on the left
                long c = double_pair_cnt(cnt_lft, x);

                long d = a * (b - c);

                // we need to discount where we picked for our pair on the left the same we had picked on the right
                long e = lft_rgt_cnt(cnt_rgt, cnt_lft, x);

                // cout << "0 x 1 " << max(0L, (d-e)) << endl;
                ans = ans + max(0L, (d-e));
            }
            // pick 2 x on the right and no x on the left
            if( cnt_rgt[x] > 1 ) {
                // number pairs to the right with 2 x in it
                long a = cnt_rgt[x] * (cnt_rgt[x] - 1L)/2L;

                // number pairs on the left w/o x
                long t = (l_lft - cnt_lft[x]);
                long b = t * (t-1L)/2L;

                // cout << "0 x 2 " << a*b << endl;
                ans = ans + (a * b);
            }
            // pick one on the left and one on the right
            if( cnt_lft[x] > 0 && cnt_rgt[x] > 0 ) {
                // number pairs to the left with 1 x in it
                long a = (l_lft - cnt_lft[x]) * cnt_lft[x];
                // number pairs to the right with 1 x in it
                long b = (l_rgt - cnt_rgt[x]) * cnt_rgt[x];

                // cout << "1 x 1 " << a*b << endl;
                ans = ans + (a*b);
            }
            // pick one on the left and two on the right
            if( cnt_lft[x] > 0 && cnt_rgt[x] > 1 ) {
                // number pairs to the left with 1 x in it
                long a = (l_lft - cnt_lft[x]) * cnt_lft[x];
                // number pairs to the right with 2 x in it
                long b = cnt_rgt[x] * (cnt_rgt[x] - 1L)/2L;

                // cout << "1 x 2 " << a*b << endl;
                ans = ans + (a*b);
            }
            // pick two on the left and one on the right
            if( cnt_lft[x] > 1 && cnt_rgt[x] > 0 ) {
                // number pairs to the left with 2 x in it
                long a = cnt_lft[x] * (cnt_lft[x] - 1L)/2L;
                // number pairs to the right with 1 x in it
                long b = (l_rgt - cnt_rgt[x]) * cnt_rgt[x];

                // cout << "2 x 1 " << a*b << endl;
                ans = ans + (a*b);
            }
            // pick two on the left and two on the right
            if( cnt_lft[x] > 1 && cnt_rgt[x] > 1 ) {
                // number pairs to the left with 2 x in it
                long a = cnt_lft[x] * (cnt_lft[x] - 1L)/2L;
                // number pairs to the right with 2 x in it
                long b = cnt_rgt[x] * (cnt_rgt[x] - 1L)/2L;

                // cout << "2 x 2 " << a*b << endl;
                ans = ans + (a*b);
            }
            // cout << "i " << i << " nums[i] " << nums[i] << " ans " << ans << endl;
            ++cnt_lft[x];
        }

        return ans % mod;
    }
};
