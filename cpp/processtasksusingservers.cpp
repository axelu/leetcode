
// 1882. Process Tasks Using Servers
// https://leetcode.com/problems/process-tasks-using-servers/


class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();


        struct Server{
            int weight;
            int index;
            Server(int weight, int index) : weight(weight), index(index) {}
        };


        // free server heap by smallest weight and smallest index
        auto cmpfs = [](const Server* a, const Server* b) {
            if( a->weight > b->weight ) {
                return true;
            } else if ( a->weight == b->weight ) {
                if( a->index > b->index )
                    return true;
            }
            return false;
        };
        priority_queue<Server*,vector<Server*>,decltype(cmpfs)> freeServers(cmpfs);
        // initially all servers are free
        for(int i = 0; i < n; ++i) {
            // cout << "server i " << i << " weight " << servers[i] << endl;
            freeServers.push(new Server(servers[i],i));
        }


        // busy server heap
        auto cmpbs = [](const pair<long,Server*>& a, const pair<long,Server*>& b) {
            return a.first > b.first;
        };
        priority_queue<pair<long,Server*>,vector<pair<long,Server*>>,decltype(cmpbs)> busyServers(cmpbs);

        vector<int> ans(m);
        Server* pServer;
        long t = 0;                     // current second;

        for(int j = 0; j < m; ++j) {    // current task

            if( freeServers.empty() ) {
                // advance the time
                t = busyServers.top().first;
            }

            // cout << "t = " << t << endl;

            // free up servers that finished their task
            while(!busyServers.empty() && busyServers.top().first <= t ) {
                freeServers.push(busyServers.top().second);
                busyServers.pop();
            }


            // assign the current task to the top free server
            pServer = freeServers.top();
            // cout << "top free server weight " << pServer->weight << " index " << pServer->index << endl;

            freeServers.pop();
            busyServers.push({t+(long)tasks[j],pServer});
            ans[j] = pServer->index;

            // advance the time
            if( j == t )
                ++t;
        }

        return ans;
    }
};
