
-- 1934. Confirmation Rate
-- https://leetcode.com/problems/confirmation-rate/



/* Write your T-SQL query statement below */


with confirmed (user_id,cnt)
as
(
select
  user_id,
  count(*)
from
  confirmations
where
  [action] = 'confirmed'
group by
  user_id
),
requested (user_id,cnt)
as
(
select
  user_id,
  count(*)
from
  confirmations
group by
  user_id
)
select
  s.user_id,
  case
    when c.cnt is null then 0 else round(cast(c.cnt as decimal)/r.cnt,2)
  end as confirmation_rate
from
  signups s
    left outer join confirmed c on s.user_id = c.user_id
    left outer join requested r on s.user_id = r.user_id
