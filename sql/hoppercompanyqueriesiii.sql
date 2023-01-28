
-- 1651. Hopper Company Queries III
-- https://leetcode.com/problems/hopper-company-queries-iii/



/* Write your T-SQL query statement below */


with window_ids  -- rolling 3 months, e.g. 1 => Jan, Feb, Mar, 2 => Feb, Mar, Apr
as
(
    select * from ( values
        (1),(2),(3),(4),(5),(6),(7),(8),(9),(10)
    ) t(window_id)
),
rides_2020
as
(
select
  datepart(month,r.requested_at) as month,
  a.ride_distance,
  a.ride_duration
from
  rides r join acceptedrides a on r.ride_id = a.ride_id
where
  datepart(year,r.requested_at) = 2020
),
rolling_threemonth_2020
as
(
select
  w.window_id,
  r.month,
  r.ride_distance,
  r.ride_duration
from
  window_ids w join rides_2020 r on w.window_id <= r.month and r.month <= w.window_id + 2
)
select
  w.window_id as month,
  case
    when sum(rtm.ride_distance) is null
    then 0
    else round(cast(sum(rtm.ride_distance) as decimal)/3,2)
  end as average_ride_distance,
  case
    when sum(rtm.ride_duration) is null
    then 0
    else round(cast(sum(rtm.ride_duration) as decimal)/3,2)
  end as average_ride_duration
from
  window_ids w left join rolling_threemonth_2020 rtm on w.window_id = rtm.window_id
group by
  w.window_id
order by
  w.window_id
