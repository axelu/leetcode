
// 2172. Maximum AND Sum of Array
// https://leetcode.com/problems/maximum-and-sum-of-array/



class Solution {
private:
    int n, num_slots;
    int* _nums;

    unordered_map<long,int> mem;

    int rec(int slotA, int slotB, int pos) {
        // cout << "rec pos " << pos << endl;
        if( pos == n )
            return 0;

        // state is combining slotA and  slotB
        // for a given slot position as follows:
        // slotA slotB
        //   0     0    2 slots are available
        //   1     0    1 slot is available
        //   0     1    1 slot is available
        //   1     1    slot is not available
        long key = (pos<<18) + (slotA<<9) + slotB;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        //if( mem[slotA & slotB][pos] != -1 )
        //    return mem[slotA & slotB][pos];

        // at each pos we have a choice
        //    we can put nums[pos] in any availabe slot
        //    Note: there will be a slot available always

        int ret = 0;

        for(int i = 1; i <= num_slots; ++i) {
            if( !((slotA >> i) & 1) ) {
                slotA |= 1 << i;
                ret = max(ret,(_nums[pos] & i) + rec(slotA,slotB,pos+1));
                // backtrack
                slotA &= ~(1 << i);
            } else if( !((slotB >> i) & 1) ) {
                slotB |= 1 << i;
                ret = max(ret,(_nums[pos] & i) + rec(slotA,slotB,pos+1));
                // backtrack
                slotB &= ~(1 << i);
            }
        }

        return mem[key] = ret;
    }

public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        n = nums.size();      // 1 <= n <= 2 * numSlots
        num_slots = numSlots; // 1 <= numSlots <= 9
        _nums = nums.data();

        // each slot can hold up to 2 numbers,
        // lets call those slots within the slots A and B
        // slotA and slotB are bitmasks: 0 slot position is available, 1 is taken
        return rec(0,0,0);
    }
};
