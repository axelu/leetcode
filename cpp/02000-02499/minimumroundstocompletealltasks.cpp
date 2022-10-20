
// 2244. Minimum Rounds to Complete All Tasks
// https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/



class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        unordered_map<int,int> dic;
        for(int& x: tasks)
            ++dic[x];

        int ans = 0;

        for(auto it = dic.begin(); it != dic.end(); ++it) {
            int cnt = it->second;

            int rem3 = cnt % 3;
            // rem3 is either 0, 1 or 2

            if( rem3 == 0 ) {
                ans += cnt/3;
            } else if( rem3 == 2) {
                ans += cnt/3 + 1;
            } else {
                if( cnt == 1 )
                    return -1;

                // we need to find the largest count t < cnt
                // where t % 3 = 0 and (cnt-t) % 2 = 0

                ans += (cnt-4)/3 + 2;
            }
        }

        return ans;
    }
};
