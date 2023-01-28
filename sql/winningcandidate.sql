
-- 574. Winning Candidate
-- https://leetcode.com/problems/winning-candidate/


/* Write your T-SQL query statement below */

select
  name
from
  (
    select
     name,
     -- count(*) as cnt,
     rank() over (order by count(*) desc) as rnk
    from
      (
        select
          v.id,
          v.candidateId,
          c.name
        from
          vote v join candidate c on v.candidateId = c.id
      ) t
    group by
      name
   ) t
where
  rnk = 1
