
-- 2082. The Number of Rich Customers
-- https://leetcode.com/problems/the-number-of-rich-customers/

/* Write your T-SQL query statement below */

select
  count(distinct customer_id) as rich_count
from store
where amount > 500
