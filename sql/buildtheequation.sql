
-- 2118. Build the Equation
-- https://leetcode.com/problems/build-the-equation/



/* Write your T-SQL query statement below */

-- LHS should follow the format "<sign><fact>X^<pow>" where:
--     <sign> is either "+" or "-".
--     <fact> is the absolute value of the factor.
--     <pow> is the value of the power.
--         If the power is 1, do not add "^<pow>", e.g. power = 1 and factor = 3, the term will be "+3X"
--         If the power is 0, add neither "X" nor "^<pow>", e.g. power = 0 and factor = -3, the term will be "-3"

declare @lhs varchar(max);
set @lhs =
(
select
  case
    when factor > 0 then '+' + cast(factor as varchar) else cast(factor as varchar)
  end
  +
  case
    when power > 1 then 'X^' + cast(power as varchar)
    when power = 1 then 'X' else ''
  end
from (
select
  power,factor
from
  terms
) t
order by
  power desc
for xml path('')
);

select @lhs + '=0' as equation;
