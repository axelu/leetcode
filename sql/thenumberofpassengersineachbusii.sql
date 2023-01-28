
-- 2153. The Number of Passengers in Each Bus II
-- https://leetcode.com/problems/the-number-of-passengers-in-each-bus-ii/


/* Write your T-SQL query statement below */

-- see 2142. The Number of Passengers in Each Bus I
--     https://leetcode.com/problems/the-number-of-passengers-in-each-bus-i/
-- first 3 steps taken from that solution

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

passenger_arrival
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
),

-- bus usage if each bus had unlimited capacity
bus_usage
as
(
select
  row_number() over(order by b.arrival_time) as rownbr, -- no guarantee that bus_id is increasing, hence row_number
  b.bus_id,
  b.capacity,
  isnull(pa.passenger_cnt,0) as passenger_cnt
from
  buses b left join passenger_arrival pa on b.bus_id = pa.bus_id
),

-- now we need to go bus by bus and see how many (if any) passengers were left behind
--   by the prior busses based on each bus's capacity

bus_usage_with_capacity -- recursive cte
as
(
select
  rownbr,
  bus_id,
  capacity,
  passenger_cnt,
  case
    when passenger_cnt - capacity <= 0
    then 0
    else passenger_cnt - capacity
  end as waiting
from
  bus_usage
where
  rownbr = 1 -- first arriving bus
union all
select
  bu.rownbr,
  bu.bus_id,
  bu.capacity,
  bu.passenger_cnt + buc.waiting as passenger_cnt,
  case
    when bu.passenger_cnt + buc.waiting - bu.capacity <= 0
    then 0
    else bu.passenger_cnt + buc.waiting - bu.capacity
  end as waiting
from
  bus_usage_with_capacity buc inner join bus_usage bu on bu.rownbr = buc.rownbr + 1
)

select
  bus_id,
  case when waiting > 0 then capacity else passenger_cnt end as passengers_cnt
from
  bus_usage_with_capacity
order by
  bus_id

