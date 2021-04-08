
// 362. Hit Counter
// https://leetcode.com/problems/design-hit-counter/



class HitCounter {
private:
    deque<pair<int,int>> dq; // timestamp,cnt
    int hits;

    void maintenance(int timestamp) {
        while( !dq.empty() ) {
            if( dq.front().first <= timestamp - 300) {
                hits -= dq.front().second;
                dq.pop_front();
            } else {
                break;
            }
        }
    }
public:
    /** Initialize your data structure here. */
    HitCounter() {
       hits = 0;
    }

    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        ++hits;
        if( dq.empty() ) {
            dq.push_back({timestamp,1});
        } else if( dq.back().first == timestamp ) {
            // time has not advanced, hit at the same time
            ++dq.back().second;
        } else {
            dq.push_back({timestamp,1});
            maintenance(timestamp);
        }
    }

    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        maintenance(timestamp);
        return hits;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
