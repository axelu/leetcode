
-- 2324. Product Sales Analysis IV
-- https://leetcode.com/problems/product-sales-analysis-iv/



/* Write your T-SQL query statement below */


select
  r.user_id,
  r.product_id
from (
    select
      o.user_id,
      o.product_id,
      rank() over(partition by o.user_id order by o.total desc) as rnk
    from (
       select
         t.user_id,
         t.product_id,
         sum(sale) as total
        from (
            select
              s.sale_id,
              s.product_id,
              p.price,
              s.user_id,
              s.quantity,
              s.quantity * p.price as sale
            from
              sales s inner join product p on s.product_id = p.product_id
          ) t
        group by t.user_id,t.product_id
      ) o
  ) r
where r.rnk = 1
