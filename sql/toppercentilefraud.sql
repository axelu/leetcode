
-- 3055. Top Percentile Fraud
-- https://leetcode.com/problems/top-percentile-fraud/




/* Write your T-SQL query statement below */

with state_count as
(
select state, count(*) as cnt from Fraud group by state
),
fraud_rank as
(
select
    policy_id,
    state,
    fraud_score,
    RANK() over(partition by state order by fraud_score desc) as rnk
from
    Fraud
),
top5percentile as
(
select
    state,
    case -- there is at least 1
        when 0.05 * cnt > 1
        then 0.05 * cnt
        else 1
    end as top5
from
    state_count
)
-- select * from state_count
-- select * from fraud_rank
-- select * from top5percentile
select
    f.policy_id,
    f.state,
    f.fraud_score
from
    fraud_rank as f join top5percentile as t on f.state = t.state and f.rnk <= t.top5
order by
    f.state asc, f.fraud_score desc, f.policy_id

