
// 1580. Put Boxes Into the Warehouse II
// https://leetcode.com/problems/put-boxes-into-the-warehouse-ii/




// builds on solution for
// 1564. Put Boxes Into the Warehouse I
// https://leetcode.com/problems/put-boxes-into-the-warehouse-i/


class Solution {
private:
    vector<pair<int,int>> mapWarehouse(int pos, vector<int>& warehouse) {
        vector<pair<int,int>> stck; // warehouse height,idx
        stck.push_back({warehouse[0],0});

        // process the 1st box
        // map the warehouse as far as we need to
        for(int i = 0; i < pos; ++i) {
            if( warehouse[i] < stck.back().first ) {
                stck.push_back({warehouse[i],i});
            }
        }

        return stck;
    }

    pair<int,int> placeBox(int boxHeight, int pos, vector<pair<int,int>>& stck) {
        if( pos < 1 )
            return {-1,-1};
        // pos is the position of the last box we placed

        // the current box needs to go into the warehouse as far as it can go
        // how far is determined by either how far we have our warehouse filled up
        // OR by the box hitting the ceiling of the warehouse, whichever comes 1st
        int i = stck.size() - 1;
        pos -= 1;
        while( i > -1 && boxHeight > stck[i].first ) {
            if( stck[i].second-1 < pos )
                pos = stck[i].second - 1;
            --i;
        }

        if( i == -1 ) // the current box is higher than the warehouse entrance
            return {-1,-1};

        while( i > -1 && pos < stck[i].second )
            --i;

        return {pos,i};
    }

    int maxBoxesInWarehouse(int pos, vector<int>& boxes, vector<int>& warehouse) {
        // cout << "box 0 at pos " << pos << endl;

        vector<pair<int,int>> stck = mapWarehouse(pos,warehouse);

        int ans = 1;                // 1st box placed at pos

        for(int i = 1; i < boxes.size(); ++i) {
            auto p = placeBox(boxes[i],pos,stck);
            pos = p.first;
            int lst = p.second;
            if( pos == -1 )
                break;

            ++ans;

            if( pos == 0 ) // our warehouse is full
                break;

            for(int k = stck.size() - 1; k > lst; --k)
                stck.pop_back();
        }
        return ans;
    }

    int maxBoxesInTwoWarehouses(int mn_pos, vector<int>& boxes, vector<int>& warehouse) {
        // put smallest box as mn_pos
        // split the warehouse at mn_pos:
        // left warehouse:   0          to   mn_pos-1
        // right warehouse:  mn_pos+1   to   n-1

        int ans = 0; // box 0 placed at pos mn_pos

        // map left warehouse
        vector<pair<int,int>> stckl = mapWarehouse(mn_pos+1,warehouse);
        int posl = mn_pos + 1;

        // map right warehouse
        reverse(warehouse.begin(),warehouse.end());
        mn_pos = warehouse.size()-1 - mn_pos;
        vector<pair<int,int>> stckr = mapWarehouse(mn_pos,warehouse);
        int posr = mn_pos;

        // we want to place the box into smallest space,
        // which could be left of right warehouse

        for(int i = 0; i < boxes.size(); ++i) {

            auto pl = placeBox(boxes[i],posl,stckl);
            int tl = pl.first;
            int lstl = pl.second;
            auto pr = placeBox(boxes[i],posr,stckr);
            int tr = pr.first;
            int lstr = pr.second;

            if( tl == -1 && tr == -1 ) // both warehouses full or entrances to small
                break;

            ++ans;

            if( tl == -1 ) {
                posl = -1;
                stckl.clear();
                posr = tr;
                for(int k = stckr.size() - 1; k > lstr; --k)
                    stckr.pop_back();

            } else if( tr == -1 ) {
                posl = tl;
                for(int k = stckl.size() - 1; k > lstl; --k)
                    stckl.pop_back();
                posr = -1;
                stckr.clear();

            } else {
                if( stckl[lstl].first < stckr[lstr].first ) {
                    posl = tl;
                    for(int k = stckl.size() - 1; k > lstl; --k)
                        stckl.pop_back();
                } else {
                    posr = tr;
                    for(int k = stckr.size() - 1; k > lstr; --k)
                        stckr.pop_back();
                }
            }
        }

        return ans;
    }

public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(boxes.begin(),boxes.end());

        int n = warehouse.size();

        // we need to put one box into the warehouse
        // we start with the smallest box
        // cases: we try from the left and box get stuck at pos i
        //        then the box will also get stuck from the right at some pos j
        //        note: i could be -1 if box does not fit through left entrance
        //              j could be n if box does not fit through right entrance
        //              if( i == -1 and j == n ) then no box fits
        //              if( i == -1 and j < n  ) we can only load from right side
        //              if( i > -1  and j == n ) we can only load from left side
        //              if( i > -1  and j < n  ), meaning the box gets stuck somewhere
        //                 we put the box in smallest room no matter from either end and with that
        //                 have two warehouses to choose from
        //              if the smallest box fits through the entire warehouse from left and right
        //                 then we put it in the smallest room, if multiple smallest rooms,
        //                 it doesn't matter which one we chose

        // try from the left
        int mn = INT_MAX, mn_pos;
        int i = 0;
        for(; i < n; ++i) {
            if( boxes[0] > warehouse[i] ) {
                i -= 1;
                break;
            }
            if( warehouse[i] <= mn ) {
                mn = warehouse[i];
                mn_pos = i;
            }
        }

        // smallest box fits through entire warehouse
        if( i == n ) {
            if( n == 1 )
                return 1;
            // put smallest box into smallest room
            // if smallest room at pos n-1, we could simplify to one warehouse
            if( mn_pos == n-1 ) {
                return maxBoxesInWarehouse(n-1,boxes,warehouse);
            } else {
                return maxBoxesInTwoWarehouses(mn_pos,boxes,warehouse);
            }
        }

        // try from the right
        int j = n-1;
        for(; j >= 0; --j)
            if( boxes[0] > warehouse[j] ) {
                j += 1;
                break;
            }

        // the 1st box is higher than the warehouse entrance left and right
        if( i == -1 && j == n )
            return 0;

        // we can only load from left side
        if( i > -1  and j == n ) {
            return maxBoxesInWarehouse(i,boxes,warehouse);
        }

        // we can only load from right side
        if( i == -1 and j < n  ) {
            reverse(warehouse.begin(),warehouse.end());
            j = n-1 - j;
            return maxBoxesInWarehouse(j,boxes,warehouse);
        }

        // cout << "i " << i << " j " << j << endl;
        // just split the warehouse at i+1
        return maxBoxesInTwoWarehouses(i+1,boxes,warehouse);

    }
};
