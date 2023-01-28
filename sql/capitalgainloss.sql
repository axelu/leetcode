
-- 1393. Capital Gain/Loss
-- https://leetcode.com/problems/capital-gainloss/



/* Write your T-SQL query statement below */

select
  s.stock_name
  ,sum(
      case
        when s.operation = 'Buy' then -s.price else s.price
      end
  ) as capital_gain_loss
from
  stocks as s
group by
  s.stock_name

