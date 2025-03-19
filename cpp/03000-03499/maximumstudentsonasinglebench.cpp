
// 3450. Maximum Students on a Single Bench
// https://leetcode.com/problems/maximum-students-on-a-single-bench/





class Solution {
public:
    int maxStudentsOnBench(vector<vector<int>>& students) {
        int n = students.size();
        if( n == 0 )
            return 0;

        unordered_map<int,unordered_set<int>> by_bench;
        for(int i = 0; i < n; ++i) {
            int student_id = students[i][0];
            int bench_id = students[i][1];
            by_bench[bench_id].insert(student_id);
        }

        int ans = 0;
        for(auto it = by_bench.begin(); it != by_bench.end(); ++it)
            ans = max(ans, (int)it->second.size());

        return ans;
    }
};
