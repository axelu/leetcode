
-- 1543. Fix Product Name Format
-- https://leetcode.com/problems/fix-product-name-format/



/* Write your T-SQL query statement below */

select
  lower(trim(product_name)) as product_name,
  format(sale_date, 'yyyy-MM') as sale_date,
  count(*) as total
from
  sales
group by lower(trim(product_name)),format(sale_date, 'yyyy-MM')
order by lower(trim(product_name)),format(sale_date, 'yyyy-MM')
