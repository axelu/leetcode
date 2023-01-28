
-- 1285. Find the Start and End Number of Continuous Ranges
-- https://leetcode.com/problems/find-the-start-and-end-number-of-continuous-ranges/



/* Write your T-SQL query statement below */

select
  p.log_id as start_id,
  p.tt1 as end_id
from (

select
  o.log_id,
  o.tpe,
  lead(o.log_id,1) over(order by o.log_id,o.tpe) as tt1
from (

select
  t.log_id,
  1 as tpe -- start_id
from (
-- start_id
select
  log_id,
  case
    when
      log_id - lag(log_id,1,log_id) over(order by log_id) = 1 then
        lag(log_id,1,log_id) over(order by log_id)
    else
        log_id
  end as pre
from
  logs
) t
where t.log_id = t.pre

union

select
  t.log_id,
  2 as tpe -- end_id
from (
-- end_id
select
  log_id,
  case
    when
      lead(log_id,1,log_id) over(order by log_id) - log_id = 1 then
        lead(log_id,1,log_id) over(order by log_id)
    else
        log_id
  end as nxt
from
  logs
) t
where t.log_id = t.nxt

) o

) p
where p.tpe = 1
order by p.log_id
