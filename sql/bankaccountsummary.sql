
-- 1555. Bank Account Summary
-- https://leetcode.com/problems/bank-account-summary/




/* Write your T-SQL query statement below */

with cte
as
(
select
  user_id,
  credit as amount
from
  users
union all
select
  paid_by,
  -amount
from
  transactions
union all
select
  paid_to,
  amount
from
  transactions
)
select
  u.user_id,
  u.user_name,
  sum(cte.amount) as credit,
  case when sum(cte.amount) < 0 then 'Yes' else 'No' end as credit_limit_breached
from
  users u left join cte on u.user_id = cte.user_id
group by
  u.user_id,u.user_name
