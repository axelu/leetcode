
-- 2989. Class Performance
-- https://leetcode.com/problems/class-performance/





/* Write your T-SQL query statement below */

-- min score
declare @min_score int;
set @min_score = (
select min(score) from (
select
    student_id,
    (assignment1 + assignment2 + assignment3) as score
from
    Scores
) t );

-- max score
declare @max_score int;
set @max_score = (
select max(score) from (
select
    student_id,
    (assignment1 + assignment2 + assignment3) as score
from
    Scores
) t );


select @max_score - @min_score as difference_in_score;
