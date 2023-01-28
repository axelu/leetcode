
-- 2372. Calculate the Influence of Each Salesperson
-- https://leetcode.com/problems/calculate-the-influence-of-each-salesperson/


/* Write your T-SQL query statement below */

with cte (sale_id,price,customer_id,salesperson_id)
as (
  select
    s.sale_id
    ,s.price
    ,s.customer_id
    ,c.salesperson_id
  from sales s inner join customer c on s.customer_id = c.customer_id
)
select
  p.salesperson_id
  ,p.name
  ,sum(isnull(o.price,0)) as total
from
  salesperson p left outer join cte o on p.salesperson_id = o.salesperson_id
group by
  p.salesperson_id,p.name

