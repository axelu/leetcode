
// 930. Binary Subarrays With Sum
// https://leetcode.com/problems/binary-subarrays-with-sum/





class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size();
        // extreme case: n = 30000, nums[i] = 0 for 0 <= i < n, goal 0
        //          ans: 450015000 ( = n * ((n+1)/2) )

        int ans = 0;
        int i,j; // left index, right index

        if( goal == 0 ) {
            // find contigous subarrays of zero's
            for(i = 0; i < n; ++i)
                if( nums[i] == 0 )
                    break;
            if( i == n )
                return 0;
            if( i == n-1)
                return 1;
            int mode = 1;
            for(j = i+1; j < n; ++j) {
                if( mode == 1 ) {
                    if( nums[j] == 1 && nums[j-1] == 0 ) {
                        ans += (j - i) * ((double)(j-i+1)/2);
                        mode = 0;
                    }
                } else {
                    if( nums[j] == 0 ) {
                        i = j;
                        mode = 1;
                    }
                }
            }
            if( mode == 1 ) // finish up
                ans += (j - i) * ((double)(j-i+1)/2);

            return ans;
        }



        int zerosToLeft[n];
        int t = 0;
        for(i = 0; i < n; ++i) {
            zerosToLeft[i] = t;
            if( nums[i] == 1 ) {
                t = 0;
            }
            if( nums[i] == 0 )
                ++t;
        }
        int zerosToRight[n];
        t = 0;
        for(i = n-1; i >= 0; --i) {
            zerosToRight[i] = t;
            if( nums[i] == 1 ) {
                t = 0;
            }
            if( nums[i] == 0 )
                ++t;
        }

        /*
        for(i = 0; i < n; ++i)
            cout << i << ":" << zerosToLeft[i] << " ";
        cout << endl;
        for(i = 0; i < n; ++i)
            cout << i << ":" << zerosToRight[i] << " ";
        cout << endl;
        */


        i = 0;
        j = 0;
        int sum = nums[j];
        while( sum < goal && j < n-1) {
            ++j;
            sum += nums[j];
        }
        if( sum < goal )
            return 0;
        while( nums[i] != 1 )
            ++i;


        // i and j will be at a 1

        int l,r;
        int leftZeros,rightZeros;
        while(j<n) {

            // advance i to next 1 to count left zeros if any
            leftZeros = zerosToLeft[i];
            ++i;
            while( i < n && nums[i] != 1 )
                ++i;

            // advance j to the next 1 to count right zeros if any
            rightZeros = zerosToRight[j];
            ++j;
            while( j < n && nums[j] != 1 )
                ++j;

            ans += leftZeros + 1 + rightZeros + (leftZeros * rightZeros);
         }

        return ans;
    }
};
