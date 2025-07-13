
// 3495. Minimum Operations to Make Array Elements Zero
// https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/






const vector<int> ops = {0, 3, 15, 63, 255, 1023, 4095, 16383, 65535, 262143, 1048575, 4194303, 16777215, 67108863, 268435455};

class Solution {
private:
    int get_number_ops(int x) {
        int ops = 0;
        while( x ) {
            ++ops;
            x = x / 4;
        }
        return ops;
    }

    // binary search
    int lower_bound(int target) {
        int n = 15;

        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= ops[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && ops[s] < target )
            ++s;

        return s;
    }

public:
    long long minOperations(vector<vector<int>>& queries) {
        // ops to take x to 0 via division by 4, specifically floor(x/4)
        // with 1 <= x <= 1e9
        //    3 15 63 255 1023 4095 16383 65535 262143 1048575 4194303 16777215 67108863 268435455 1000000000
        //    1  2  3   4    5    6     7     8      9      10      11       12       13        14         15

        /*
        int pre = 0;
        for(int i = 1; i <= 1000000000; ++i) {
            int tt1 = get_number_ops(i);
            if( tt1 > pre ) {
                ++pre;
                cout << pre-1 << " " << i-1 << endl;
            }
        }
        */

        long long ans = 0LL;

        // for each query
        // how many of each do num of ops do we have in our range?
        for(auto& q: queries) {
            long long area = 0LL;

            int l = q[0];
            int r = q[1]; // l < r
            // cout << "l " << l << " r " << r << endl;

            int e = r;
            long long i = lower_bound(r); // index into ops = number of ops
            // cout << "initial r will take " << i << " ops" << endl;
            while( i >= 1 ) {
                int s = ops[i-1]+1;
                if( s < l )
                    s = l;
                long long cnt = e - s + 1;

                // cout << "range s " << s << " e " << e << " ops " << i << " cnt " << cnt << endl;

                area += cnt * i;

                if( s == l )
                    break;

                e = s - 1;
                --i;
            }

            long long local_ans = area / 2LL;
            local_ans += area % 2LL;

            ans += local_ans;
        }

        return ans;
    }
};
