
// 1054. Distant Barcodes
// https://leetcode.com/problems/distant-barcodes/


class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();

        unordered_map<int,int> um; // val, count
        for(int x: barcodes)
            ++um[x];

        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
            return a.second < b.second;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> pq(cmp);
        for(auto p: um)
            pq.push(p);

        // place first
        auto p = pq.top();
        pq.pop();
        barcodes[0] = p.first;
        --p.second;
        if( p.second > 0 )
            pq.push(p);

        for(int i = 1; i < n; ++i) {

            queue<pair<int,int>> parking_lot;
            while( pq.top().first == barcodes[i-1] ) {
                parking_lot.push(pq.top());
                pq.pop();
            }
            // we should have at least one left,
            // so no check for empty needed
            auto p = pq.top();
            pq.pop();
            barcodes[i] = p.first;
            --p.second;
            if( p.second > 0 )
                pq.push(p);
            while( !parking_lot.empty() ) {
                pq.push(parking_lot.front());
                parking_lot.pop();
            }
        }

        return barcodes;
    }
};
