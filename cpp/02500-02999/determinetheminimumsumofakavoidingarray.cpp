
// 2829. Determine the Minimum Sum of a k-avoiding Array
// https://leetcode.com/problems/determine-the-minimum-sum-of-a-k-avoiding-array/





class Solution {
public:
    int minimumSum(int n, int k) {

        int l = 0;
        int sum = 0;
        unordered_set<int> avoid;

        for(int i = 1; l < n; ++i) {

            if( i >=k ||  avoid.find(i) == avoid.end() ) {
                // cout << i << " ";
                sum += i;
                ++l;

                if( i < k ) {
                    int t = k - i;
                    avoid.insert(t);
                }
            }
        }
        // cout << endl;

        return sum;
    }
};
