
-- 2142. The Number of Passengers in Each Bus I
-- https://leetcode.com/problems/the-number-of-passengers-in-each-bus-i/




/* Write your T-SQL query statement below */

-- we will assume the 1st bus and passenger arriving at 0 <= arrival_time

with bus_schedule
as
(
select
  bus_id,
  isnull(lag(arrival_time,1) over(order by arrival_time),-1) as prior_bus,
  arrival_time
from
  buses
),
bus_usage
as
(
select
  b.bus_id,
  count(*) as passenger_cnt
from
  bus_schedule b join passengers p on
    b.prior_bus < p.arrival_time and b.arrival_time >= p.arrival_time
group by
  b.bus_id
)
select
  b.bus_id,
  isnull(bu.passenger_cnt,0) as passengers_cnt
from
  buses b left join bus_usage bu on b.bus_id = bu.bus_id
order by
  b.bus_id
