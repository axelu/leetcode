
-- 1581. Customer Who Visited but Did Not Make Any Transactions
-- https://leetcode.com/problems/customer-who-visited-but-did-not-make-any-transactions/



/* Write your T-SQL query statement below */

select
  v.customer_id,
  count(*) as count_no_trans
from visits v
where v.visit_id not in(
    select visit_id from transactions
  )
group by v.customer_id
