
-- 2072. The Winner University
-- https://leetcode.com/problems/the-winner-university/


/* Write your T-SQL query statement below */

declare @ny int;
set @ny = ( select count(*) from newyork where score >= 90);

declare @ca int;
set @ca = ( select count(*) from california where score >= 90);


select
  case when @ca > @ny then 'California University'
       when @ca = @ny then 'No Winner' else 'New York University'
  end
  as winner;
