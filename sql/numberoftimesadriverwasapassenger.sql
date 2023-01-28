
-- 2238. Number of Times a Driver Was a Passenger
-- https://leetcode.com/problems/number-of-times-a-driver-was-a-passenger/



/* Write your T-SQL query statement below */


with cte (id,cnt)
as
(
select
  passenger_id as id,
  count(*) as cnt
from
  rides
group by
  passenger_id
)
select
  distinct r.driver_id,
  isnull(cte.cnt,0) as cnt
from
  rides r left outer join cte on r.driver_id = cte.id
