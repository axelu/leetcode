
// 1985. Find the Kth Largest Integer in the Array
// https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/




class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {
        int n = nums.size();

        sort(begin(nums),end(nums),[](const string& a, const string& b){
            if( a.size() < b.size() ) {
                return true;
            } else if( a.size() == b.size() ) {
                return a < b;
            }
            return false;
        });
        /*
        for(auto s : nums)
            cout << s << " ";
        cout << endl;
        */

        return nums[n-k];
    }
};
