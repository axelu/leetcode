
-- 1853. Convert Date Format
-- https://leetcode.com/problems/convert-date-format/



/* Write your T-SQL query statement below */

select
  concat_ws(', ',datename(weekday,day), concat_ws(' ',datename(month,day),datepart(day,day)),datepart(year,day)) as day
from days
