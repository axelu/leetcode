
// 568. Maximum Vacation Days
// https://leetcode.com/problems/maximum-vacation-days/




class Solution {
private:
    vector<vector<int>>* pFlights;
    vector<vector<int>>* pDays;
    int numberOfCities,numberOfWeeks;
    int mem[100][100]; // week,city


    int rec(int week, int city) {
        // cout << "rec week " << week << " city " << city << endl;
        if( week == numberOfWeeks )
            return 0;

        if( mem[week][city] != -1 )
           return mem[week][city];


        // we have choices
        // stay in the current city OR fly to another city
        int ret = (*pDays)[city][week] + rec(week+1,city); // stay

        for(int i = 0; i < numberOfCities; ++i) {      // fly
            if( (*pFlights)[city][i] == 0 )
                continue;

            ret = max(ret,(*pDays)[city][week] + rec(week+1,i));

        }

        return mem[week][city] = ret;
    }
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        pFlights = &flights;
        pDays    = &days;

        numberOfCities = flights.size();
        numberOfWeeks  = days[0].size();


        for(int i = 0; i < numberOfWeeks; ++i)
            for(int j = 0; j < numberOfCities; ++j)
                mem[i][j] = -1;


        // start points in week 0 (1st week) are city 0
        // and all cities that city 0 has a connection to
        int ans = rec(0,0);

        for(int i = 1; i < numberOfCities; ++i) {
            if( flights[0][i] == 0 )
                continue;

            ans = max(ans,rec(0,i));

        }


        return ans;
    }
};
