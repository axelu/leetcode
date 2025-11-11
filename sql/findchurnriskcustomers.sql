
-- 3716. Find Churn Risk Customers
-- https://leetcode.com/problems/find-churn-risk-customers/



/* Write your T-SQL query statement below */

-- assume if there is a cancel, it is only one event per day
--     if that assumption proofs wrong, maybe we assume increasing event_id as the next criteria
-- can a user have cancel and then a start ???
-- because if not, we only need to check for cancel as an event
-- plays also in how long they have been a subscriber if they can cancel and then start again
-- because in that case we need to look for the last start event
-- note via testing found that 1st start counts, so to simplify only check date of 1st event
-- note via testing found there can be two events on same day, and event_id determines which one is last

with cte_subscription_users as
(
select distinct user_id from subscription_events
),
cte_first_event_date as
(
select
    o.user_id,
    (select top(1) i.event_date
     from subscription_events i
     where i.user_id = o.user_id
     order by i.event_id asc) as event_date
from cte_subscription_users o
),
cte_last_event_id as
(
select
    o.user_id,
    (select top(1) i.event_id
     from subscription_events i
     where i.user_id = o.user_id
     order by i.event_id desc) as last_event_id
from cte_subscription_users o
),
cte_downgrade_events as
(
select
    o.user_id,
    isnull((select count(*)
            from subscription_events i
            where o.user_id = i.user_id and i.event_type = 'downgrade'),0) as downgrades
from
    cte_subscription_users o
),
cte_monthly_amounts as
(
select
    o.user_id,
    (select max(i.monthly_amount)
     from subscription_events i
     where i.user_id = o.user_id) as max_monthly_amount,
    e.monthly_amount as current_monthly_amount
from cte_subscription_users o
     join cte_last_event_id le on o.user_id = le.user_id
     join subscription_events e on e.event_id = le.last_event_id
),
cte_user_details as
(
select
    u.user_id,
    CASE
        WHEN le.event_type <> 'cancel'
        THEN 'active' ELSE 'inactive'
    END as user_state,
    de.downgrades,
    ma.current_monthly_amount / (ma.max_monthly_amount * 1.0) as curr_rev_ratio,
    DATEDIFF(day,fe.event_date,le.event_date) as days_as_subscriber,
    le.plan_name as current_plan,
    le.monthly_amount as current_monthly_amount,
    ma.max_monthly_amount as max_historical_amount
from
    cte_subscription_users u
    join cte_last_event_id leid on u.user_id = leid.user_id
    join subscription_events le on le.event_id = leid.last_event_id
    join cte_downgrade_events de on u.user_id = de.user_id
    join cte_monthly_amounts ma on u.user_id = ma.user_id
    join cte_first_event_date fe on u.user_id = fe.user_id
)
-- select * from cte_user_details

select
    user_id,
    current_plan,
    current_monthly_amount,
    max_historical_amount,
    days_as_subscriber
from
    cte_user_details
where
    user_state = 'active'
    and downgrades >= 1
    and curr_rev_ratio < .5
    and days_as_subscriber >= 60
order by
    days_as_subscriber desc, user_id

