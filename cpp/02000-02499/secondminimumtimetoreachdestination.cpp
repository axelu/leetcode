
// 2045. Second Minimum Time to Reach Destination
// https://leetcode.com/problems/second-minimum-time-to-reach-destination/




class Solution {
private:
    pair<int,int> delay(int time, int change) {
        // time > change

        int wait;
        int i = 2;
        while( true ) {

            int a = (time * i) / change;
            if( a % 2 == 1 ) {
                // after i traversals we arrive at red light and need to wait
                wait = (a+1) * change - (time * i);
                break;
            }
            ++i;
        }

        return {i,wait};
    }


public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        // calculate the shortest path (number edges to traverse)
        // the next shortest path would be one edge more, if a path with one edge more
        //     does not exist, it is two edges more
        // then overlay the delay encountered due to stop lights

        vector<int> g[n+1]; // bi-directional connected graph
        for(auto& v : edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        // BFS
        // array<int,3> node,steps,source
        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[1] > b[1];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        int seen1[n+1];memset(seen1,0,sizeof seen1); // track shortest path
        int seen2[n+1];memset(seen2,0,sizeof seen2); // track second shortest path
        pq.push({1,0,-1});
        seen1[1] = 1;
        while( !pq.empty() ) {
            int u = pq.top()[0];
            int steps = pq.top()[1];
            int src = pq.top()[2];
            pq.pop();

            if( u == n ) {
                if( seen2[u] )
                    break;
                else
                    continue;
            }

            // cout << "u " << u << " src " << src << " steps " << steps << endl;
            for(int i = 0; i < g[u].size(); ++i) {
                int v = g[u][i];
                // cout << "    v " << v << endl;
                if( v != src ) {
                    if( !seen1[v] ) {
                        seen1[v] = steps+1;
                        pq.push({v,steps+1,u});
                    } else if( !seen2[v] ) {
                        if( steps+1 > seen1[v] ) {
                            seen2[v] = steps+1;
                            pq.push({v,steps+1,u});
                        }
                    }
                }
            }
        }

        // cout << "seen1[n] " << seen1[n] << endl;
        // cout << "seen2[n] " << seen2[n] << endl;

        int t;
        if( !seen2[n] ) {
            t = seen1[n] + 2;
        } else if( seen2[n] > seen1[n]+2 ) {
            t = seen1[n] + 2;
        } else {
            t = seen2[n];
        }
        // cout << "t " << t << endl;

        // now we just need to figure out how long it takes t turns to arrive at n
        int ans;
        if( time < change ) {
            int m = change / time;
            int rem = change % time;
            if( rem != 0 ) {
                // m+1 traversals will take 2x change time
                if( t % (m+1) == 0 ) {
                    ans = ((t / (m+1)) - 1) * 2 * change;
                    ans += (m+1) * time;
                } else {
                    ans = (t / (m+1)) * 2 * change;
                    int rem2 = t % (m+1);
                    if( rem2 != 0 )
                        ans += rem2 * time;
                }
            } else {
                // m traversals will take 2x change time
                if( t % m == 0 ) {
                    ans = ((t / m) - 1) * 2 * change;
                    ans += m * time;
                } else {
                    ans = (t / m) * 2 * change;
                    int rem2 = t % m;
                    if( rem2 != 0 )
                        ans += rem2 * time;
                }
            }

        } else if( time > change ) {
            // cout << "time > change " << endl;
            int m = time / change;
            int rem = time % change;
            if( rem != 0 ) {
                if( m % 2 == 0 ) {
                    // for a certain number of traversals we will not experience a delay
                    // meaining we will arrive when the light is green
                    auto _delay = delay(time,change);
                    // _delay.first  = nbr times we can go w/o delay
                    // _delay.second = wait time after that

                    int a = _delay.first;
                    int wait = _delay.second;
                    // cout << "a " << a << " wait " << wait << endl;

                    if( t <= a ) {
                        ans = t * time;
                    } else {
                        int b = t / a;
                        int c = t % a;
                        ans = t * time + b * wait;
                        if( c == 0 )
                            ans -= wait;
                    }
                } else {
                    // we always arrive when light is red and need to wait (m+1)*change - time
                    // except when we arrive at n ( hence - 1x change )
                    int wait = ((m+1) * change) - time;
                    ans = t * time + t * wait - wait;
                }
            } else {
                if( m % 2 == 0 ) {
                    // we always arrive when light is green and can proceed
                    ans = t * time;
                } else {
                    // we always arrive when light is red and need to wait 'change'
                    // except when we arrive at n ( hence - 1x change )
                    ans = t * time + t * change - change;
                }
            }

        } else { // time == change
           ans = (t * 2 * change) - change;
        }

        return ans;
    }
};
