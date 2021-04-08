
// 937. Reorder Data in Log Files
// https://leetcode.com/problems/reorder-data-in-log-files/


class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        int n = logs.size();

        vector<string> ans;

        queue<string> digitLogs;
        for(int i = 0; i < n; ++i)
            // is the entry a Letter-log or a Digit-log?
            if( isdigit(logs[i][logs[i].find(' ')+1]) )
                digitLogs.push(logs[i]);
            else
                ans.push_back(logs[i]);

        sort(ans.begin(),ans.end(),[](const string& a, const string& b){

            int aPos1stSpace = a.find(' ');
            string aIdentifier = a.substr(0,aPos1stSpace);
            string aContent = a.substr(aPos1stSpace+1);

            int bPos1stSpace = b.find(' ');
            string bIdentifier = b.substr(0,bPos1stSpace);
            string bContent = b.substr(bPos1stSpace+1);

            if( aContent < bContent ) {
                return true;
            } else if( aContent == bContent ) {
                if( aIdentifier < bIdentifier ) return true;
            }
            return false;
        });

        // add digit logs to the back in their original order
        while( !digitLogs.empty() ) {
            ans.push_back(digitLogs.front());
            digitLogs.pop();
        }

        return ans;
    }
};
