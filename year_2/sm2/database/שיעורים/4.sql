

SELECT 
    first_name, COUNT(first_name) amount
FROM
    customer
GROUP BY first_name
HAVING COUNT(first_name) = 1
ORDER BY amount DESC;

SELECT 
    last_name, COUNT(last_name) amount
FROM
    actor
GROUP BY last_name
HAVING COUNT(last_name) > 1;

SELECT 
    a.first_name, a.last_name, COUNT(a.first_name) amount_acted
FROM
    actor a
        INNER JOIN
    film_actor fa ON a.actor_id = fa.actor_id
        INNER JOIN
    film f ON f.film_id = fa.film_id
GROUP BY a.first_name , a.last_name
order by count(first_name) desc;

SELECT 
    c.name,avg(f.length)AvgFilmLength
FROM
    category c
        INNER JOIN
    film_category fc ON c.category_id = fc.category_id
        INNER JOIN
    film f ON f.film_id = fc.film_id
    group by c.name 
    order by avg(f.length)
    ;