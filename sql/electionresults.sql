
-- 2820. Election Results
-- https://leetcode.com/problems/election-results/



/* Write your T-SQL query statement below */

with election as
(
select
    voter,
    candidate,
    1.0 / count(candidate) over(partition by voter) as factor
from
    Votes
where
    candidate is not null
),
result as
(
select
    e.candidate,
    sum(e.factor) as votes
from
    election as e
group by
    e.candidate
),
candidate_ranks as
(
select
    rank() over(order by votes desc) as rnk,
    candidate
from
    result
)
select candidate from candidate_ranks where rnk = 1 order by candidate asc
