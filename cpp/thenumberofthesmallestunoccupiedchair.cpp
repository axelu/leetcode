
// 1942. The Number of the Smallest Unoccupied Chair
// https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/
// https://leetcode.com/contest/biweekly-contest-57/problems/the-number-of-the-smallest-unoccupied-chair/




class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size(); // number of friends

        // split times into arrivals and departures
        // min heap arrivals and min heap departures
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[0]>b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> arrivals(cmp);
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> departures(cmp);
        for(int i = 0; i < n; ++i) {
            arrivals.push({times[i][0],i});
            departures.push({times[i][1],i});
        }

        priority_queue<int,vector<int>,greater<int>> available_chairs;
        // worst case all friends arrive sequentially
        // and have not left till targetFriend arrives
        for(int i = 0; i < n+1; ++i)
            available_chairs.push(i);


        unordered_map<int,int> um; // friend,chair


        // process arrivals and departures till targetFriend is seated
        while(arrivals.top()[1] != targetFriend) {

            // process arrival
            um.insert({arrivals.top()[1],available_chairs.top()});
            arrivals.pop();
            available_chairs.pop();

            // process departures
            while(!departures.empty() && departures.top()[0] <= arrivals.top()[0]) {
                auto f = um.find(departures.top()[1]);
                available_chairs.push(f->second);
                um.erase(f);
                departures.pop();
            }

        }

        return available_chairs.top();;
    }
};
