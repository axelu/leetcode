
-- 2252. Dynamic Pivoting of a Table
-- https://leetcode.com/problems/dynamic-pivoting-of-a-table/



-- see also 1777. Product's Price for Each Store https://leetcode.com/problems/products-price-for-each-store/
-- see also 2253. Dynamic Unpivoting of a Table https://leetcode.com/problems/dynamic-unpivoting-of-a-table/

CREATE PROCEDURE PivotProducts AS
BEGIN
    /* Write your T-SQL query statement below. */

    declare @colspivot as nvarchar(MAX);
    set @colspivot = STUFF((
        SELECT ',' + store
        FROM ( select distinct store from products ) t
        FOR XML PATH(''))
    ,1,1,'');

    -- select @colspivot;


    declare @query as nvarchar(MAX);
    set @query = '
        select *
        from
        (
          select product_id,store,price from products
        ) as SourceTable pivot(avg(price) for store in (' + @colspivot + ')) as PivotTable
    ';

    execute(@query);
END
