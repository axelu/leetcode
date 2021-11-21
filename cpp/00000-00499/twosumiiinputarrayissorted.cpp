#include <iostream>
#include <vector>
#include <map>

// 167. Two Sum II - Input Array Is Sorted
// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted

using namespace std;

class Solution {
public:
    // the is the solution for https://leetcode.com/problems/two-sum/, works for this problem also,
    // but requires extra space, the solution does NOT rely on the the input array being sorted
    /*
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> r;                                                          
        map<int,int> m;                                                         
                                                                                
        for (int i = 0; i < numbers.size(); i++) {                                 
                                                                                
            int diff = target - numbers.at(i);                                     
                                                                                
            auto f = m.find(diff);                                              
            if ( f != m.end() ) {                                               
                r.push_back(f->second + 1);                                     
                r.push_back(i + 1);                                             
                break;                                                          
            }                                                                   
            m.insert({numbers.at(i),i});                                           
        }                                                                       
                                                                                
        return r;                                                                
    }
    */
    // but because in this problem https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    // the input array is sorted, we don't need the extra space and use a two-pointer solution instead
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0;                  // left idx
        int r = numbers.size() - 1; // right idx
        int sum;
        while(l < r) {
            sum = numbers[l] + numbers[r];
            if( sum == target ) {
                return {l+1,r+1};
            } else if( sum < target ) {
                ++l;
            } else {
                // sum > 0
                --r;
            }
        }
        return {};
    }
};

int main() {

    //vector<int> nums = {2,7,11,15};
    vector<int> nums = {1,2,7,11,15};
    int target = 18;

    Solution s;

    auto result = s.twoSum(nums, target);

    for (auto i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}




