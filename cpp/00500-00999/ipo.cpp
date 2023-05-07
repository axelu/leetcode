
// 502. IPO
// https://leetcode.com/problems/ipo/




class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        // we want to start the project with the highest profit
        // that we are able to start ( w >= capital[i] )
        // if two projects have the same profit, we want to find the
        // the one that requires less capital first

        int n = profits.size();             // profits.size() == capital.size()
        vector<array<int,2>> projects(n);   // {profit,capital}
        for(int i = 0; i < n; ++i)
            projects[i] = {profits[i],capital[i]};

        // sort projects by capital required in ascending order
        sort(projects.begin(),projects.end(),[](array<int,2>& a, array<int,2>& b){
           return a[1] < b[1];
        });

        priority_queue<int> pq; // project with highest profit on top

        int executed = 0;
        int i = 0;
        while( executed < k and i < n ) {

            // add all projects we can execute to our priority queue
            while( i < n && projects[i][1] <= w ) {
                pq.push(projects[i][0]);
                ++i;
            }

            if( pq.empty() )
                break;

            // execute the project with the highest profit
            w += pq.top();
            pq.pop();
            ++executed;
        }
        while( executed < k && !pq.empty() ) {
            w += pq.top();
            pq.pop();
            ++executed;
        }

        return w;
    }
};
