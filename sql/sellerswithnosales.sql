
-- 1607. Sellers With No Sales
-- https://leetcode.com/problems/sellers-with-no-sales/


/* Write your T-SQL query statement below */

select
  seller_name
from
  seller
where
  seller_id not in (
    select distinct seller_id from orders where datepart(year,sale_date) = 2020
  )
order by
  seller_name
