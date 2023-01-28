
-- 1495. Friendly Movies Streamed Last Month
-- https://leetcode.com/problems/friendly-movies-streamed-last-month/



/* Write your T-SQL query statement below */


select distinct
  c.title
from
  tvprogram as t inner join content as c on
    t.content_id = c.content_id
where
  t.program_date between '2020-06-01' and '2020-06-30'
  and c.kids_content = 'Y'
  and c.content_type = 'Movies'
