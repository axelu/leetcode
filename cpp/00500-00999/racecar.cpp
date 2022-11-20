
// 818. Race Car
// https://leetcode.com/problems/race-car/




class Solution {
public:
    int racecar(int target) {
        // 1 <= target <= 10000

        // Example target = 6
        // instruction    A   A   A   R   A
        // position      0   1   3   7   7    6
        // speed         1   2   4   8  -1   -2

        /*
        int pos = 0;
        int speed = 1;
        while( pos < 10000 ) {
            cout << "pos " << pos << " speed " << speed << endl;
            pos = pos + speed;
            speed = speed * 2;
        }
        cout << "pos " << pos << " speed " << speed << endl;
        */

        struct cmp {
            public:
            bool operator()(const array<int,3>& a, const array<int,3>& b) {
                return a[0] > b[0];
            }
        };
        priority_queue<array<int,3>,vector<array<int,3>>,cmp> pq;
        pq.push({0,0,1});

        int offset = 10000;

        unordered_set<unsigned int> seen;
        seen.insert(1+offset);

        while( !pq.empty() ) {
            int steps  = pq.top()[0];
            int pos    = pq.top()[1];
            int speed  = pq.top()[2];

            pq.pop();

            if( pos == target )
                return steps;

            long key;

            // A
            int pos_new   = pos + speed;
            int speed_new = 2 * speed;
            if( abs(pos_new - target) < target ) {
                key = ((pos_new+offset)<<16) + speed_new+offset;
                if( seen.insert(key).second )
                    pq.push({steps+1,pos_new,speed_new});
            }
            // R
            pos_new       = pos;
            speed_new     = speed < 0 ? 1 : -1;
            key = ((pos_new+offset)<<16) + speed_new+offset;
            if( seen.insert(key).second )
                pq.push({steps+1,pos_new,speed_new});
            // RR
            if( speed != 1 && speed != -1 ) {
                pos_new       = pos;
                speed_new     = speed < 0 ? -1 : 1;
                key = ((pos_new+offset)<<16) + speed_new+offset;
                if( seen.insert(key).second )
                    pq.push({steps+2,pos_new,speed_new});
            }
            // RA
            pos_new       = speed > 0 ? pos -1 : pos + 1;
            speed_new     = speed > 0 ? -2 : 2;
            key = ((pos_new+offset)<<16) + speed_new+offset;
            if( seen.insert(key).second )
                pq.push({steps+2,pos_new,speed_new});

        }

        return 99;
    }
};
