
// 805. Split Array With Same Average
// https://leetcode.com/problems/split-array-with-same-average/



class Solution {
private:
    vector<bool> seen;

    bool rec(const vector<int>& nums, const int n, const int sumNums, const int pos, const int sumA, const int sizeA) {
        // cout << "rec pos " << pos << " sumA " << sumA << " sizeA " << sizeA << endl;
        if( pos == n ) {
            if( sizeA == n )
                return 0;

            double a = sumA / (double)sizeA;
            double b = (sumNums - sumA) / (double)(n-sizeA);
            return abs(a-b) <= 1e-5; // floating point compare
        }

        int key = (pos<<24) + (sumA<<5) + sizeA;
        if( seen[key] )
            return false;

        seen[key] = true;

        // we have a choice
        //    add nums[pos] to partition A OR
        //    add nums[pos] to partition B

        if( rec(nums,n,sumNums,pos+1,sumA+nums[pos],sizeA+1) == 1 )
            return true;

        return rec(nums,n,sumNums,pos+1,sumA,sizeA);
    }

public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 30

        // if n = 30, we would have 1073741823 - 2 options
        // minus 1 where all values would be assigned to one partition and
        // minus 1 where all values would be assigned to the other partition

        int sumNums = accumulate(nums.begin(),nums.end(),0);

        // mem size
        // 30 positions max -> binary 5 digits
        // max sum = max position * max nums[i] = 30 * 10000 = 300000 -> 19 binary digits
        // 30 elements max in one partition -> binary 5 digits
        // total 29 digits binary -> binary 11111111111111111111111111111 = descimal 536870911
        seen.resize(536870912);

        return rec(nums,n,sumNums,0,0,0);
    }
};
