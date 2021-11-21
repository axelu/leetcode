
// 1980. Find Unique Binary String
// https://leetcode.com/problems/find-unique-binary-string/




class Solution {
private:
    // binary search
    int search(vector<int>& arr, int s, int e, int target) {
        if( s > e )
            return -1;
        
        int mid = s + ((e-s)/2);
        if( arr[mid] == target ) {
            return mid;
        } else if( arr[mid] > target ) {
            return search(arr,s,mid-1,target);
        } else {
            // arr[mid] < target
            return search(arr,mid+1,e,target);
        }
    }
    
    int binarystring2int(string& s, int n) {
        int ret = 0;
        for(int i = n-1; i >= 0; --i)
            if( s[i] == '1' )
                ret |= 1 << n-1-i;
        return ret;        
    }
    
    string int2binarystring(int x, int n) {
        string ret(n,'0');
        for(int i = 0; i < n; ++i)
            if( (x>>i) & 1 )
                ret[n-1-i] = '1';
        return ret;
    }
    
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        
        int i;
        
        vector<int> v(n);
        for(i = 0; i < n; ++i) {
            v[i] = binarystring2int(nums[i],n);
        }        
        sort(begin(v),end(v));
        
        int imax = pow(2,n);
        for(i = 0; i < imax; ++i)
            if( search(v,0,n-1,i) == -1 )
                break;
 
        return int2binarystring(i,n);
    }
};
