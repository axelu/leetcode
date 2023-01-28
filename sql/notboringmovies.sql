
-- 620. Not Boring Movies
-- https://leetcode.com/problems/not-boring-movies/

/* Write your T-SQL query statement below */

select *
from cinema
where id % 2 = 1 and description <> 'boring'
order by rating desc
