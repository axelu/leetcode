
// 769. Max Chunks To Make Sorted
// https://leetcode.com/problems/max-chunks-to-make-sorted/




class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();

        priority_queue<int> pq;
        int chunks = 0;
        
        for(int i = 0; i < n; ++i) {
            pq.push(arr[i]);

            if( pq.top() == i ) {
                ++chunks;
                priority_queue<int> pq_new;
                pq = pq_new;
            }
        }

        return chunks;
    }
};
