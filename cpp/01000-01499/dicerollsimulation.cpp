
// 1223. Dice Roll Simulation
// https://leetcode.com/problems/dice-roll-simulation/


class Solution {
private:
    long mod = 1000000007;
    int N;
    int roll_max_org[6];
    
    int mem[5000][6];
    
    
    long rec(long roll, int dice) {
        // cout << "rec roll " << roll << " dice " << dice << endl;
        if( roll == N )
            return 1;
        
        if( mem[roll][dice] != -1 )
            return mem[roll][dice];
                
        long ret = 0;
        
        for(int i = 1; i <= roll_max_org[dice]; ++i) {
            // roll our dice i times up to max repetition times
            // and if there are rolls left, proceed to any other dice
            if( roll + i == N ) {
                ret = (ret + 1) % mod;
                break;
            }
            for(int j = 0; j < 6; ++j) {
                if( j == dice )
                    continue;
                ret = (ret + rec(roll+i,j)) % mod;
            }
        }
                
        return mem[roll][dice] = ret;
    }
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        N = n;
        for(int i = 0; i < 6; ++i)
            roll_max_org[i] = rollMax[i];
        
        memset(mem,-1,sizeof mem);
        long ans = 0;
        for(int i = 0; i < 6; ++i)
            ans = (ans + rec(0,i)) % mod;

        return ans;
    }
};







// passes but slow solution

class Solution {
private:
    long mod = 1000000007;
    int N;
    int roll_max_org[6];

    unordered_map<long,long> seen;


    long rec(long roll, int mask[]) {
        if( roll == N )
            return 1;

        long key = (roll<<24) + (mask[5]<<20) + (mask[4]<<16) + (mask[3]<<12) + (mask[2]<<8) + (mask[1]<<4) + mask[0];
        auto f = seen.find(key);
        if( f != seen.end() )
            return f->second;

        // at each roll we have a choice
        //    any dice from 1 - 6 can be rolled
        //    if we have not reached its rollMax limit
        //    if we roll a give dice, it resets all
        //    other rollMax limits

        long ret = 0;

        int mask_new[6];
        for(int i = 0; i < 6; ++i)
            mask_new[i] = roll_max_org[i];
        for(int i = 0; i < 6; ++i) {
            if( mask[i] == 0 )
                continue;

            mask_new[i] = mask[i] - 1;
            ret = (ret + rec(roll+1,mask_new)) % mod;
            // backtrack
            mask_new[i] = roll_max_org[i];
        }

        return seen[key] = ret;
    }
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        N = n;
        for(int i = 0; i < 6; ++i)
            roll_max_org[i] = rollMax[i];

        return rec(0,rollMax.data());
    }
};
