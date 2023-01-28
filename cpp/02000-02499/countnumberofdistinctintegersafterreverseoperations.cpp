
// 2442. Count Number of Distinct Integers After Reverse Operations
// https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/




class Solution {
public:
    int countDistinctIntegers(vector<int>& nums) {
        int n = nums.size();
        unordered_set<long> us;

        for(int x: nums) {
            us.insert(x);
            long t = 0;
            while( x > 0 ) {
                t = t * 10  + (x % 10);
                x /= 10;
            }
            us.insert(t);
        }

        return us.size();
    }
};
