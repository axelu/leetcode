#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> r;
        map<int,int> m;

        for (int i = 0; i < nums.size(); i++) {

            int diff = target - nums.at(i);

            auto f = m.find(diff);
            if ( f != m.end() ) {
                r.push_back(f->second);
                r.push_back(i); 
                break;
            }
            m.insert({nums.at(i),i});
        }

        return r;
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




