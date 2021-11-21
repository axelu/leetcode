
// 1725. Number Of Rectangles That Can Form The Largest Square
// https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/


class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        map<int,int> m; // sqare length, count
        int maxLength;
        pair<map<int,int>::iterator,bool> p;
        for(int i = 0; i < rectangles.size(); ++i) {
            maxLength = min(rectangles[i][0],rectangles[i][1]);
            p = m.insert({maxLength,1});
            if( !p.second ) ++p.first->second;
        }
        return m.rbegin()->second;
    }
};
