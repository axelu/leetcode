
// 565. Array Nesting
// https://leetcode.com/problems/array-nesting/



// solution approach #2
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        size_t n = nums.size();
        int visited[n]; memset(visited,0,sizeof visited);
        int ans = 0;
        int start,count;
        for(int i = 0; i < n; ++i) {
            if( !visited[i] ) {
                start = nums[i];
                count = 0;
                do {
                    start = nums[start];
                    ++count;
                    visited[start] = 1;
                } while(start != nums[i]);
                ans = max(ans,count);
            }
        }
        return ans;
    }
};
