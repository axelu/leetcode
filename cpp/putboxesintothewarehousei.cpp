
// 1564. Put Boxes Into the Warehouse I
// https://leetcode.com/problems/put-boxes-into-the-warehouse-i/
// day 8 May 2021 challenge bonus question
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3735/



class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(boxes.begin(),boxes.end());

        int n = warehouse.size();

        stack<pair<int,int>> stck; // warehouse height,idx
        stck.push({warehouse[0],0});

        // process the 1st box
        // map the warehouse as far as we need to
        int currBoxHeight = boxes[0];
        int i = 0;
        for(; i < n; ++i) {
            if( warehouse[i] < currBoxHeight ) {
                // the current box needs to go in pos i-1;
                i -= 1;
                break;
            }
            if( warehouse[i] < stck.top().first ) {
                stck.push({warehouse[i],i});
            }
        }

        // cout << "stck.size  " << stck.size() << endl;
        // cout << "stck.top() " << stck.top().first << " " << stck.top().second << endl;

        if( i == -1 ) return 0;     // the 1st box is higher than the warehouse entrance
        if( i == 0  ) return 1;     // the 1st box had to go at pos 0, no more boxes fit
        if( n == 1  ) return 1;     // warehouse has only 1 slot and we put the 1st box there
        int pos = i == n ? n-1 : i;
        int ans = 1;                // 1st box placed at pos

        // cout << "box 0 at pos " << pos << endl;

        for(i = 1; i < boxes.size(); ++i) {
            currBoxHeight = boxes[i];
            // the current box needs to go into the warehouse as far as it can go
            // how far is determined by either how far we have our warehouse filled up
            // OR by the box hitting the ceiling of the warehouse, whichever comes 1st
            pos -= 1;
            while( !stck.empty() && currBoxHeight > stck.top().first ) {
                if( stck.top().second-1 < pos ) pos = stck.top().second-1;
                stck.pop();
            }
            if( stck.empty() ) break; // the current box is higher than the warehouse entrance

            while( !stck.empty() && pos <= stck.top().second )
                stck.pop();

            ++ans;
            // cout << "box " << i << " at pos " << pos << endl;
            if( pos == 0 ) break; // our warehouse is full
        }
        return ans;
    }
};
