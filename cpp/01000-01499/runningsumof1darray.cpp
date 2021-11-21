#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1480. Running Sum of 1d Array
// https://leetcode.com/problems/running-sum-of-1d-array/
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> r;

        int sum = 0;
        transform(nums.begin(), nums.end(), back_inserter(r),
                   [sum](int a) mutable { sum += a; return sum; });

        //auto print = [](const int& n) { cout << " " << n; };
        //for_each(nums.cbegin(), nums.cend(), print);
        
        //r = {3,1,2,10,1};

        //for_each(nums.cbegin(), nums.cend(),
        //    [r](int n) mutable { 
        //        cout << "here: " << n << endl;
        //        r.push_back(n); 
                
        // });







        return r;
    }
};

int main() {

    Solution s;

    vector<int> nums = {3,1,2,10,1};

    vector<int> r = s.runningSum(nums);

    auto print = [](const int& n) { cout << " " << n; };
    for_each(r.cbegin(), r.cend(), print);
    cout << endl;



    return 0;
}
