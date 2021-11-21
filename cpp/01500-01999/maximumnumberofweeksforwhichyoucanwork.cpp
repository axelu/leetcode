
// 1953. Maximum Number of Weeks for Which You Can Work
// https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/
// https://leetcode.com/contest/weekly-contest-252/problems/maximum-number-of-weeks-for-which-you-can-work/





class Solution {
private:
    /*
    long long rec(vector<int>& milestones, int n, int parent) {

        cout << "rec parent " << parent << endl;
        for(int i = 0; i < n; ++i)
            cout << milestones[i] << " ";
        cout << endl;


        long long ret = 0;

        // we can go to any index other than the one we came from
        // it does not make sense to go to a project that does
        // not have any more milestones left
        for(int i = 0; i < n; ++i) {
            if( i == parent || milestones[i] == 0 )
                continue;

            --milestones[i];
            ret = max(ret,1LL+rec(milestones,n,i));
            // backtrack
            ++milestones[i];
        }

        return ret;
    }
    */
public:
    long long numberOfWeeks(vector<int>& milestones) {
        int n = milestones.size();
        if( n == 1 )
            return 1;
        if( n == 2 )
            if( milestones[0] == milestones[1] )
                return milestones[0]+milestones[1];
            else
                return 2*min(milestones[0],milestones[1])+1;

        // worst case
        // 10^5 projects and each project has 10^9 milestones
        // -> 10^14 weeks
        // a top-down solution is not feasable
        // return rec(milestones,n,-1);

        sort(milestones.begin(),milestones.end());

        long long sum = accumulate(milestones.begin(),milestones.end(),0LL);

        // observation
        // if the largest and second to largest project have equal number
        // of milestones, we can always complete all projects alternating
        if( milestones[n-1] == milestones[n-2] )
            return sum;

        // based on observation, the question becomes, can we equalize
        // the largest to the second largest milestones

        int d = milestones[n-1] - milestones[n-2];
        int l = 0; // left index
        while( l != n-2 ) {

            if( d <= milestones[l] )
                return sum;

            d -= milestones[l];
            ++l;
        }

        // we are left with the largest and second largest
        // if the remaining difference is 0 or 1, we can
        // finish all projects, else only finish 1 project
        // of the remaining difference
        if( d <= 1 )
            return sum;
        else
            return sum-(long long)(d-1);

    }
};
