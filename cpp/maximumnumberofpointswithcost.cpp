


// 1937. Maximum Number of Points with Cost
// https://leetcode.com/problems/maximum-number-of-points-with-cost/
// https://leetcode.com/contest/weekly-contest-250/problems/maximum-number-of-points-with-cost/

// for a good explanation see here
// https://leetcode.com/problems/maximum-number-of-points-with-cost/discuss/1344908/Python-3-DP-Explanation-with-pictures.

class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int m = points.size();      // rows
        int n = points[0].size();   // cols
        
        long long ans = LLONG_MIN;

        int i,j,p;
        
        if( m == 1 ) {
            for(j = 0; j < n; ++j)
                ans = max(ans,(long long)points[0][j]);
            return ans;    
        }
        if( n == 1 ) {
            ans = 0LL;
            for(i = 0; i < m; ++i)
                ans += (long long)points[i][0];
            return ans;    
        }
        
        long long mem[2][n];memset(mem,0,sizeof mem);
        
        
        // bottom up
        int memRow = 0;
        for(i = m-1; i >= 0; --i) {     // current row
            
            // at each col we have a choice to go left, right or straight
            // the optimal choice is to go where the max is
            // to figure where the max is, we would need to go to each col and
            // then go to each col of the preceding row, that would lead to n*n asymptotic 
            /*
            // reset mem
            for(int j = 0; j < n; ++j)
               mem[memRow][j] = LLONG_MIN;

            for(int p = 0; p < n; ++p) {            // col in the current row

                long long base = (long long)points[i][p] + mem[!memRow][p];


                for(int j = 0; j < n; ++j)        // col we are coming from in the row above
                    mem[memRow][j] = max(mem[memRow][j], base - (long long)abs(j-p) );

            }
            memRow = !memRow;
            */
            
            // instead, we are going to determine the max to the left of a given col
            // and the max to the right of a given col, including applying the cost
            
            // max to the left
            long long l[n];
            l[0] = mem[!memRow][0]; // there is nothing to the left
            for(j = 1; j < n; ++j)
                l[j] = max(mem[!memRow][j],l[j-1]-1);
            
            // max to the right
            long long r[n];
            r[n-1] = mem[!memRow][n-1]; // there is nothing to the right
            for(j = n-2; j >= 0; --j)
                r[j] = max(mem[!memRow][j],r[j+1]-1);
            
            
            for(j = 0; j < n; ++j)
               mem[memRow][j] = (long long)points[i][j] + max(l[j],r[j]);
                
                 
            
            memRow = !memRow;
        }
        
        // top row
        ans = LLONG_MIN;
        for(j = 0; j < n; ++j)
            ans = max(ans,mem[!memRow][j]);
       
      
        return ans;
    }
};
