
// 2899. Last Visited Integers
// https://leetcode.com/problems/last-visited-integers/




class Solution {
public:
    vector<int> lastVisitedIntegers(vector<string>& words) {
        int words_sz = words.size();

        vector<int> ans;
        vector<int> nums;
        int n = 0;
        int consecutive_prev = 0;
        for(int i = 0; i < words_sz; ++i) {

            if( words[i] == "prev" ) {
                ++consecutive_prev;

                int nums_idx = n-1 - (consecutive_prev-1);
                if( nums_idx >= 0 ) {
                    ans.push_back(stoi(words[nums[nums_idx]]));
                } else {
                    ans.push_back(-1);
                }

            } else {
                nums.push_back(i);
                ++n;
                consecutive_prev = 0;
            }
        }

        return ans;
    }
};
