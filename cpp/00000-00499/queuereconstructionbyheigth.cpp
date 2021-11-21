
// 406. Queue Reconstruction by Height
// https://leetcode.com/problems/queue-reconstruction-by-height/



class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {

        // sort people by height desc and number of people w/ or greater height in front asce
        sort(people.begin(),people.end(),[](const vector<int>& a, const vector<int>& b){
           if( a[0] > b[0] ) {
               return true;
           } else if( a[0] == b[0] ) {
               if( a[1] < b[1] ) {
                   return true;
               }
           }
            return false;

        });

        // insert into answer
        // smaller people are 'invisible' to taller people, hence starting with
        // tallest person
        vector<vector<int>> ans;
        int n = people.size();
        for(int i = 0; i < n; ++i)
            ans.insert(ans.begin()+people[i][1],people[i]);

        return ans;
    }
};
