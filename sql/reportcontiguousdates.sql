
-- 1225. Report Contiguous Dates
-- https://leetcode.com/problems/report-contiguous-dates/




/* Write your T-SQL query statement below */

with states
as
(
  select 'failed' as state,fail_date as dt from failed where fail_date between '2019-01-01' and '2019-12-31'
  union
  select 'succeeded',success_date from succeeded where success_date between '2019-01-01' and '2019-12-31'
),
states_start_end
as
(
select
  o.state,
  o.dt,
  case
    when lag(o.state,1) over(order by dt) is null or lag(o.state,1) over(order by dt) <> o.state
    then 1
    else 0
  end as start,
  case
    when lead(o.state,1) over(order by dt) is null or lead(o.state,1) over(order by dt) <> o.state
    then 1
    else 0
  end as finish
from
  states o
)
select
  sse.state as period_state,
  (select top 1 i.dt from states_start_end i where i.state = sse.state and i.dt <= sse.dt and i.start = 1 order by i.dt desc) as start_date,
  sse.dt as end_date
from
  states_start_end sse
where
  finish = 1
order by
  2
