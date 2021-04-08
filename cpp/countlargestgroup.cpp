
// 1399. Count Largest Group
// https://leetcode.com/problems/count-largest-group/

class Solution {
public:
    int countLargestGroup(int n) {
        int a[37];
        for(int i = 0; i < 37; ++i) a[i] = 0;

        int k, sum, rem;
        int mx = 0;
        for(int i = 1; i <= n; ++i) {
            k = i;
            sum = 0;
            while(k > 0) {
                rem = k % 10;
                sum += rem;
                k /= 10;
            }
            ++a[sum];
            mx = max(mx,a[sum]);
        }

        return count(a,a+37,mx);
    }
};
