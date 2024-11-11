
// 3269. Constructing Two Increasing Arrays
// https://leetcode.com/problems/constructing-two-increasing-arrays/




class Solution {
private:
    int nxt(int x, int last) {

        if( x == 0 ) {     // we must proceed with even
            if( (last + 1) % 2 == 0 )
                return last + 1;
            else
                return last + 2;

        } else {          // we must proceed with odd
            if( (last + 1) % 2 == 1 )
                return last + 1;
            else
                return last + 2;
        }
    }

public:
    int minLargest(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(); // 0 <= nums1.length <= 1000
        int n2 = nums2.size(); // 1 <= nums2.length <= 1000

        // 0 -> even positive integer;  1 -> odd positive integer

        auto cmp = [](array<int,3>& a, array<int,3>& b) {
            return a[0] > b[0];
        };
        priority_queue<array<int,3>, vector<array<int,3>>, decltype(cmp)> pq(cmp);

        int seen[1001][1001];memset(seen,-1,sizeof seen);

        pq.push({0,0,0}); // last int, next pos in nums1, next pos in nums2
        while( true ) {
            int last = pq.top()[0];
            int pos1 = pq.top()[1];
            int pos2 = pq.top()[2];
            pq.pop();
            // cout << "last " << last << " pos1 " << pos1 << " pos2 " << pos2 << " pq.size() " << pq.size() << endl;

            if( pos1 == n1 && pos2 == n2 ) { // we are done
                return last;

            } else if( pos1 == n1 ) {        // we can only proceed in nums2
                int last_new = nxt(nums2[pos2], last);
                if( seen[pos1][pos2+1] == -1 ||  seen[pos1][pos2+1] > last_new ) {
                    pq.push({last_new, pos1, pos2 + 1});
                    seen[pos1][pos2+1] = last_new;
                }

            } else if( pos2 == n2 ) {        // we can only proceed in nums1
                int last_new = nxt(nums1[pos1], last);
                if( seen[pos1+1][pos2] == -1 ||  seen[pos1+1][pos2] > last_new ) {
                    pq.push({last_new, pos1 + 1, pos2});
                    seen[pos1+1][pos2] = last_new;
                }

            } else {
                int last_new1 = nxt(nums1[pos1], last);
                if( seen[pos1+1][pos2] == -1 ||  seen[pos1+1][pos2] > last_new1 ) {
                    pq.push({last_new1, pos1 + 1, pos2});
                    seen[pos1+1][pos2] = last_new1;
                }

                int last_new2 = nxt(nums2[pos2], last);
                if( seen[pos1][pos2+1] == -1 ||  seen[pos1][pos2+1] > last_new2 ) {
                    pq.push({last_new2, pos1, pos2 + 1});
                    seen[pos1][pos2+1] = last_new2;
                }
            }
        }

        return -1; // we should never get here
    }
};
