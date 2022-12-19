
-- 1587. Bank Account Summary II
-- https://leetcode.com/problems/bank-account-summary-ii/

/* Write your T-SQL query statement below */

select
  u.name as name,
  sum(t.amount) as balance
from users u, transactions t
where u.account = t.account
group by u.name
having sum(t.amount) > 10000
