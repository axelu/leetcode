
// 1947. Maximum Compatibility Score Sum
// https://leetcode.com/problems/maximum-compatibility-score-sum/
// https://leetcode.com/contest/weekly-contest-251/problems/maximum-compatibility-score-sum/




class Solution {
private:
    int scores[8][8]; // score[student][mentor]
    int mem[8][256];

    int calcCompatibilityScore(vector<int>& a, vector<int>& b, int n) {
        int ret = 0;
        for(int i = 0; i < n; ++i)
           if( a[i] == b[i] )
               ++ret;
        return ret;
    }

    int rec(int student, int taken, int m) {
        // taken is a bitmask of already assigned mentors

        if( student == m )
            return 0;

        if( mem[student][taken] != -1 )
            return mem[student][taken];

        int ret = -1;

        // we have a choice to assign student to each non-assigned mentor
        for(int i = 0; i < m; ++i) {    // mentor
            if( (taken >> i) & 1 )
                continue;

            taken |= 1 << i;
            ret = max(ret,scores[student][i] + rec(student+1,taken,m));

            // backtrack
            taken &= ~(1 << i);
        }

        return mem[student][taken] = ret;
    }

public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        // 1 <= m, n <= 8
        int m = students.size();        // number students = number mentors
        int n = students[0].size();     // number questions

        int ans = 0;

        // precompute scores for every possible pairing of student and mentor
        for(int i = 0; i < m; ++i)        // student
            for(int j = 0; j < m; ++j)    // mentor
                scores[i][j] = calcCompatibilityScore(students[i],mentors[j],n);

        memset(mem,-1,sizeof mem);

        return rec(0,0,m);;
    }
};
