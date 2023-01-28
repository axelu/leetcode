
-- 618. Students Report By Geography
-- https://leetcode.com/problems/students-report-by-geography/


/* Write your T-SQL query statement below */

-- test cases are generated so that the student number from America
--   is not less than either Asia or Europe

with america
as
(
select
  name,
  row_number() over(order by name ) as rnk
from
  student
where continent = 'America'
),
asia
as
(
select
  name,
  row_number() over(order by name ) as rnk
from
  student
where continent = 'Asia'
),
europe
as
(
select
  name,
  row_number() over(order by name ) as rnk
from
  student
where continent = 'Europe'
)
select
  am.name as America,
  aa.name as Asia,
  eu.name as Europe
from
  america am left join asia aa on am.rnk = aa.rnk
             left join europe eu on am.rnk = eu.rnk
