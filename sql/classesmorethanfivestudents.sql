
-- 596. Classes More Than 5 Students
-- https://leetcode.com/problems/classes-more-than-5-students/



/* Write your T-SQL query statement below */


select
  class
from
  courses
group by
  class
having
  count(*) >= 5
