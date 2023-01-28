
-- 1440. Evaluate Boolean Expression
-- https://leetcode.com/problems/evaluate-boolean-expression/


/* Write your T-SQL query statement below */


select
  e.left_operand,
  -- l.value as left_val,
  e.operator,
  e.right_operand,
  -- r.value as right_val,
  case
    when e.operator = '>' then
      case when l.value > r.value then 'true' else 'false' end
    when e.operator = '<' then
      case when l.value < r.value then 'true' else 'false' end
    else
      case when l.value = r.value then 'true' else 'false' end
  end as [value]
from
  expressions e
    inner join variables l on e.left_operand = l.name
    inner join variables r on e.right_operand = r.name
