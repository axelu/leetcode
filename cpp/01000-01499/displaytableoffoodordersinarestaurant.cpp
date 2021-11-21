
// 1418. Display Table of Food Orders in a Restaurant
// https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/





class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        
        set<string> foods;
        set<string>::iterator f;
        
        int table,cnt;
        string food;
        map<int,unordered_map<string,int>> tableFoodCnt;
        map<int,unordered_map<string,int>>::iterator f1;
        unordered_map<string,int>::iterator f2;
        for(auto order : orders) {
            table = stoi(order[1]);
            food  = order[2]; foods.insert(food);
            
            f1 = tableFoodCnt.find(table);
            if( f1 == tableFoodCnt.end() ) {
                tableFoodCnt.insert({table,{{food,1}}});
            } else {
                f2 = f1->second.find(food);
                if( f2 == f1->second.end() ) {
                    f1->second.insert({food,1});
                } else {
                    ++f2->second;
                }
            }
        }
        
        vector<vector<string>> ans(tableFoodCnt.size()+1,vector<string>(foods.size()+1,"0"));
        // header = row zero
        ans[0][0] = "Table";
        for(auto it = foods.begin(); it != foods.end(); ++it)
           ans[0][distance(foods.begin(),it)+1] = *it;
        
        int r,c;
        for(auto ito = tableFoodCnt.begin(); ito != tableFoodCnt.end(); ++ito) {
            r = distance(tableFoodCnt.begin(),ito)+1;
            
            // table number = column zero
            table = ito->first; // cout << table << endl;
            ans[r][0] = to_string(table);
            
            // foods
            for(auto iti = ito->second.begin(); iti != ito->second.end(); ++iti) {
                
                // food and count
                food = iti->first;  // cout << food << endl;
                cnt  = iti->second; // cout << cnt << endl;
                
                // get column for the food
                f = foods.find(food);
                c = distance(foods.begin(),f)+1;
                
                ans[r][c] = to_string(cnt);
            }
        }
        
        return ans;
    }
};
