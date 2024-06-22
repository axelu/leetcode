
-- 2987. Find Expensive Cities
-- https://leetcode.com/problems/find-expensive-cities/





/* Write your T-SQL query statement below */


declare @national_avg float;
set @national_avg = (select cast(sum(price) as float)/count(listing_id) from Listings);

with avg_by_city
as
(
select
  city,
  cast(sum(price) as float)/count(listing_id) as avg
from
  Listings
group by
  city
)
select city from avg_by_city where avg > @national_avg order by city
