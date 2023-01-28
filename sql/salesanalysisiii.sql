
-- 1084. Sales Analysis III
-- https://leetcode.com/problems/sales-analysis-iii/



/* Write your T-SQL query statement below */

select distinct
  p.product_id
  ,p.product_name
from sales s inner join product p on s.product_id = p.product_id
where
  p.product_id in (
    select product_id from sales where sale_date >= '2019-01-01' and sale_date <= '2019-03-31'
  )
  and p.product_id not in (
    select product_id from sales where sale_date < '2019-01-01' or sale_date > '2019-03-31'
  )
