
-- 3052. Maximize Items
-- https://leetcode.com/problems/maximize-items/





/* Write your T-SQL query statement below */

/*
 * assuming that if one or more items of a given item_type are present,
 * that the required square footage to store the items of the item_type > 0,
 * otherwise we could have division by 0
 *
 * observation
 * while testing with a dataset that had no prime_eligible items
 * expected answer: {"headers": ["item_type", "item_count"], "values": [["not_prime", null]]}
 * even though non_prime items where present and could fit into the warehouse

 */

-- prime eligible
declare @req_square_footage_prime_eligible float;
set @req_square_footage_prime_eligible = (
    select sum(square_footage) from Inventory where item_type = 'prime_eligible'
);
-- select @req_square_footage_prime_eligible;

declare @items_in_group_prime_eligible int;
set @items_in_group_prime_eligible = (
    select count(*) from Inventory where item_type = 'prime_eligible'
);


declare @prime_eligible int;
set @prime_eligible = 500000 / @req_square_footage_prime_eligible;

declare @prime_eligible_items int;
set @prime_eligible_items = @prime_eligible * @items_in_group_prime_eligible;


-- not prime
declare @req_square_footage_not_prime float;
set @req_square_footage_not_prime = (
    select sum(square_footage) from Inventory where item_type = 'not_prime'
)

declare @items_in_group_not_prime int;
set @items_in_group_not_prime = (
    select count(*) from Inventory where item_type = 'not_prime'
);

declare @available_square_footage_not_prime float;
set @available_square_footage_not_prime = 500000 - (@prime_eligible * @req_square_footage_prime_eligible);

declare @not_prime int;
set @not_prime = @available_square_footage_not_prime / @req_square_footage_not_prime;

declare @not_prime_items int;
set @not_prime_items = @not_prime * @items_in_group_not_prime;

-- result
with cte as
(
select CASE
           when @prime_eligible_items is not NULL
           then 'prime_eligible'
           else 'do_not_include_in_result'
       END as item_type,
       @prime_eligible_items as item_count
union
select CASE
           when @prime_eligible_items is not NULL and @not_prime_items is NULL
           then 'do_not_include_in_result'
           else 'not_prime'
       END,
       @not_prime_items
)
select
    item_type,
    item_count
from
    cte
where
    item_type = 'prime_eligible'
    or item_type = 'not_prime'

order by
    item_type desc -- prime_eligigble before not_prime




/*

-- example 1
{"headers":{"Inventory":["item_id","item_type","item_category","square_footage"]},"rows":{"Inventory":[[1374,"prime_eligible","Watches",68.00],[4245,"not_prime","Art",26.40],[5743,"prime_eligible","Software",325.00],[8543,"not_prime","Clothing",64.50],[2556,"not_prime","Shoes",15.00],[2452,"prime_eligible","Scientific",85.00],[3255,"not_prime","Furniture",22.60],[1672,"prime_eligible","Beauty",8.50],[4256,"prime_eligible","Furniture",55.50],[6325,"prime_eligible","Food",13.20]]}}

-- no prime_eligible, not_prime fits
{"headers":{"Inventory":["item_id","item_type","item_category","square_footage"]},"rows":{"Inventory":[[4245,"not_prime","Art",26.40],[8543,"not_prime","Clothing",64.50],[2556,"not_prime","Shoes",15.00],[3255,"not_prime","Furniture",22.60]]}}

-- no not_prime, prime_eligible fits
{"headers":{"Inventory":["item_id","item_type","item_category","square_footage"]},"rows":{"Inventory":[[1374,"prime_eligible","Watches",68.00],[5743,"prime_eligible","Software",325.00],[2452,"prime_eligible","Scientific",85.00],[1672,"prime_eligible","Beauty",8.50],[4256,"prime_eligible","Furniture",55.50],[6325,"prime_eligible","Food",13.20]]}}

-- prime_eligible fits, not_prime does not fit
{"headers":{"Inventory":["item_id","item_type","item_category","square_footage"]},"rows":{"Inventory":[[1374,"prime_eligible","Watches",68.00],[4245,"not_prime","Art",26.40],[5743,"prime_eligible","Software",325.00],[8543,"not_prime","Clothing",64.50],[2556,"not_prime","Shoes",15.00],[2452,"prime_eligible","Scientific",85.00],[3255,"not_prime","Furniture",499999.00],[1672,"prime_eligible","Beauty",8.50],[4256,"prime_eligible","Furniture",55.50],[6325,"prime_eligible","Food",13.20]]}}

-- prime_eligible does not fits, not_prime does fit
{"headers":{"Inventory":["item_id","item_type","item_category","square_footage"]},"rows":{"Inventory":[[1374,"prime_eligible","Watches",499999.00],[4245,"not_prime","Art",26.40],[5743,"prime_eligible","Software",325.00],[8543,"not_prime","Clothing",64.50],[2556,"not_prime","Shoes",15.00],[2452,"prime_eligible","Scientific",85.00],[3255,"not_prime","Furniture",22.60],[1672,"prime_eligible","Beauty",8.50],[4256,"prime_eligible","Furniture",55.50],[6325,"prime_eligible","Food",13.20]]}}

-- prime_eligible does not fits, not_prime does not fit
{"headers":{"Inventory":["item_id","item_type","item_category","square_footage"]},"rows":{"Inventory":[[1374,"prime_eligible","Watches",499999.00],[4245,"not_prime","Art",26.40],[5743,"prime_eligible","Software",325.00],[8543,"not_prime","Clothing",64.50],[2556,"not_prime","Shoes",15.00],[2452,"prime_eligible","Scientific",85.00],[3255,"not_prime","Furniture",499999.60],[1672,"prime_eligible","Beauty",8.50],[4256,"prime_eligible","Furniture",55.50],[6325,"prime_eligible","Food",13.20]]}}

 */
