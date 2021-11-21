
// 60. Permutation Sequence
// https://leetcode.com/problems/permutation-sequence/



// NAIVE IMPLEMENTATION will deliver correct result, but TLE
// NOT FINAL SOLUTION, see below for final solution

// adapted from problem 46. Permutations
// https://leetcode.com/problems/permutations/
/*
class Solution {
private:
    vector<int> * pNums;
    vector<vector<int>> * pR;

    void permute(int n) {
        if( n == 1 ) {
            pR->push_back(*pNums);
            return;
        }

        int t;
        for(int i = 0; i < n; ++i) {
            permute(n-1);

            if( n % 2 == 1 ) {
                // size is odd,: swap first and size-1 element
                t = (*pNums)[0];
                (*pNums)[0] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            } else {
                // size is even: swap ith and size-1 element
                t = (*pNums)[i];
                (*pNums)[i] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            }
        }
    }
public:
    string getPermutation(int n, int k) {
        // 1 <= n <= 9
        // worst case n = 9 -> n! = 9! = 362,880

        vector<int> nums(n);
        for(int i = 1; i <= n; ++i)
            nums[i-1] = i;

        pNums = &nums;

        vector<vector<int>> r;
        pR = &r;
        permute(n);

        sort(begin(r),end(r));
        string ans = "";
        for(int i = 0; i < n; ++i)
            ans += to_string(r[k-1][i]);


        return ans;
    }
};
*/

// based on solution approach #1
// factorial number system -> positional system with non-constant base
// https://en.wikipedia.org/wiki/Factorial_number_system

class Solution {
public:
    string getPermutation(int n, int k) {


        int factorials[n];
        factorials[0] = 1;
        vector<int> nums = {1};

        for(int i = 1; i < n; ++i) {
            // generate factorial system bases 0!, 1!, ..., (n - 1)!
            factorials[i] = factorials[i-1] * i;
            // generate nums 1, 2, ..., n
            nums.push_back(i+1);
        }

        // fit k in the interval 0 ... (n! - 1)
        --k;

        // compute factorial representation of k
        string ans = "";
        for(int i = n - 1; i > -1; --i) {
            int idx = k / factorials[i];

            ans += to_string(nums[idx]);
            auto it = begin(nums);advance(it,idx);
            nums.erase(it);

            k -= idx * factorials[i];
        }

        return ans;
    }
};
