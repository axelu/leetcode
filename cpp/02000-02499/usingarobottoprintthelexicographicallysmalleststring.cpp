
// 2434. Using a Robot to Print the Lexicographically Smallest String
// https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/





class Solution {
public:
    string robotWithString(string s) {
        int n = s.size();

        deque<pair<char,int>> dq;
        for(int i = 0; i < n; ++i) {
            char c = s[i];
            while( !dq.empty() && c < dq.front().first ) {
                dq.pop_front();
            }
            dq.push_front({c,i});
        }
        /*
        for(auto it = dq.begin(); it != dq.end(); ++it)
            cout << it->first << "," << it->second << " ";
        cout << endl;
        */

        string ans = "";
        stack<char> stck;

        int i = 0;
        while( !dq.empty() ) {

            while( !stck.empty() && stck.top() <= dq.back().first ) {
                ans.push_back(stck.top());
                stck.pop();
            }
            while( i < dq.back().second ) {
                stck.push(s[i]);
                ++i;
            }
            ++i;
            ans.push_back(dq.back().first);
            dq.pop_back();
        }
        // finish up
        while( !stck.empty() ) {
            ans.push_back(stck.top());
            stck.pop();
        }

        return ans;
    }
};
