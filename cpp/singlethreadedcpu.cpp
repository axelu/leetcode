
// 1834. Single-Threaded CPU
// https://leetcode.com/problems/single-threaded-cpu/





class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        // tasks[i] = [enqueueTimei, processingTimei]
        // the ith task will be available to process at enqueueTime
        // and will take processingTime to finish processing

        // add the original task index to the task list before sorting
        // tasks[i] = [enqueueTimei,processingTimei,index]
        int n = tasks.size();
        for(int i = 0; i < n; ++i)
            tasks[i].push_back(i);


        // sort tasks based on enqueueTime
        sort(tasks.begin(),tasks.end(),[](const vector<int>& a, const vector<int>& b){
           return a[0] < b[0];
        });



        // available tasks queue
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            if( a[0] > b[0] ) {         // processing time
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] )       // index
                    return true;
            }
            return false;
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);

        long t = tasks[0][0]; // time
        int pos = 0;

        // add tasks into available tasks queue
        while( pos < n && tasks[pos][0] == t ) {
            pq.push({tasks[pos][1],tasks[pos][2]});
            ++pos;
        }

        vector<int> ans(n);
        int i = 0; // index into ans

        while( !pq.empty() ) {

            // process the top task in the available tasks queue
            ans[i] = pq.top()[1];
            ++i;
            t += (long)pq.top()[0];      // advance the time
            pq.pop();

            // add new tasks that became available
            while( pos < n && tasks[pos][0] <= t ) {
                pq.push({tasks[pos][1],tasks[pos][2]});
                ++pos;
            }

            // if there are tasks left in the task list, but non were
            //    available yet, then skip time
            if( pq.empty() && pos < n ) {
                t = tasks[pos][0]; // skip time
                while( pos < n && tasks[pos][0] == t ) {
                    pq.push({tasks[pos][1],tasks[pos][2]});
                    ++pos;
                }
            }
        }

        return ans;
    }
};
