
// 1497. Check If Array Pairs Are Divisible by k
// https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/






class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        int n = arr.size();

        int pairs = 0;

        int pos_rem[k];memset(pos_rem,0,sizeof pos_rem);
        int neg_rem[k];memset(neg_rem,0,sizeof neg_rem);

        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << " ";

            if( arr[i] >= 0 ) {
                // cout << " arr[i] " << arr[i] << " non-negative" << endl;
                int cur_rem = arr[i] % k;

                // we need
                // a negative arr[j] with abs(arr[j]) % k == cur_rem OR
                // a non-negative arr[j] with arr[j] % k == k - cur_rem
                bool f = false;
                if( neg_rem[cur_rem] > 0 ) {
                    f = true;
                    ++pairs;
                    --neg_rem[cur_rem];
                }
                if( !f ) {
                    int oth_rem = cur_rem != 0 ? k - cur_rem : 0;
                    if( pos_rem[oth_rem] > 0 ) {
                        f = true;
                        ++pairs;
                        --pos_rem[oth_rem];
                    }
                }
                if( !f )
                    ++pos_rem[cur_rem];

            } else { // arr[i] < 0
                // cout << " arr[i] " << arr[i] << " negative" << endl;
                int cur_rem = abs(arr[i]) % k;

                // we need
                // a non-negative arr[j] with abs(arr[j]) % k == cur_rem OR
                // a negative arr[j] with arr[j] % k == k - cur_rem
                bool f = false;
                if( pos_rem[cur_rem] > 0 ) {
                    f = true;
                    ++pairs;
                    --pos_rem[cur_rem];
                }
                if( !f ) {
                    int oth_rem = cur_rem != 0 ? k - cur_rem : 0;
                    if( neg_rem[oth_rem] > 0 ) {
                        f = true;
                        ++pairs;
                        --neg_rem[oth_rem];
                    }
                }
                if( !f )
                    ++neg_rem[cur_rem];
            }
        }

        return pairs == n/2;
    }
};
