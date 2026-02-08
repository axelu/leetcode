
// 3817. Good Indices in a Digit String
// https://leetcode.com/problems/good-indices-in-a-digit-string/




class Solution {
public:
    vector<int> goodIndices(string s) {
        int n = s.size();

        vector<int> ans;

        int i = 0;
        string running = "";
        for(int j = 0; j < n; ++j) {
            running.push_back(s[j]);

            // construct string equal to the decimal representation of j
            string str_j = to_string(j);

            int i_to_be = j - str_j.size() + 1;
            while( i < i_to_be ) {
                running.erase(running.begin());
                ++i;
            }

            if( running == str_j )
                ans.push_back(j);
        }

        return ans;
    }
};
