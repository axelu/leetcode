
-- 2066. Account Balance
-- https://leetcode.com/problems/account-balance/



/* Write your T-SQL query statement below */

-- (account_id, day) is the primary key for table transaction
-- hence there can only be one transaction per account per day

select
  t.account_id
  ,t.day
  ,sum(case when type = 'Withdraw' then -t.amount else t.amount end) over (partition by t.account_id order by t.day) as balance
from
  transactions t
order by
  t.account_id
