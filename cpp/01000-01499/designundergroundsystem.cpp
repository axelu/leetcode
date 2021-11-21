
// 1396. Design Underground System
// https://leetcode.com/problems/design-underground-system/
// day 20 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/590/week-3-march-15th-march-21st/3678/



class UndergroundSystem {
private:
    unordered_map<int,pair<string,int>> currRiders; // id,{stationName,checkInTime}
    unordered_map<string,pair<int,int>> travel; // startStation::endStation,{totalTravelTime,count}

public:
    UndergroundSystem() {

    }

    void checkIn(int id, string stationName, int t) {
        currRiders.insert({id,{stationName,t}});
    }

    void checkOut(int id, string stationName, int t) {
        auto f = currRiders.find(id);
        string startStation = f->second.first;
        int checkInTime = f->second.second;
        currRiders.erase(id);

        auto p = travel.insert({startStation+"::"+stationName,{t-checkInTime,1}});
        if( !p.second ) {
            p.first->second.first += t-checkInTime;
            ++p.first->second.second;
        }
    }

    double getAverageTime(string startStation, string endStation) {
        auto f = travel.find(startStation+"::"+endStation);
        return (double)f->second.first/(double)f->second.second;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
