
// 3433. Count Mentions Per User
// https://leetcode.com/problems/count-mentions-per-user/






class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> ans(numberOfUsers,0); // count of mentions

        vector<bool> online(numberOfUsers,true); // initially all users are online
        queue<pair<int,int>> online_events; // timestamp, user

        sort(events.begin(), events.end(),[](const vector<string>& a, const vector<string>& b){
            int atimestamp = stoi(a[1]);
            int btimestamp = stoi(b[1]);
            if( atimestamp < btimestamp ) {
                return true;
            } else if( atimestamp == btimestamp ) {
                if( a[0] == "OFFLINE" ) {
                    return true;
                }
            }
            return false;
        });

        for(int i = 0; i < events.size(); ++i) {
            int timestamp = stoi(events[i][1]);

            while( !online_events.empty() && online_events.front().first <= timestamp ) {
                online[online_events.front().second] = true;
                online_events.pop();
            }

            if( events[i][0] == "MESSAGE" ) {

                if( events[i][2] == "ALL" ) {
                    for(int j = 0; j < numberOfUsers; ++j)
                        ++ans[j];
                } else if( events[i][2] == "HERE" ) {
                    for(int j = 0; j < numberOfUsers; ++j)
                        if( online[j] )
                            ++ans[j];
                } else {
                    stringstream ss(events[i][2]);
                    string s;
                    while( getline(ss,s,' ') ) {
                        int user = stoi(s.substr(2));
                        ++ans[user];
                    }
                }

            } else { // events[i][0] == "OFFLINE"
                int user = stoi(events[i][2]);
                online[user] = false;
                online_events.push({timestamp+60, user});
            }
        }

        return ans;
    }
};
