
// 1700. Number of Students Unable to Eat Lunch
// https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/

class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        size_t n = students.size(); // students.length == sandwiches.length

        int i = 0, j = 0;
        queue<int> q;

        // round 1
        for(; i < n; ++i)
            if( students[i] == sandwiches[j] ) ++j;
            else q.push(students[i]);
        if( j == n ) return 0;

        size_t qsz;
        int student;
        while(true) {
            qsz = q.size();
            for(i = 0; i < qsz; ++i) {
                student = q.front();
                q.pop();
                if( student == sandwiches[j] ) ++j;
                else q.push(student);
            }
            if( j == n ) return 0;
            if( q.size() == qsz ) break;
        }

        return n-j;
    }
};
