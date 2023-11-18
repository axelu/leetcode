
// 2532. Time to Cross a Bridge
// https://leetcode.com/problems/time-to-cross-a-bridge/




class Solution {
public:
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {

        struct Worker {
            int i;
            int leftToRight;
            int pickOld;
            int rightToLeft;
            int putNew;
            int arrival;
            Worker(int i, int leftToRight, int pickOld, int rightToLeft, int putNew) :
                i(i), leftToRight(leftToRight), pickOld(pickOld), rightToLeft(rightToLeft), putNew(putNew), arrival(0) {}
        };

        // sort by efficiency
        auto cmp1 = [](Worker * a, Worker * b){
            int a_efficiency = a->leftToRight + a->rightToLeft;
            int b_efficiency = b->leftToRight + b->rightToLeft;
            if( a_efficiency < b_efficiency ) {
                return true;
            } else if( a_efficiency == b_efficiency ) {
                if( a->i < b->i ) {
                    return true;
                }
            }
            return false;
        };

        // sort by arrival
        auto cmp2 = [](Worker * a, Worker * b){
            return a->arrival > b->arrival;
        };

        priority_queue<Worker*,vector<Worker*>,decltype(cmp1)> l2r(cmp1);
        priority_queue<Worker*,vector<Worker*>,decltype(cmp2)> po(cmp2); // picking from old
        priority_queue<Worker*,vector<Worker*>,decltype(cmp1)> r2l(cmp1);
        priority_queue<Worker*,vector<Worker*>,decltype(cmp2)> un(cmp2); // unloading to new

        // initially all workers are ready to cross at time 0
        for(int i = 0; i < k; ++i) {
            Worker* worker = new Worker(i,time[i][0],time[i][1],time[i][2],time[i][3]);
            l2r.push(worker);
        }

        // the bridge is our limiter
        // at each cycle a worker is crossing the bridge
        // we advance the time to when the crossing is done

        // put the 1st worker on the bridge
        Worker* worker_on_bridge(l2r.top());
        l2r.pop();
        int direction = 0; // 0 -> left to right, 1 -> right to left

        // as long as there are packages in the new warehouse, send a worker
        int t = 0;
        while( n > 0 ) {
            // cout << "time " << t << " worker " << worker_on_bridge->i << " crosses bridge from ";

            // worker on the bridge crosses
            if( direction == 0 ) { // left to right
                // cout << "left to right" << endl;
                // she will finish crossing at t + worker_on_bridge->leftToRight = our new time
                t = t + worker_on_bridge->leftToRight;
                // she will be waiting to return at t + worker_on_bridge->leftToRight + pickOld
                worker_on_bridge->arrival = t + worker_on_bridge->pickOld;
                po.push(worker_on_bridge);

                // decrement packages
                --n;

            } else { // right to left
                // cout << "right to left" << endl;
                // she will finish crossing at t + worker_on_bridge->RightToLeft = our new time
                t = t + worker_on_bridge->rightToLeft;
                // she will be waiting to return at t + worker_on_bridge->RightToLeft + putNew
                worker_on_bridge->arrival = t + worker_on_bridge->putNew;
                un.push(worker_on_bridge);
            }

            // worker crossed the bridge
            worker_on_bridge = nullptr;
            direction = -1;

            // our current time is t
            // determine who is waiting
            while( !un.empty() && un.top()->arrival <= t ) {
                l2r.push(un.top());
                un.pop();
            }
            while( !po.empty() && po.top()->arrival <= t ) {
                r2l.push(po.top());
                po.pop();
            }

            // if both queues to cross bridge are empty, then advance the time
            if( r2l.empty() && l2r.empty() ) {
                int tun = INT_MAX;
                if( !un.empty() )
                    tun = un.top()->arrival;
                int tpo = INT_MAX;
                if( !po.empty() )
                    tpo = po.top()->arrival;

                t = min(tun,tpo);
                // determine who is waiting again
                while( !un.empty() && un.top()->arrival <= t ) {
                    l2r.push(un.top());
                    un.pop();
                }
                while( !po.empty() && po.top()->arrival <= t ) {
                    r2l.push(po.top());
                    po.pop();
                }
            }

            // put a new worker on the bridge according to rules
            if( !r2l.empty() ) {
                worker_on_bridge = r2l.top();
                direction = 1;
                r2l.pop();
            } else if( n > 0 && !l2r.empty() ) {
                worker_on_bridge = l2r.top();
                direction = 0;
                l2r.pop();
            } else { // r2l is empty, but n == 0
                // TODO

            }
        }

        // it could be that we are here and no worker is on the bridge
        if( worker_on_bridge == nullptr ) {
            // our current time is t
            // determine who is waiting
            while( !po.empty() && po.top()->arrival <= t ) {
                r2l.push(po.top());
                po.pop();
            }

            // if queue to cross bridge is empty, then advance the time
            if( r2l.empty() && !po.empty() ) {
                t = po.top()->arrival;
                // determine who is waiting again
                while( !po.empty() && po.top()->arrival <= t ) {
                    r2l.push(po.top());
                    po.pop();
                }
            }

            if( !r2l.empty() ) {
                worker_on_bridge = r2l.top();
                direction = 1;
                r2l.pop();
            }
        }

        // let the workers picking up old packages cross
        // the last one is our answer
        // t is our time
        while( worker_on_bridge != nullptr ) {
            // cout << "time " << t << " worker " << worker_on_bridge->i << " crosses bridge from right to left";
            // worker on the bridge crosses
            // only workers crossing are going right to left
            t = t + worker_on_bridge->rightToLeft;

            // worker crossed the bridge
            worker_on_bridge = nullptr;
            direction = -1;

            // our current time is t
            // determine who is waiting
            while( !po.empty() && po.top()->arrival <= t ) {
                r2l.push(po.top());
                po.pop();
            }

            // if queue to cross bridge is empty, then advance the time
            if( r2l.empty() && !po.empty() ) {
                t = po.top()->arrival;
                // determine who is waiting again
                while( !po.empty() && po.top()->arrival <= t ) {
                    r2l.push(po.top());
                    po.pop();
                }
            }

            if( !r2l.empty() ) {
                worker_on_bridge = r2l.top();
                direction = 1;
                r2l.pop();
            }
        }

        return t;
    }
};
