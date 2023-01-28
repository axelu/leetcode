
-- 2474. Customers With Strictly Increasing Purchases
-- https://leetcode.com/problems/customers-with-strictly-increasing-purchases/



/* Write your T-SQL query statement below */

with yearly_orders
as
(
select
  customer_id,
  datepart(year,order_date) as yr,
  sum(price) as total
from
  orders
group by
  customer_id,datepart(year,order_date)
),
yearly_consecutive_orders
as
(
select
  customer_id,
  yr,
  total,
  case
    when lead(yr) over(partition by customer_id order by yr) is null
    then 1
    else 0
  end as is_last_year,
  case
    when lead(yr) over(partition by customer_id order by yr) is null
    then -1
    else
    case
      when lead(yr) over(partition by customer_id order by yr) = yr+1
      then lead(total) over(partition by customer_id order by yr)
      else 0
    end
  end as next_year_total
from
  yearly_orders
)
select distinct
  customer_id
from
  orders
where
  customer_id not in
    (
        select distinct
          customer_id
        from
          yearly_consecutive_orders
        where
          is_last_year = 0 and
          total >= next_year_total
     )
