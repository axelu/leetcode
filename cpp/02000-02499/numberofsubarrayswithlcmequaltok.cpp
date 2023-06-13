
// 2470. Number of Subarrays With LCM Equal to K
// https://leetcode.com/problems/number-of-subarrays-with-lcm-equal-to-k/






class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

public:
    int subarrayLCM(vector<int>& nums, int k) {
        // adding a sentinel
        nums.push_back(k+1);

        int n = nums.size();

        int ans = 0;

        int s = 0;
        int i = 0;
        int r = -1;     // index at which lcm(nums[i],nums[r]) == k
        for(int j = 0; j < n; ++j) {
            // cout << "i " << i << " j " << j << endl;

            if( nums[j] > k || k % nums[j] != 0 ) {
                // nums[j] cannot be part of a window
                // cout << "nums[" << j << "] = " << nums[j] << " cannot be part of a window" << endl;

                // do we have a window with LCM == k?
                if( r != -1 ) {
                    // we have a window [i,j-1] inclusive where LCM == k
                    // we know we saw LCM == k first in window [s,r] with i <= s and r <= j
                    // lets count the windows on the left side of r

                    int l = s;
                    ++s;
                    while( s <= r ) {
                        if( lcm(nums[s],nums[r]) == k ) {
                            l = s;
                        }
                        ++s;
                    }
                    int cnt = l + 1 - i;
                    // cout << "cnt " << cnt << endl;
                    // anything about the pivot window [l,r] has LCM == k
                    // cout << "anything about the pivot window [" << l << "," << r << "] has LCM == k" << endl;
                    ans += cnt * (j - r);
                    j = r;
                    i = s = l + 1;
                    r = -1;

                } else {
                    i = j+1;
                }

            } else {
                // nums[j] can be part of a window
                // cout << "nums[" << j << "] = " << nums[j] << " can be part of a window" << endl;
                if( r == -1 ) {

                    // find the leftmost index t in which the lcm for the window [t,j] is k
                    int _lcm = nums[j];
                    int t = j;
                    while( t >= i ) {
                        _lcm = lcm(nums[t],_lcm);
                        if( _lcm == k ) {
                            s = t;
                            r = j;
                        }
                        --t;
                    }
                    /*
                    if( r != -1 )
                        cout << "nums[" << i << "] = " << nums[i] << " nums[" << j << "] = " << nums[j] << " have lcm == k" << endl;
                    */
                }
            }
        }

        return ans;
    }
};
