
// 42. Trapping Rain Water
// https://leetcode.com/problems/trapping-rain-water/




class Solution {
public:
    int trap(vector<int>& height) {
        // 0 <= n <= 30000
        // 0 <= height[i] <= 100000
        // -> worst case: height[0] = 100000, height[29999] = 100000, height[1]...height[29998] = 0
        //    result: 2999800000 integer overflow
        //            2147483647 INT_MAX


        int n = height.size();
        if( n < 3 ) return 0;

        long ans = 0;

        array<long,2> mx{height[0],0}; // height,pos
        stack<array<long,2>> stck;     // height,width
        long prev,curr,prevH,prevW;
        for(int i = 1; i < n; ++i) {
            prev = height[i-1];
            curr = height[i];

            if( curr > prev ) {
                // there is something to be trapped potentially
                if( mx[0] == prev ) {
                    mx[0] = curr;
                    mx[1] = i;
                } else {

                    while(!stck.empty()) {
                        prevH = stck.top()[0];
                        prevW = stck.top()[1];
                        stck.pop();

                        if( !stck.empty()) {
                            if( stck.top()[0] > curr ) {
                                ans += (curr-prevH)*prevW;
                                stck.push({curr,prevW+1});
                                break;
                            } else if( stck.top()[0] == curr ) {
                                ans += (curr-prevH)*prevW;
                                stck.top()[1] += prevW+1;
                                break;
                            } else { // stck.top()[0] < curr
                                ans += (stck.top()[0]-prevH)*prevW;
                                stck.top()[1] += prevW;
                            }
                        } else {
                            ans += (min(mx[0],curr)-prevH)*prevW;
                            if( curr < mx[0] ) {
                                stck.push({curr,i-mx[1]});
                                break;
                            }
                        }
                    }

                }

                if( curr >= mx[0] ) {
                    mx[0] = curr;
                    mx[1] = i;
                }

            } else if( curr == prev ) {
                if( mx[0] == prev ) {
                    mx[1] = i;
                }
                if( !stck.empty() )
                    ++stck.top()[1];
            } else { // curr < prev
                stck.push({curr,1});
            }

            // cout << "i " << i;
            // cout << " mxh " << mx[0] << " ans " << ans << " stck.size " << stck.size() << endl;

        }
        return ans;
    }
};
