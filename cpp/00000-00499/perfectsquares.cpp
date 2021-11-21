
// 279. Perfect Squares
// https://leetcode.com/problems/perfect-squares/




class Solution {
private:
    // binary search largest element less or equal element
    int search(int arr[], int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( arr[mid] == target ) {
            return mid;
        } else if( arr[mid] > target ) {
            return search(arr,s,mid-1,target);
        } else {
            // can we do better?
            int ans = search(arr,mid+1,e,target);
            return ans != -1 ? ans : mid;
        }
    }

public:
    int numSquares(int n) {

        int arr[101];
        int i = 0;
        while(i<=100)
            arr[i++] = i*i;


        // BFS
        queue<array<int,2>> q; // target,step
        q.push({n,0});
        unordered_set<unsigned int> seen;
        unsigned int seenIdx = (unsigned int)n << 16;
        seen.insert(seenIdx);

        int t,rem,step;
        while(!q.empty()) {
            n    = q.front()[0];
            step = q.front()[1];
            q.pop();

            t = search(arr,0,100,n);
            if( t*t == n ) return step+1;

            for(i = 1; i <= t; ++i) {
                rem = n-i*i;
                seenIdx = (unsigned int)rem << 16;
                seenIdx |= (step+1);

                if( seen.count(seenIdx) )
                    continue;

                seen.insert(seenIdx);
                q.push({rem,step+1});
            }
        }

        return -1;
    }
};
