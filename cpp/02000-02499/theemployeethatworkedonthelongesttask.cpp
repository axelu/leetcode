
// 2432. The Employee That Worked on the Longest Task
// https://leetcode.com/problems/the-employee-that-worked-on-the-longest-task/



class Solution {
public:
    int hardestWorker(int n, vector<vector<int>>& logs) {

        int mx = 0;
        int id = -1;
        int s = 0;
        for(int i = 0; i < logs.size(); ++i) {

            if( logs[i][1] - s > mx ) {
                mx = logs[i][1] - s;
                id = logs[i][0];
            } else if( logs[i][1] - s == mx ) {
                if( logs[i][0] < id ) {
                    id = logs[i][0];
                }
            }
            s = logs[i][1];
        }

        return id;
    }
};
