
// 422. Valid Word Square
// https://leetcode.com/problems/valid-word-square/



class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        int n = words.size();

        string row,col;
        for(int i = 0; i < n; ++i) {
            row = words[i];
            col = "";
            // grab the ith char from every row
            for(int j = 0; j < n; ++j)
                if( words[j].size() > i )
                    col += words[j][i];
            if( row != col ) return false;
        }

        return true;
    }
};
