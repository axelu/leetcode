
// 1298. Maximum Candies You Can Get from Boxes
// https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/

class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        
        unordered_set<int> keys_i_have;
        unordered_set<int> boxes_i_have;

        // BFS
        queue<int> q;

        // process the initial boxes we have
        // if the box is open add it to our queue
        // otherwise add it to our list of boxes
        for(int k : initialBoxes)
            if( status[k] )
                q.push(k);
            else
                boxes_i_have.insert(k);

        int ans = 0;
        
        while( !q.empty() ) {
            int box = q.front();
            q.pop();
            
            // harvest the contents of the current box
            // harvest the candies
            ans += candies[box];
            // harvest the contained boxes
            for(int i = 0; i < containedBoxes[box].size(); ++i) {
                int containedBox = containedBoxes[box][i];
                // if the containedBox is open OR
                // we have a key for it, add it to our queue
                if( status[containedBox] ) {
                    q.push(containedBox);
                } else if( keys_i_have.count(containedBox) ) {
                    q.push(containedBox);
                    keys_i_have.erase(containedBox); // house keeping
                } else {
                    boxes_i_have.insert(containedBox);
                }
            }
            // harvest the keys
            for(int i = 0; i < keys[box].size(); ++i) {
                int key = keys[box][i];
                // if we have the box that this key opens,
                // then we open that box aka add the box to our queue
                // unless the box was open to begin with
                if( status[key] == 0 )
                    if( boxes_i_have.count(key) ) {
                        q.push(key);
                        boxes_i_have.erase(key); // house keeping
                    } else {
                        keys_i_have.insert(key);
                    }
            }
        }
        
        return ans;
    }
};
