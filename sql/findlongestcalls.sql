
-- 3124. Find Longest Calls
-- https://leetcode.com/problems/find-longest-calls/





/* Write your T-SQL query statement below */

-- assumption duration not exceeding 24 hours

-- outgoing
with outgoing as
(
select top(3)
    ct.id,
    ct.first_name,
    cl.type,
    CONVERT(varchar, DATEADD(s, cl.duration, 0), 108) as duration
from
    Contacts as ct join Calls as cl on ct.id = cl.contact_id
where
    cl.type = 'outgoing'
order by
    cl.duration desc
),
-- incoming
incoming as
(
select top(3)
    ct.id,
    ct.first_name,
    cl.type,
    CONVERT(varchar, DATEADD(s, cl.duration, 0), 108) as duration
from
    Contacts as ct join Calls as cl on ct.id = cl.contact_id
where
    cl.type = 'incoming'
order by
    cl.duration desc
)
select first_name, type, duration as duration_formatted from outgoing
union
select first_name, type, duration as duration_formatted from incoming
order by type, duration desc, first_name
