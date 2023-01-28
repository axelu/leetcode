
-- 2041. Accepted Candidates From the Interviews
-- https://leetcode.com/problems/accepted-candidates-from-the-interviews/


/* Write your T-SQL query statement below */


select
  t.candidate_id--,
  --sum(score)
from
  (
    select
      c.candidate_id,
      c.interview_id,
      r.round_id,
      r.score
    from
      candidates c inner join rounds r on c.interview_id = r.interview_id
    where
      c.years_of_exp >= 2
  ) t
group by
  t.candidate_id
having
  sum(score) > 15
