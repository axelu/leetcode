
-- 3497. Analyze Subscription Conversion
-- https://leetcode.com/problems/analyze-subscription-conversion/





/* Write your T-SQL query statement below */

-- UserActivity: (user_id, activity_date, activity_type) is the unique key for this table
-- activity_type is one of ('free_trial', 'paid', 'cancelled').

with cte_paid_users as
(
    select distinct ua.user_id from UserActivity ua where ua.activity_type = 'paid'
),
cte_trial_avg_daily_duration as
(
    select
        ua.user_id,
        ROUND(AVG(CAST(ua.activity_duration as decimal)),2) as trial_avg_duration
    from
        UserActivity ua join cte_paid_users pu on ua.user_id = pu.user_id
    where
        ua.activity_type = 'free_trial'
    group by
        ua.user_id
),
cte_paid_avg_daily_duration as
(
    select
        ua.user_id,
        ROUND(AVG(CAST(ua.activity_duration as decimal)),2) as paid_avg_duration
    from
        UserActivity ua join cte_paid_users pu on ua.user_id = pu.user_id
    where
        ua.activity_type = 'paid'
    group by
        ua.user_id
)
select
    tad.user_id,
    tad.trial_avg_duration,
    pad.paid_avg_duration
from
    cte_trial_avg_daily_duration tad join cte_paid_avg_daily_duration pad on tad.user_id = pad.user_id
order by
    tad.user_id
