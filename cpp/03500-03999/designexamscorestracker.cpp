
// 3709. Design Exam Scores Tracker
// https://leetcode.com/problems/design-exam-scores-tracker/



class ExamTracker {
private:
    vector<long long> bit; // binary indexed tree, 0-indexed, range query (sum), point update (addition)
    int nxt_idx;
    vector<int> times;

    long long sum(int r) {
        long long ret = 0LL;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        int n = bit.size();
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    // binary search
    int lower_bound(int target) {
        int n = times.size();
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= times[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && times[s] < target )
            ++s;

        return s;
    }

    // binary search
    int gelttoret(int target) {
        int n = times.size();
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( times[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && times[s] > target) || s == n )
            --s;

        return s;
    }

public:
    ExamTracker() {
        // constraint
        // At most 1e5 calls will be made in total to record() and totalScore()
        bit.assign(100000,0LL);
        nxt_idx = 0;
    }

    void record(int time, int score) {
        // calls to record() will be made with strictly increasing time
        int idx = times.size();
        add(idx, score);
        times.push_back(time);
        return;
    }

    long long totalScore(int startTime, int endTime) {
        int l = lower_bound(startTime);
        int r = gelttoret(endTime);
        return sum(l,r);
    }
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */
