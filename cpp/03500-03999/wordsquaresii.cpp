
// 3799. Word Squares II
// https://leetcode.com/problems/word-squares-ii/



class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        int n = words.size(); // 4 <= words.length <= 15; words[i].length == 4

        // collect words by starting char
        // collect words by starting and ending char (26 x 26 = 676)
        // dfs for each word remembering the starting letter of the 1st word
        //  0    1     2      3
        // (top, left, right, bottom)​​​​​​​

        // 01234567890123456789012345
        // abcdefghijklmnopqrstuvwxyz

        vector<vector<int>> dicfirst(26, vector<int>());
        vector<vector<vector<int>>> dicfirstlast(26, vector<vector<int>>(26, vector<int>()));
        for(int i = 0; i < n; ++i) {
            int fst = words[i][0] - 'a';
            int lst = words[i][3] - 'a';
            dicfirst[fst].push_back(i);
            dicfirstlast[fst][lst].push_back(i);
        }

        vector<vector<string>> ans;

        vector<string> square;
        vector<bool> seen(n, false);
        for(int i = 0; i < n; ++i) {
            // try every word as word 0
            int idx0 = i;
            seen[idx0] = true;
            int fst0 = words[i][0] - 'a';
            int lst0 = words[i][3] - 'a';
            square.push_back(words[idx0]);

            // try every word with same starting char as word 0 fst0
            // left as word 1
            for(int j = 0; j < dicfirst[fst0].size(); ++j) {
                int idx1 = dicfirst[fst0][j];
                if( seen[idx1] )
                    continue;

                seen[idx1] = true;
                int lst1 = words[idx1][3] - 'a';
                square.push_back(words[idx1]);

                // try every word with same starting char as word 0 lst0
                // right as word 2
                for(int k = 0; k < dicfirst[lst0].size(); ++k) {
                    int idx2 = dicfirst[lst0][k];
                    if( seen[idx2] )
                        continue;

                    seen[idx2] = true;
                    int lst2 = words[idx2][3] - 'a';
                    square.push_back(words[idx2]);

                    // every word with char0 = lst1 and char3 = lst2
                    // completes our square
                    for(int o = 0; o < dicfirstlast[lst1][lst2].size(); ++o) {
                        int idx3 = dicfirstlast[lst1][lst2][o];
                        if( seen[idx3] )
                            continue;
                        square.push_back(words[idx3]);
                        ans.push_back(square);
                        square.pop_back();
                    }

                    // back track
                    seen[idx2] = false;
                    square.pop_back();
                }
                // back track
                seen[idx1] = false;
                square.pop_back();
            }
            // back track
            seen[idx0] = false;
            square.pop_back();
        }

        // sort
        sort(ans.begin(), ans.end());

        return ans;
    }
};
