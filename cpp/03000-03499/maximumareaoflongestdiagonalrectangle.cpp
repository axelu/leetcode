
// 3000. Maximum Area of Longest Diagonal Rectangle
// https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/




class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        // array<int,2> diagonal sqare, area
        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        for(auto dim: dimensions) {
            int length = dim[0];
            int width = dim[1];
            int diagonal2 = (length * length) + (width * width);
            int area = length * width;
            pq.push({diagonal2,area});
        }

        return pq.top()[1];
    }
};
