
-- 1211. Queries Quality and Percentage
-- https://leetcode.com/problems/queries-quality-and-percentage/



/* Write your T-SQL query statement below */

-- quality: The average of the ratio between query rating and its position.
-- poor query percentage: The percentage of all queries with rating less than 3.

select
  q.query_name,
  q.quality,
  p.poor_query_percentage
from (
        select
          q.query_name,
          cast(round(sum(cast(q.rating as decimal)/q.position)/count(q.query_name),2) as numeric(5,2)) as quality
        from queries q
        group by q.query_name
    ) as q,
    (
        select
          p.query_name,
          cast(round(cast(p.cnt as decimal)/t.cnt*100,2) as numeric(5,2)) as poor_query_percentage
        from (
            select
              distinct queries.query_name,
              isnull(qr.cnt,0) as cnt
            from queries left outer join (
                select
                  q.query_name,
                  count(*) as cnt
                from queries q
                where q.rating < 3
                group by q.query_name ) as qr on queries.query_name = qr.query_name
            ) as p,
            (
                select
                  q.query_name,
                  count(*) as cnt
                from queries q
                group by q.query_name
            ) as t
        where p.query_name = t.query_name
    ) as p
where q.query_name = p.query_name
