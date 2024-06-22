
-- 3172. Second Day Verification
-- https://leetcode.com/problems/second-day-verification/




/* Write your T-SQL query statement below */

select
    -- e.email_id,
    e.user_id --,
    --e.signup_date,
    --t.signup_action,
   -- t.action_date
from
    Emails e join Texts t on e.email_id = t.email_id
where
    t.signup_action = 'Verified'
    and DATEDIFF(dd, e.signup_date, t.action_date) = 1
order by
    e.user_id
