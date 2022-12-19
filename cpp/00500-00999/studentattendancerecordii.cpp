
// 552. Student Attendance Record II
// https://leetcode.com/problems/student-attendance-record-ii/



class Solution {
private:
    long mod = 1000000007;
    int n;

    long rec(int pos, bool has_been_absent, int prior_late_cnt, long mem[][2][3]) {
        if( pos == n )
            return 1;

        if( mem[pos][has_been_absent][prior_late_cnt] != -1 )
            return mem[pos][has_been_absent][prior_late_cnt];

        // at each position we have a choice
        //     P OR
        //     A if so far she has never been absent OR
        //     L if prior position is no L or if prior position is L then
        //         position before that is not L

        long ret = 0;

        // P
        ret = (ret + rec(pos+1,has_been_absent,0,mem)) % mod;

        // A
        if( !has_been_absent )
            ret = (ret + rec(pos+1,true,0,mem)) % mod;

        // L
        if( prior_late_cnt < 2 )
            ret = (ret + rec(pos+1,has_been_absent,prior_late_cnt+1,mem)) % mod;

        return mem[pos][has_been_absent][prior_late_cnt] = ret;
    }
public:
    int checkRecord(int n) {
        this->n = n;

        long mem[n][2][3];memset(mem,-1,sizeof mem);
        return rec(0,false,0,mem);
    }
};
