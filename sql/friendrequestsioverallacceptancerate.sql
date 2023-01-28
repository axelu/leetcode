
-- 597. Friend Requests I: Overall Acceptance Rate
-- https://leetcode.com/problems/friend-requests-i-overall-acceptance-rate/



/* Write your T-SQL query statement below */

declare @accepted decimal;
set @accepted = (select count(*) from (select distinct requester_id,accepter_id from RequestAccepted) t);

declare @requested int;
set @requested = (select count(*) from (select distinct sender_id,send_to_id from FriendRequest) t);

if @requested = 0
  select 0 as accept_rate
else
  select round(@accepted/@requested,2) as accept_rate

