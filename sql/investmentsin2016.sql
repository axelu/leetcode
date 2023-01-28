
-- 585. Investments in 2016
-- https://leetcode.com/problems/investments-in-2016/




/* Write your T-SQL query statement below */


with a -- multiple lat,lon
as
(
select
  lat,
  lon
from
  insurance
group by
  lat,lon
having
  count(*) > 1
)
select
  round(sum(i.tiv_2016),2) as tiv_2016
from
  insurance i left join a on i.lat = a.lat and i.lon = a.lon
where
  i.tiv_2015 in (select tiv_2015 from insurance group by tiv_2015 having count(*) > 1) and
  a.lat is null

