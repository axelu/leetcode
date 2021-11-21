
// 457. Circular Array Loop
// https://leetcode.com/problems/circular-array-loop/





class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return false;
        // cout << "n " << n << endl;

        // every index is a potential starting point
        int mode;
        int seen[n];memset(seen,-1,sizeof seen);
        for(int i = 0; i < n; ++i) {

            if( seen[i] == -1 ) {
                // cout << "starting from i " << i << " nums[i] " << nums[i] << endl;
                seen[i] = i;
                mode = nums[i] > 0 ? 0 : 1; // 0 positive start, 1 negative start

                int j = i;
                while( true ) {
                    int nxt = j + nums[j];
                    if( nxt >= n )
                        nxt = nxt % n;
                    else if( nxt < 0 )
                        nxt = n - (abs(nxt) % n);

                    // cout << "  nxt " << nxt << endl;

                    if( seen[nxt] == i ) {
                        // we have seen next as part of our current journey
                        if( j == nxt ) // loop of length 1
                            break;
                        return true;
                    }

                    if( (mode == 0 && nums[nxt] < 0) ||
                        (mode == 1 && nums[nxt] > 0) ) {
                        break;
                    }
                    seen[nxt] = i;
                    j = nxt;
                }
            }
        }

        return false;
    }
};
