
// 1847. Closest Room
// https://leetcode.com/problems/closest-room/



class Solution {
private:
    // binary search equal or largest less than targe
    int search(vector<int>& v, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( v[mid] == target ) {
            return mid;
        } else if( v[mid] < target ) {
            // can we do better?
            int t = search(v,mid+1,e,target);
            return t == -1 ? mid : t;
        } else {
            // v[mid] > target
            return search(v,s,mid-1,target);
        }
    }

public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        auto cmp = [](const array<int,3>& a, const array<int,3>& b){
            return a[1] < b[1];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);
        for(int i = 0; i < queries.size(); ++i)
            pq.push({queries[i][0],queries[i][1],i});

        sort(begin(rooms),end(rooms),[](const vector<int>& a, const vector<int>& b){
           return a[1] > b[1];
        });

        vector<int> ans(queries.size());

        int n = rooms.size(), roomIdx = 0, preferred, minSize, t, queryIdx;
        vector<int> v; // roomId
        for(int i = 0; i < queries.size(); ++i) {
            preferred = pq.top()[0];
            minSize   = pq.top()[1];
            queryIdx  = pq.top()[2];
            pq.pop();

            // add all rooms with roomSize >= minSize to our map
            for(; roomIdx < n; ++roomIdx)
                if( rooms[roomIdx][1] >= minSize ) {
                    if( v.empty() ) {
                        v.push_back(rooms[roomIdx][0]);
                    } else {
                        t = search(v,0,v.size()-1,rooms[roomIdx][0]);
                        if( t == -1 ) {
                            v.insert(v.begin(),rooms[roomIdx][0]);
                        } else if( t == v.size()-1) {
                            v.push_back(rooms[roomIdx][0]);
                        } else {
                            v.insert(v.begin()+t+1,rooms[roomIdx][0]);
                        }
                    }
                } else
                    break;

            if( v.empty() ) {
                ans[queryIdx] = -1;
                continue;
            } else if( v.size() == 1 ) {
                ans[queryIdx] = v[0];
                continue;
            }

            t = search(v,0,v.size()-1,preferred);
            if( t == -1 ) {
                ans[queryIdx] = v[0];
            } else if( v[t] == preferred ) {
                ans[queryIdx] = v[t];
            } else {
                if( t < v.size()-1 ) {
                    if( abs(v[t]-preferred) < abs(v[t+1]-preferred) || abs(v[t]-preferred) == abs(v[t+1]-preferred) )
                        ans[queryIdx] = v[t];
                    else
                        ans[queryIdx] = v[t+1];
                } else {
                    ans[queryIdx] = v[t];
                }
            }
        }

        return ans;
    }
};
