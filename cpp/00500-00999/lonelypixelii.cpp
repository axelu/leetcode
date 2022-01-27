
// 533. Lonely Pixel II
// https://leetcode.com/problems/lonely-pixel-ii/




class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int target) {
        int m = picture.size();
        int n = picture[0].size();

        int rowCnt[m];memset(rowCnt,0,sizeof rowCnt);
        int colCnt[n];memset(colCnt,0,sizeof colCnt);

        unordered_map<int,pair<string,bool>> um;

        int i,j;

        int ans = 0;

        // pass 1
        string rowStr;
        queue<int> colsWithBs;
        for(i = 0; i < m; ++i) {
            rowStr.clear();
            for(j = 0; j < n; ++j) {
                rowStr.push_back(picture[i][j]);
                if( picture[i][j] == 'B' ) {
                    ++rowCnt[i];
                    ++colCnt[j];
                    colsWithBs.push(j);
                }
            }
            while( !colsWithBs.empty() ) {
                auto p = um.insert({colsWithBs.front(),{rowStr,true}});
                if( !p.second && p.first->second.first != rowStr )
                        p.first->second.second = false;
                colsWithBs.pop();
            }
        }


        // pass 2
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                if( picture[i][j] == 'B' && rowCnt[i] == target && colCnt[j] == target &&
                    um[j].second )
                    ++ans;

        return ans;
    }
};
