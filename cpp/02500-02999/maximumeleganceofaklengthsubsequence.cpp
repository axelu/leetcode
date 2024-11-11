
// 2813. Maximum Elegance of a K-Length Subsequence
// https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/

class Solution {
public:
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        // edge case
        if( k == 1 ) {
            int mx = 0;
            for(auto& item: items)
                mx = max(mx, item[0]);
            
            return mx + 1;
        }
        
        int n = items.size(); // cout << "n " << n << endl;
        
        sort(items.begin(),items.end(),greater<vector<int>>()); // sort our items in non-decreasing order
        
        int items_selected = 0;
        long long distinct_categories = 0LL;
        int cnt_by_category[n+1];memset(cnt_by_category,0,sizeof cnt_by_category);
        long long total_profit = 0LL;
        long long elegance = 0LL;
        
        long long mx_elegance = 0LL;
        
        // TODO change implementation as this may not scale
        priority_queue<long long,vector<long long>,greater<long long>> by_cat[n+1]; // selected
        
        for(int i = 0; i < n; ++i) {
            // cout << "begin i " << i << " elegance " << elegance << " distinct_categories " << distinct_categories << endl;
            
            long long profit = items[i][0];
            int category = items[i][1];
            
            // if the number of items we have selected so far
            // is less then k, then we simply select the current item
            
            // but if the number of items we have selected so far
            // is equal k, then we have a choice:
            //   select the current item and evict an item from the previously included items OR
            //   don't select the current item
            
            // it is beneficial to select the current item if it increases our elegance after
            // evicting the previously selected item that contributes the least, we are after the max possible increase
            
            if( items_selected < k ) {
                ++items_selected;
                
                ++cnt_by_category[category];            
                if( cnt_by_category[category] == 1 ) {
                    ++distinct_categories;
                    
                } else if( cnt_by_category[category] == 2 ) {

                    
                } else {
                                        
                }
                
                by_cat[category].push(profit);
                
                total_profit += profit; 
                elegance = total_profit + (distinct_categories * distinct_categories);
                
                mx_elegance = elegance;
                
            } else { // items_selected == k
                
                // cases
                // 
                //    if we already have an item of the current category in our selection
                //        then selecting this item will NOT increase our distinct category count, it may decrease our distinct category count
                //    a   same category swap: 
                //            we could swap it in if the item with the smallest profit in the same category is less then profit,
                //            but because we sorted our items in non-decreasing order, this case will never happer
                //            distinct category count stays the same
                //        different category:
                //    b       category with more than one item selected
                //                we could swap it for the item with the smallest profit that is less then profit, 
                //                distinct categories stays the same
                //    c       category with one item selected
                //                we could swap it for the item with the smallest profit that is less then profit, 
                //                distinct categories decreases (our overall elegance may still incrase)
                //
                //    if we do not have an item of the current category in our selection
                //        then selecting this item MAY increase our distinct category count
                //    d   evict item from category with more than one item selected
                //            we could swap it for the item with the smallest profit that is less then profit, 
                //            distinct categories increases
                //    e   evict item from category with one item selected
                //            we could swap it for the item with the smallest profit that is less then profit,
                //            distinct categories stays the same
                //
                // so only case d is what we are after !!!
                
                // if a profit of the current category is already included we know it is better or equal, hence we can skip
                if( by_cat[category].size() >= 1 )
                    continue;
                
                long long val_twoormore = -1LL;
                long long cat_twoormore = -1LL;
                
                for(int j = 1; j <= n; ++j) {
                    if( j == category )
                        continue;
                    
                    if( by_cat[j].size() > 1 ) {
                        if( val_twoormore == -1LL ) {
                            val_twoormore = by_cat[j].top();
                            cat_twoormore = j;
                        } else if( by_cat[j].top() < val_twoormore ) {
                            val_twoormore = by_cat[j].top();
                            cat_twoormore = j;  
                        }
                    }
                }
                
                // note: we may not have one or twoormore
                
                if( val_twoormore != -1 ) {
                    elegance = (total_profit - val_twoormore + profit) + ((distinct_categories+1) * (distinct_categories+1));
                    total_profit = total_profit - val_twoormore + profit;
                    by_cat[cat_twoormore].pop();
                    --cnt_by_category[cat_twoormore];
                    by_cat[category].push(profit);
                    ++cnt_by_category[category]; // should be 1
                    ++distinct_categories;

                    mx_elegance = max(mx_elegance, elegance);

                }
                    
            }
            
            // cout << "end   i " << i << " elegance " << elegance << " distinct_categories " << distinct_categories << endl;
            
        }
        
        
        return mx_elegance;
    }
};


/*
example test cases
[[3,2],[5,1],[10,1]]
2
[[3,1],[3,1],[2,2],[5,3]]
3
[[1,1],[2,1],[3,1]]
3
[[1,2],[10,1]]
1
[[3,3],[2,3],[9,1]]
2
[[1,1],[1,3],[3,3],[6,1]]
3
[[1,3],[3,3],[10,2],[10,1]]
2
[[35,25],[41,8],[8,14],[29,12],[48,5],[33,2],[11,20],[34,26],[40,17],[22,8],[41,26],[13,3],[9,10],[1,15],[12,24],[46,2],[21,11],[33,2],[46,25],[50,13],[7,19],[5,8],[25,18],[34,12],[14,5],[17,14],[19,27]]
19
[[35,25],[41,8],[8,14],[29,12],[48,5],[33,2],[11,20],[34,26],[40,17],[22,8],[41,26],[13,3],[9,10],[1,15],[12,24],[46,2],[21,11],[33,2],[46,25],[50,13],[7,19],[5,8],[25,18],[34,12],[14,5],[17,14],[19,27]]
18
[[35,25],[41,8],[8,14],[29,12],[48,5],[33,2],[11,20],[34,26],[40,17],[22,8],[13,3],[9,10],[1,15],[12,24],[46,2],[21,11],[33,2],[46,25],[50,13],[7,19],[5,8],[25,18],[34,12],[14,5],[17,14],[19,26]]
18
[[5,1],[5,1],[5,1],[1,2],[2,3]]
3
[[10,1],[10,1],[10,1],[10,1],[10,1],[10,1],[10,1],[10,1],[10,1],[10,1],[3,2],[3,3],[3,4],[3,5],[3,6],[3,7],[3,8],[3,9],[3,10],[3,11]]
10
*/

