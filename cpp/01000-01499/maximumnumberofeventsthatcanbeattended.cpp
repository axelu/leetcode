
// 1353. Maximum Number of Events That Can Be Attended
// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/



class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(),events.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] )
                    return true;
            }
            return false;
        });

        int ans = 0;

        // heap, top of heap is earliest end date
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if( a[1] > b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] > b[0] )
                    return true;
            }
            return false;
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);
        pq.push(events[0]);

        int k = 0; // last day event attended
        for(int i = 1; i < events.size(); ++i) {
            int eventStart = events[i][0];
            int eventEnd   = events[i][1];
            // cout << "eventStart " << eventStart << " eventEnd " << eventEnd << endl;

            // our events are sorted by start day asc,
            // if our eventStart > top of queue start,
            // then attend as many events from queue as we can
            while( !pq.empty() && eventStart > pq.top()[0] ) {
                if( k+1 == eventStart )
                    break;
                if( k < pq.top()[1] ) {
                    ++ans;
                    k = max(pq.top()[0],k+1);
                }
                pq.pop();
            }
            pq.push(events[i]);
        }

        // finish up
        cout << pq.size() << endl;
            while( !pq.empty() ) {
                if( k < pq.top()[1] ) {
                    ++ans;
                    k = max(pq.top()[0],k+1);
                }
                pq.pop();
            }

        return ans;
    }
};
