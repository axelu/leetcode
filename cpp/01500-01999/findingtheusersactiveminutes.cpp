
// 1817. Finding the Users Active Minutes
// https://leetcode.com/problems/finding-the-users-active-minutes/


class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {

        sort(logs.begin(),logs.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });


        int n = logs.size();
        /*
        for(int i = 0; i < n; ++i) {
            cout << logs[i][0] << "," << logs[i][1] << ";";
        }
        cout << endl;
        */


        vector<int> ans(k,0);
        int prevUser = logs[0][0];
        int prevTime = -1;
        int uam = 0;
        for(int i = 0; i < n; ++i) {
            if( prevUser == logs[i][0] ) {
                if( prevTime != logs[i][1] ) {
                    ++uam;
                }
            } else {
                ++ans[uam-1];
                uam = 1;
            }
            prevUser = logs[i][0];
            prevTime = logs[i][1];
        }
        ++ans[uam-1];

        return ans;
    }
};
