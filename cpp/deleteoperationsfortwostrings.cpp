
// 583. Delete Operation for Two Strings
// https://leetcode.com/problems/delete-operation-for-two-strings/
// day 7 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3734/





class Solution {
private:
    int mem[500][500];

    int rec(string& s1, int& n1, int p1, string& s2, int& n2, int p2) {
        // cout << "p1 " << p1 << " p2 " << p2 << endl;
        if( p1 == n1 ) return n2-p2;
        if( p2 == n2 ) return n1-p1;

        if( mem[p1][p2] != -1 ) return mem[p1][p2];

        // at each step we have choices
        // - delete char in s1
        // - delete char in s2
        // - dont' delete char in s1 or s2 if they are equal

        int d1 = rec(s1,n1,p1+1,s2,n2,p2)+1;
        int d2 = rec(s1,n1,p1,s2,n2,p2+1)+1;
        int d3 = s1[p1] == s2[p2] ? rec(s1,n1,p1+1,s2,n2,p2+1) : INT_MAX;

        return mem[p1][p2] = min({d1,d2,d3});
    }
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size();
        int n2 = word2.size();
        memset(mem,-1,sizeof mem);
        return rec(word1,n1,0,word2,n2,0);
    }
};
