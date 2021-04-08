
// 1051. Height Checker
// https://leetcode.com/problems/height-checker/



class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> vo(heights);
        sort(vo.begin(),vo.end());
        int cnt = 0;
        for(int i = 0; i < vo.size(); ++i)
            if( vo[i] != heights[i] ) ++cnt;
        return cnt;
    }
};
