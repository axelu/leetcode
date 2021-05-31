
// 630. Course Schedule III
// https://leetcode.com/problems/course-schedule-iii/
// day 2 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3729/




class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();

        // sort by lowest lastDay; if same lastDay sort by duration asc
        sort(courses.begin(),courses.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[1]  < b[1] ) return true;
            if( a[1] == b[1] ) {
                if( a[0] < b[0] ) return true;
            }
            return false;
        });

        priority_queue<int> pq; // will hold all current courses with the course with biggest duration on top

        int duration,lastDay;
        int currentTotalTime = 0;
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            duration = courses[i][0];
            lastDay  = courses[i][1];
            if( duration > lastDay ) continue;

            if( currentTotalTime + duration <= lastDay ) {
                currentTotalTime += duration;
                ++ans;
                pq.push(duration);
            } else {
                // if there is a course already in our current courses that has a bigger duration,
                // if we would swap the course with the bigger duration against our current course,
                // and it would allow us to finish the current course before its deadline AND
                // end up with a smaller total time, then we want to make the swap
                if( pq.top() > duration ) {
                    if( currentTotalTime - pq.top() + duration <= lastDay ) {
                        // swap
                        currentTotalTime = currentTotalTime - pq.top() + duration;
                        pq.pop();
                        pq.push(duration);
                    }
                }
            }
        }

        return ans;
    }
};
