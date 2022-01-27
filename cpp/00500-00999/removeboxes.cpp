
// 546. Remove Boxes
// https://leetcode.com/problems/remove-boxes/
// day 14 August 2021 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3889/





class Solution {
private:
    int mem[100][100][100];
    
    int rec(vector<int>& boxes, int s, int e, int countSame) {
        if( s > e )
            return 0;
        
        if( mem[s][e][countSame] != -1 )
            return mem[s][e][countSame];
        
        // we have a choice

        // countSame is the number of boxes to the left of s with the same color,
        // hence we can move our start index one to the right initially
        int ret = pow(countSame+1,2) + rec(boxes,s+1,e,0);
    
        // but we can also look for a box between s+1 and e inclusive, that
        // has the same color.  If we find one, we can skip the interval s+1 to i-1
        // and add our boxes to the rest.
        // note that the box of the same color could be immideatly adjacent to s
        // also, in which case we simply expand our left side
        for(int i= s+1; i <= e; ++i)
            if( boxes[s] == boxes[i] )
                ret = max(ret,rec(boxes,s+1,i-1,0) + rec(boxes,i,e,countSame+1));
        
        return mem[s][e][countSame] = ret;
    }
    
    
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        
        memset(mem,-1,sizeof mem);
        return rec(boxes,0,n-1,0);
        
    }
};
