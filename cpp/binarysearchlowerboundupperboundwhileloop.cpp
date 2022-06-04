
// binary search lower bound upper bound while loop will work with duplicates (dups)
// https://www.geeksforgeeks.org/implementing-upper_bound-and-lower_bound-in-c/ 




        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;



        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;



        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s] > target) || s == n )
            --s;


        // binary search greatest element less than target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] < target )
                s = mid+1;
            else
                e = mid;
        }
        if( (s < n && nums[s] >= target) || s == n )
            --s;



