
-- 2687. Bikes Last Time Used 
-- https://leetcode.com/problems/bikes-last-time-used/




/* Write your T-SQL query statement below */

select
  bike_number,
  max(end_time) as end_time
from
  bikes
group by
  bike_number
order by
  end_time desc
