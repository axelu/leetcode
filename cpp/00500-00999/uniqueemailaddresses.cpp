
// 929. Unique Email Addresses
// https://leetcode.com/problems/unique-email-addresses/



class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> us;
        string em;
        bool domainName;
        for(int i = 0; i < emails.size(); ++i) {
            em = "";
            domainName = false;
            for(int j = 0; j < emails[i].size(); ++j) {
                if( !domainName ) {
                    if( emails[i][j] == '@' ) {
                        domainName = true;
                    } else if( emails[i][j] == '.' ) {
                        continue;
                    } else if( emails[i][j] == '+' ) {
                        while( j < emails[i].size() && emails[i][j] != '@' ) ++j;
                        domainName = true;
                    }
                }
                em += emails[i][j];
            }
            us.insert(em);
        }
        return us.size();
    }
};
