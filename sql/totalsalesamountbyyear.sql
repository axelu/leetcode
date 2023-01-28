
-- 1384. Total Sales Amount by Year
-- https://leetcode.com/problems/total-sales-amount-by-year/




/* Write your T-SQL query statement below */

with sale_details
as
(
select
  s.product_id,
  p.product_name,
  s.period_start,
  s.period_end,
  case
    when s.period_start between '2018-01-01' and '2018-12-31'
    then
      case
        when s.period_end <= '2018-12-31'
        then datediff(day,s.period_start,s.period_end)+1
        else datediff(day,s.period_start,'2018-12-31')+1
      end
    else 0
  end as [2018],
  case
    when s.period_start > '2019-12-31' or s.period_end < '2019-01-01'
    then 0
    else
      case
        when s.period_start < '2019-01-01'
        then
          case
            when s.period_end <= '2019-12-31'
            then datediff(day,'2019-01-01',s.period_end) + 1
            else datediff(day,'2019-01-01','2019-12-31') + 1
          end
        else
          case
            when s.period_end <= '2019-12-31'
            then datediff(day,s.period_start,s.period_end) + 1
            else datediff(day,s.period_start,'2019-12-31') + 1
          end
      end
  end as [2019],
  case
    when s.period_end <= '2019-12-31'
    then 0
    else
      case
        when s.period_start <= '2019-12-31'
        then datediff(day,'2020-01-01',s.period_end) + 1
        else datediff(day,s.period_start,s.period_end) + 1
      end
  end as [2020],
  s.average_daily_sales
from
  sales s join product p on s.product_id = p.product_id
)
-- 2018
select
  product_id,
  product_name,
  '2018' as report_year,
  [2018] * average_daily_sales as total_amount
from
  sale_details
where
  [2018] <> 0

-- 2019
union
select
  product_id,
  product_name,
  '2019',
  [2019] * average_daily_sales
from
  sale_details
where
  [2019] <> 0

-- 2020
union
select
  product_id,
  product_name,
  '2020',
  [2020] * average_daily_sales
from
  sale_details
where
  [2020] <> 0

order by
  product_id, 3
