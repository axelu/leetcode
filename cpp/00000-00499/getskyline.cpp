
// 218. The Skyline Problem
// https://leetcode.com/problems/the-skyline-problem/


class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        size_t n = buildings.size();
        if( n == 0 ) return {};

        // min heap ("sort of"): xl,height,xr
        auto comp = [](const array<int,3> &a, const array<int,3> &b){
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] <  b[1] ) {
                    return true;
                } else if( a[1] == b[1] ) {
                    if( a[2] > b[2] ) {
                        return true;
                    }
                }
            }
            return false;
        };

        vector<array<int,3>> pq(2*n);
        int j = 0;
        for(int i = 0; i < n; ++i) {
            pq[j]   = {buildings[i][0],buildings[i][2],buildings[i][1]};
            ++j;
            pq[j] = {buildings[i][1],buildings[i][2],buildings[i][1]};
            ++j;
        }
        make_heap(pq.begin(),pq.end(),comp);

        // walk top line left to right
        // at each point we have to make a decision of how to continue:
        //     go up, continue horizontally or go down
        array<int,3> p; // point: xl,height,xr
        int xl,height,xr;

        // init
        pop_heap(pq.begin(),pq.end(),comp); // move top element to back
        p = pq.back();                      // get 'former' top element
        pq.pop_back();                      // remove 'former' top element
        // debug
        // cout << "p " << p[0] << " " << p[1] << " " << p[2] << endl;

        // stack of horizontal roof lines, highest (and longest) on top -> max heap
        priority_queue<array<int,2>> hl; // height, xr

        int currHeight = p[1];
        hl.push({p[1],p[2]});

        vector<vector<int>> r;
        r.push_back({p[0],p[1]});

        for(int i = 1; i < 2*n; ++i) {

            pop_heap(pq.begin(),pq.end(),comp);
            p = pq.back();
            pq.pop_back();

            // debug
            // cout << "p " << p[0] << " " << p[1] << " " << p[2] << " currHeight " << currHeight << endl;
            xl     = p[0];
            height = p[1];
            xr     = p[2];
            if( height > currHeight && xl != xr ) {
                // we are going up: point is higher than current height and a starting point
                // cout << "going up" << endl;
                currHeight = height;
                hl.push({height,xr});

                // if building 'butt' against each other,
                // we may go up on that last height change recorded
                if( !r.empty() ) {
                    if( r.back()[0] == xl ) {
                        r.back()[1] = height;
                    } else if( r.back()[1] != height ) {
                        r.push_back({xl,height});
                    }
                } else {
                    r.push_back({xl,height});
                }
            } else if( height == currHeight && xl != xr ) {
                // height == currHeight and point is a start point of its roof line
                // we will maintain current height
                hl.push({height,xr});
            } else if( height > currHeight && xl == xr ) {
                // height > currHeight && its an endpoint
                // ignore, we are not going up to an endpoint!
                // sorting/processing order may make us encounter this
            } else if( height == currHeight && xl == xr ) {
                // height == currHeight && its an endpoint
                // we are going down, the question is: how far down?
                //     Maybe to 0, maybe we stay at current height.
                // let's use our roof line stack to help us decide

                // get next stopping point on the way down from hl
                int maxHlHeight = 0;
                while( !hl.empty() ) {
                    array<int,2> horizontalline = hl.top();
                    int hlheight = horizontalline[0];
                    int hlxr = horizontalline[1];
                    if( hlxr > p[0] ) {
                        maxHlHeight = hlheight;
                        break;
                    } else {
                        // pop roof lines off that we have passed
                        hl.pop();
                    }
                }

                // if( maxHlHeight < currHeight ) cout << "going down" << endl;
                if( maxHlHeight != currHeight ) {
                    // r.push_back({xl,maxHlHeight});

                    if( !r.empty() ) {
                        if( r.back()[0] == xl ) {
                            r.back()[1] = maxHlHeight;
                        } else if( r.back()[1] != maxHlHeight ) {
                            r.push_back({xl,maxHlHeight});
                        }
                    } else {
                        r.push_back({xl,maxHlHeight});
                    }
                }
                currHeight = maxHlHeight;

            } else {
                // height < currHeight (end point or start point)
                if( xl == xr ) {
                    // endpoint
                    // ignore
                } else {
                    // staring point
                    // Note: our sorting will make us see higher starting points first
                    hl.push({height,xr});
                }
            }
        }

        // as buildings may 'butt' up on each other, we may have made a height change
        // on an existing entry, and with that created an entry with same height
        // final clean up
        n = r.size();
        for(int i = 1; i < n; ++i) {
            if( r[i-1][1] == r[i][1] ) {
                r.erase(r.begin()+i);
                --i;
                --n;
            }
        }

        return r;
    }
};
