
// 1606. Find Servers That Handled Most Number of Requests
// https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/




class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;
        vector<array<int,2>> busyCount(k);
        // initially all servers are available and have done 0 work
        for(int i = 0; i < k; ++i) {
            available.insert(i);
            busyCount[i] = {i,0};
        }


        // array<int,2> server,finish
        auto cmp = [](const array<int,2> a, const array<int,2> b) {
            return a[1] > b[1];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);




        for(int i = 0; i < arrival.size(); ++i) {
            // free up servers who's task is complete
            while( !pq.empty() && pq.top()[1] <= arrival[i] ) {
                available.insert(pq.top()[0]);
                pq.pop();
            }

            if( available.empty() ) // no free servers -> drop the request
                continue;

            // attempt to assign to (i%k)th server
            auto f = available.lower_bound(i%k);
            if( f != available.end() ) {
                pq.push({*f,arrival[i]+load[i]});
                ++busyCount[*f][1];
                available.erase(f);
            } else {
                pq.push({*available.begin(),arrival[i]+load[i]});
                ++busyCount[*available.begin()][1];
                available.erase(available.begin());
            }
        }

        sort(begin(busyCount),end(busyCount),[](const array<int,2>& a, const array<int,2>& b) {
            return a[1] > b[1];
        });

        vector<int> ans;
        int c = busyCount.front()[1];
        ans.push_back(busyCount.front()[0]);
        for(int i = 1; i < busyCount.size(); ++i)
            if( busyCount[i][1] == c )
                ans.push_back(busyCount[i][0]);
            else
                break;


        return ans;
    }
};
