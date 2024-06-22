
-- 3058. Friends With No Mutual Friends
-- https://leetcode.com/problems/friends-with-no-mutual-friends/



/* Write your T-SQL query statement below */

with user_friend as
(
select
    f.user_id1 as [user],
    f.user_id2 as friend
from
    friends as f
union
select
    f.user_id2 as [user],
    f.user_id1 as friend
from
    friends as f
),
mutual_friend_count as
(
select
    f.user_id1,
    f.user_id2,
    (
     select count(*)
     from user_friend as ufl join user_friend as ufr on ufl.friend = ufr.friend
     where ufl.[user] = f.user_id1 and ufr.[user] = f.user_id2
    ) as nbr_mutual_friends
from
    Friends as f
)
select
    user_id1,
    user_id2
from
    mutual_friend_count
where
    nbr_mutual_friends = 0
order by
    user_id1, user_id2
