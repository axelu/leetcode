
// 1349. Maximum Students Taking Exam
// https://leetcode.com/problems/maximum-students-taking-exam/





class Solution {
private:
    int m;
    int n;
    int mem[8][256];

    int rec(vector<vector<char>>& seats, int curr_row_nbr, int prev_row_state) {
        if( curr_row_nbr == m )
            return 0;

        if( mem[curr_row_nbr][prev_row_state] != -1 )
            return mem[curr_row_nbr][prev_row_state];

        // prev_row_state: if bit[i] is set, then there is a student there
        //                 0 <= i < n

        // positions (0-indexed) of available seats in the current row
        // available means: seat is not broken and seat does not allow for cheating from prev row
        vector<int> v;
        for(int i = 0; i < n; ++i) {
            // broken seat?
            if( seats[curr_row_nbr][i] == '#' )
                continue;
            // someone sitting upper left
            if( i > 0 && ((prev_row_state >> (i-1)) & 1) )
                continue;
            // someone sitting upper right
            if( i < n-1 && ((prev_row_state >> (i+1)) & 1) )
                continue;

            v.push_back(i);
        }

        int a = 0;

        // we have a choice
        //    don't put anyone in the current row
        //    put between 1 and v.size() students in the current row in all possible configurations
        //        obeying the rule that they cannot sit next to each other

        for(int x = 0; x < (1 << v.size()); ++x) {
            vector<int> row(n,0);
            int cnt = 0;            // cnt of students that we have seated
            for(int j = 0; j < v.size(); ++j) {
                if( ((x >> j) & 1) && row[v[j]] == 0 ) {
                    row[v[j]] = 1;       // seat the student
                    ++cnt;
                    if( v[j] > 0 )
                        row[v[j]-1] = 2; // block seat to the left
                    if( v[j] < n-1 )
                        row[v[j]+1] = 2; // block seat to the right
                }
            }
            // transform row to a state
            int mask = 0;
            for(int i = 0; i < n; ++i)
                if( row[i] == 1 )
                    mask |= 1 << i;

            a = max(a,cnt + rec(seats,curr_row_nbr+1,mask));
        }

        return mem[curr_row_nbr][prev_row_state] = a;
    }
public:
    int maxStudents(vector<vector<char>>& seats) {
        m = seats.size();    // rows, 1 <= m <= 8
        n = seats[0].size(); // cols, 1 <= n <= 8

        memset(mem,-1,sizeof mem);
        return rec(seats,0,0);
    }
};
