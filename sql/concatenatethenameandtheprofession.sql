
-- 2504. Concatenate the Name and the Profession
-- https://leetcode.com/problems/concatenate-the-name-and-the-profession/



/* Write your T-SQL query statement below */

select
  person_id
  ,concat(name,'(',left(profession,1),')') as name
from
  person
order by
  person_id desc
