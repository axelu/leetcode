
-- 2329. Product Sales Analysis V
-- https://leetcode.com/problems/product-sales-analysis-v/



/* Write your T-SQL query statement below */

select
  t.user_id,
  sum(t.total) as spending
from (
    select
      s.sale_id,
      s.product_id,
      p.price,
      s.user_id,
      s.quantity,
      p.price*s.quantity as total
    from sales as s inner join product p on s.product_id = p.product_id
) t
group by t.user_id
order by 'spending' desc, t.user_id
