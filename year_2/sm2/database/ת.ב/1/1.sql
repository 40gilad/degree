use sakila;

select name
from language
order by name desc;

select address from address
inner join city
on address.city_id=city.city_id
where city.city='Lethbridge';

select actor.first_name,actor.last_name
 from actor
 inner join customer
 on customer.first_name=actor.first_name
 where customer.customer_id=8;


