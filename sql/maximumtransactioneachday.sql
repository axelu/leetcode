
-- 1831. Maximum Transaction Each Day
-- https://leetcode.com/problems/maximum-transaction-each-day/



/* Write your T-SQL query statement below */

select
  t.transaction_id
from (
    select
      transaction_id,
      day,
      amount,
      rank() over(partition by CAST(day AS date) order by amount desc) as rnk
    from
      transactions
  ) t
where
  t.rnk = 1
order by
  t.transaction_id
