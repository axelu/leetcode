
// 2037. Minimum Number of Moves to Seat Everyone
// https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/




class Solution {
public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        int n = seats.size(); // 1 <= n <= 100, n == seats.length == students.length

        // greedily match smallest positioned student with smallest positioned chair
        sort(begin(seats),end(seats));
        sort(begin(students),end(students));

        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans += abs(seats[i]-students[i]);

        return ans;
    }
};
