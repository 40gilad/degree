-- -------------------------------- TABLES AND DATABASE ---------------------------------
create database animal_farm;
use animal_farm;

create table inventory (prod_id int primary key not null auto_increment,
prod_name varchar (50),
price int,
amount int);

create table address(city varchar(30),
street varchar (30),
s_num int,
s_app int,
ad_id int primary key not null auto_increment)
auto_increment=45678;

create table person(p_id int primary key not null,
p_name varchar (50),
phone varchar(12),
address int,
foreign key(address) references address(ad_id));


create table employee(e_id int primary key not null auto_increment,
e_job varchar (20) check (e_job in ('shopkeeper','inventory','delivery')),
p_id int,
foreign key (p_id) references person(p_id))
auto_increment=50;

create table costumer(c_id int primary key not null auto_increment,
p_id int,
foreign key (p_id) references person(p_id))
auto_increment=500;

create table animal(a_id int primary key not null auto_increment,
owner_costumer_id int,
a_kind varchar (30) check (a_kind in ('crocodile','wolf','elephant','chinchilla','shrimp','iguana')),
a_name varchar (30),
foreign key (owner_costumer_id) references costumer(c_id))
auto_increment=200;

create table An_order(order_id int primary key not null auto_increment,
c_id int,
e_id int,
o_date date,
price float,
delivery_emp_id int,
is_deliverd int default (0),
foreign key (c_id) references costumer(c_id),
foreign key (e_id) references employee(e_id))
auto_increment=1000;

create table product_order(order_id int,
prod_id int,
amount int,
foreign key (order_id) references an_order(order_id),
foreign key (prod_id) references inventory (prod_id));

-- ************************************** PROCEDURES **********************************************
SET SQL_SAFE_UPDATES = 0;

delimiter //
create procedure add_product_2_inventory(in Iname varchar(50),in Iprice int,in Iamount int)
begin
if  exists(select * from inventory where prod_name=Iname and price=Iprice) then
update inventory 
set amount=amount+Iamount
where prod_name=Iname;
else
insert into inventory(prod_name,price,amount)
values(Iname,Iprice,Iamount);
end if;
end //

delimiter //
create procedure add_address(in Acity varchar(50),in Astreet varchar(50),in Anum int, in Aapp int)
begin
if  exists(select * from address where city=Acity and street=Astreet and s_num=Anum and s_app=Aapp) then
update address
set s_num=Anum
where city=Acity and street=Astreet and s_num=Anum and s_app=Aapp;
else
insert into address(city,street,s_num,s_app)
values(Acity,Astreet,Anum,Aapp);
end if;
end //


delimiter //
create procedure add_person(in pid int,in pname varchar(50),in pphone varchar(12),
in Acity varchar(50),in Astreet varchar(50),in Anum int, in Aapp int)
begin
if  exists(select * from person where p_id=pid) then
update person
set p_id=pid
where p_id=pid;
else
call add_address(Acity,Astreet,Anum,Aapp);
insert into person(p_id,p_name,phone,address)
values(pid,pname,pphone,(
select ad_id from address where city=Acity and street=Astreet and s_num=Anum and s_app=Aapp));
end if;
end //

delimiter //
create procedure add_costumer(in pid int,in pname varchar(50),in pphone varchar(12),
in Acity varchar(50),in Astreet varchar(50),in Anum int, in Aapp int)
begin
if  exists(select * from costumer where p_id=pid) then
update costumer
set p_id=pid
where p_id=pid;
else
call add_person(pid,pname,pphone,Acity,Astreet,Anum,Aapp);
insert into costumer(p_id)
values(pid);
end if;
end //

delimiter //
create procedure add_employee(in ejob varchar (20),in pid int,in pname varchar(50),in pphone varchar(12),
in Acity varchar(50),in Astreet varchar(50),in Anum int,in Aapp int)
begin
if  exists(select * from employee where p_id=pid) then
update employee
set p_id=pid
where p_id=pid;
else
call add_person(pid,pname,pphone,Acity,Astreet,Anum,Aapp);
insert into employee(p_id,e_job)
values(pid,ejob);
end if;
end //

delimiter //
create procedure add_animal(in aown_id int,in akind varchar(30),in aname varchar(30))
begin
if  exists(select * from animal where a_kind=akind and a_name=aname) then
update animal
set a_kind=akind
where a_kind=akind and a_name=aname;
else
insert into animal(owner_costumer_id,a_kind,a_name)
values((select c_id from costumer where c_id=aown_id),akind,aname);
end if;
end //

delimiter //
create procedure add_An_order(in cid int,in eid int,in del_id int)
begin
insert into An_order(c_id,e_id,o_date,price,delivery_emp_id)
values((select c_id from costumer where c_id=cid),(select eid from employee where e_id=eid),curdate(),20,del_id);
end //



delimiter //
create procedure add_pro_2_order(in pname varchar (50),in pamount int,o_id int)
begin
update inventory
set amount=amount-pamount
where
prod_name=pname;
update an_order
set price=price+(select price from inventory where prod_name=pname)*pamount
where order_id=o_id;
insert into product_order(order_id,prod_id,amount)
values((select order_id from an_order where order_id=o_id),
(select prod_id from inventory where prod_name=pname),
pamount);
end //

delimiter //
create procedure give_discount(oid int,in percent float)
begin
update an_order
set price=price-((price*percent)/100) where order_id=oid;
end //

delimiter //
create procedure deliverd(oid int,in e_id int)
begin
if(select price from an_order where order_id=oid)>200
then
update an_order
set price=price-20,is_deliverd=1
where order_id=oid;
else
update an_order
set is_deliverd=1 where order_id=oid;
end if;
end //

delimiter //
create function income_amount_4_employee(e_name varchar(50),_month varchar(2),_year varchar(4))
returns int deterministic
begin
declare r int;

select sum(price) from an_order as a
where a.e_id=
(
select e_id from employee as e
inner join person as p
on (e.p_id=p.p_id)
where p.p_name=e_name) and a.o_date between '_year-_month-_01' and '2022-08-01'
into r;
return r;

end //

delimiter //
create procedure get_order_id(c_id int,e_id int)
begin
select max(order_id) from an_order as a
where (a.c_id=c_id and a.e_id=e_id);
end //


-- -------------------------------- DATA INSERTION -----------------------------

call add_product_2_inventory('Bonzo',18,20);
call add_product_2_inventory('Elephant Food',50,9);
call add_product_2_inventory('Crocodile Rock',43,19);
call add_product_2_inventory('Chinchilla Food',12,80);
call add_product_2_inventory('Chinchilla House',90,10);
call add_product_2_inventory('Hat For Iguana',8,100);
call add_product_2_inventory('Iguana Food',40,8);
call add_product_2_inventory('Elephant Trunk Cleaner',99,3);
call add_product_2_inventory('Crocodile Toothbrush',60,5);
call add_product_2_inventory('Dog Leash',20,200);

call add_costumer(313416562,'Gilad Meir','0526263862','Ramat Gan','Rokah',14,1);
call add_costumer(11111111,'Shiran Asaf','0524647473','Holon','Ibn Gabirol',3,6);
call add_costumer(22222222,'Koop','056684852','Petah Tikva','Hadera',25,1);
call add_costumer(33333333,'Linda Meir','05265464','Petah Tikva','Hadera',25,1);
call add_costumer(4444444,'Adam Meir','059375834','Ramat Gan','Rokah',14,1);
call add_costumer(5555555,'Dovi Doberman','052624353','Beer Sheva','Einstein',5,4);
call add_costumer(1234567,'Yona','052231343','Netanya','Bosel',7,1);
call add_costumer(7777777,'John Lennon','05234575','Liverpool','Concert Square',3,14);
call add_costumer(8888888,'Steven Gerrard aka Captain Fnatastic','05564745','Liverpool','Anfield Road',1,1);
call add_costumer(9999999,'God','052567557','Sky','Rain Cloud',2,1);

call add_employee('shopkeeper',0001,'Rocky Raccoon','05050505','Ramat Gan','Bialik',8,4);
call add_employee('inventory',0010,'Bungallow Bill','063450505','Haifa','Somewhere',2,1);
call add_employee('delivery',0011,'Maggie Mae','05324505','Netanya','Bossel',6,1);
call add_employee('shopkeeper',0100,'Frank Zappa','05837592','USA','New York',1,5);
call add_employee('inventory',0101,'Paul Mccartney','0545632','Glasgow','Mull Of Kintyre',1,1);
call add_employee('delivery',0110,'Charon','05382759','Berlin','LandStrasse',5,1);
call add_employee('shopkeeper',0111,'Jimmy Page','0452364','London','Oxford',56,8);
call add_employee('inventory',1000,'Kendrick Lamar','0756743','Compton','Rowscrans',55,6);
call add_employee('delivery',666,'Bruce Dicenson','06666234','Brighton','Airplane',98,2);
call add_employee('shopkeeper',1010,'Harry Mguire','052435432','Manchester','Old f***ford',9,1);

call add_an_order(506,50,52);
call add_an_order(504,51,55);
call add_an_order(505,50,58);
call add_an_order(507,53,52);
call add_an_order(508,53,55);
call add_an_order(501,50,58);
call add_an_order(502,56,52);
call add_an_order(502,57,55);
call add_an_order(500,51,58);
call add_an_order(500,59,58);

update an_order set o_date='2021-05-07' where order_id=1000;
update an_order set o_date='2022-07-25' where order_id=1008;
update an_order set o_date='2022-03-21' where order_id=1002;
update an_order set o_date='1995-10-05' where order_id=1007;
update an_order set o_date='2020-01-01' where order_id=1009;

call add_pro_2_order('Bonzo',3,1000);
call add_pro_2_order('Elephant Food',1,1000);
call add_pro_2_order('Dog Leash',10,1001);
call add_pro_2_order('Dog Leash',3,1002);
call add_pro_2_order('Chinchilla House',5,1003);
call add_pro_2_order('Elephant Trunk Cleaner',1,1004);
call add_pro_2_order('Crocodile Toothbrush',2,1005);
call add_pro_2_order('Hat For Iguana',1,1006);
call add_pro_2_order('Bonzo',2,1007);
call add_pro_2_order('Chinchilla Food',3,1008);
call add_pro_2_order('Crocodile Rock',3,1009);

call deliverd(1001,51);
call deliverd(1000,50);
call deliverd(1007,57);
call deliverd(1002,50);
call deliverd(1009,59);

call add_animal(500,'crocodile','Elton');
call add_animal(501,'wolf','Steve Harris');
call add_animal(502,'elephant','Syd Barrett');
call add_animal(503,'chinchilla','Ozzy Ousborn');
call add_animal(504,'shrimp','Mark Knopfler');
call add_animal(505,'iguana','Kanye West');
call add_animal(506,'crocodile','Phil Collins');
call add_animal(507,'wolf','Peter Gabriel');
call add_animal(508,'elephant','Donnie Darko');
call add_animal(509,'chinchilla','Vincent Vega');
call add_animal(502,'shrimp','Borat Sagdyev');
call add_animal(501,'iguana','Azamat Bagatov');
-- ************************************** QUERIES **********************************************
/*
select prod_name,amount from inventory; -- showing prod_name and amount in inventory (1)

select * from an_order where o_date> date_add(now(),interval -(7*x) day); -- showing all orders in x last weeks (2)

select p_name from person where p_id=(
select p_id from employee where e_id=(
select e_id from(
select  p.order_id,sum(p.amount) as amount ,a.e_id from product_order p
inner join an_order as a
on p.order_id=a.order_id
group by e_id
order by amount desc) as z
limit 1)); -- showing employee name with max product amount sells (3)

select p_name from person where p_id =(
select p_id from(
select p_id,sum(price) as price from an_order
inner join employee
on (an_order.e_id=employee.e_id)
group by p_id
order by price desc) as z
limit 1) -- employee sold most money (4)

select p.p_name,a.order_id from person as p
inner join(
select a.order_id,c.p_id from an_order as a
inner join costumer as c
on a.c_id=c.c_id
where is_deliverd=0)as a
on p.p_id=a.p_id; -- showing open orders and costumer name (5)

select p.p_name from person as p inner join(
select p_id from costumer as c
left join an_order as a
on (c.c_id=a.c_id)
where a.c_id is null) as d
on (p.p_id=d.p_id); -- costumers who didnt order (6)

select p.p_name from person as p
inner join(
select p_id from costumer as c 
inner join(
select c_id,count(c_id) as amount from an_order
group by c_id
having amount>1)as a
on (c.c_id=a.c_id)) as b
on (p.p_id=b.p_id); -- showing costumer orderd more than once (7)

select sum(price) as income from an_order where o_date>date_add(now(),interval -(30*x) day); -- showing incomes in x last months (8)

*/








