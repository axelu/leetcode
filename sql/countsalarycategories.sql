
-- 1907. Count Salary Categories
-- https://leetcode.com/problems/count-salary-categories/




/* Write your T-SQL query statement below */

select
  'Low Salary' as category,
  count(*) as accounts_count
from
(
select
  account_id
from
  accounts
where
  income < 20000
) t

union

select
  'Average Salary',
  count(*)
from
(
select
  account_id
from
  accounts
where
  income between 20000 and 50000
) t

union

select
  'High Salary',
  count(*)
from
(
select
  account_id
from
  accounts
where
  income > 50000
) t
