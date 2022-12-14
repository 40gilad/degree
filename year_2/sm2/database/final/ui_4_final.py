#INITILIZE CONNECTION TO MYSQL SERVER
#import numpy as np 
import mysql.connector as S
mydb = S.connect(
   host="127.0.0.1",
   user="root",
   password=" "
 )
mycursor=mydb.cursor();
mycursor.execute("use animal_farm")



#FUNCTIONS
    
#------------------------------------------ INVENTORY -----------------------------------------#

def add_product_2_inventory():
    p_name=input('Product name:')
    price=input('Product price:')
    amount=input('Amount in inventory:')
    mycursor.callproc('add_product_2_inventory',[p_name,price,amount])
 

def print_inventory():
    mycursor.execute("select * from inventory")
    myresult=mycursor.fetchall()
    print('ID , Product name , Price , Amount)')
    for x in myresult:
        print (str(x[0])+' , '+str(x[1])+' , '+str(x[2])+' $ , '+str(x[3]))

        

#------------------------------------------ COSTUMER -----------------------------------------#

def add_costumer():
    p_id=input("Costumer's ID:")
    p_name=input("Costumer's full name:")
    phone=input("Costumer's phone number:")
    city=input("Costumer's city:")
    street=input("Costumer's street:")
    b_number=input("Costumer's street number:")
    appartment=input("Costumer's appartment number:")
    mycursor.callproc('add_costumer',[p_id,p_name,phone,city,street,b_number,appartment])
    q=('select c_id from costumer as e where e.p_id='+str(p_id))
    mycursor.execute(q)
    myresult=mycursor.fetchall()
    for x in myresult:
        print(p_name,"'s costumer code is:",str(*x))
    
def print_costumer():
    mycursor.execute("select * from costumer")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)

#------------------------------------------ EMPLOYEE -----------------------------------------#

def add_employee():
    p_job=input("Employee's job('1.shopkeeper','2.inventory employee','3.deliveryman'):")
    if p_job=='1':
        p_job='shopkeeper'
    elif p_job=='2':
        p_job='inventory'
    elif p_job=='3':
        p_job='delivery'   
    p_id=input("Employee's id: ")
    p_name=input("Employee's name: ")
    phone=input("Employee's Phone: ")
    city=input("Employee's city: ")
    street=input("Employee's street: ")
    b_number=input("Employee's street number: ")
    appartment=input("Employee's appartment number: ")
    mycursor.callproc('add_employee',[p_job,p_id,p_name,phone,city,street,b_number,appartment])
    q=('select e_id from employee as e where e.p_id='+str(p_id))
    mycursor.execute(q)
    myresult=mycursor.fetchall()
    for x in myresult:
        print(p_name,"'s employee code is:",str(*x))
def print_employee():
    mycursor.execute("select * from employee")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
        
#------------------------------------------ ANIMAL -----------------------------------------#

def add_animal():
    owner_id=input("owners's costumer code:")
    kind=input("animal kind: ")
    name=input("animal's name':")
    mycursor.callproc('add_animal',[owner_id,kind,name])
    
def print_animal():
    mycursor.execute("select * from animal")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
        
#------------------------------------------ AN ORDER -----------------------------------------#

def add_an_order():
    costumer_id=input("Costumer's code:")
    employee_id=input("Employee's code:")
    delivery_employee_id=input("deliveryman's employee code:")
    mycursor.callproc('add_An_order',[costumer_id,employee_id,delivery_employee_id])
    q='select max(order_id) from an_order as a where (a.c_id='+costumer_id+' and a.e_id='+employee_id+');'
    mycursor.execute(q)
    myresult=mycursor.fetchall()
    for i in myresult:
        o_id=str(*i)
    print('Order ID is: '+str(o_id))
    zevel=input("Do you want to add products to this order? (1. YES 2.NO):\t")
    if zevel=='1':
        while true:
            add_pro_2_order(o_id)
            zevel=input("Do you want to add more products to this order? (1. YES 2.NO):\t")
            if zevel=='2':
                break
def print_an_order():
    mycursor.execute("select * from an_order")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
                
#------------------------------------------ PRODUCT ORDER -----------------------------------------#

def add_pro_2_order(o_id):
    print('\n\t\t\t\t\tOut Products:')
    print_inventory()
    product_name=input("\nProducts's name:")
    amount=input("How much?")
    q=("select amount from inventory where prod_name='"+str(product_name)+"'")
    mycursor.execute(q)
    myresult=mycursor.fetchall()
    for x in myresult:
        amount_in_inventory=int(*x)
    while int(amount)>amount_in_inventory:
        print('Inventory has '+str(amount_in_inventory)+' '+str(product_name)+' left')
        amount=input("New amount: ")
    mycursor.callproc('add_pro_2_order',[product_name,amount,o_id])
    
def print_product_order():
    mycursor.execute("select * from product_order")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
                        
#------------------------------------------ DISCOUNT/FINISH DELIVERY -----------------------------------------#

def give_discount():
    o_id=input("Order ID: ")
    precent=input("Discount percent:")
    mycursor.callproc('give_discount',[o_id,precent])

def deliverd():
    o_id=input("Order ID: ")
    delivery_emp_id=input("Delivery employee's code':")
    mycursor.callproc('deliverd',[o_id,delivery_emp_id])
          
#QUERIES
#------------------------------------------ ORDER FROM LAST X WEEKS -----------------------------------------#


def order_last_weeks():
    days=input("How many weeks back would you like to see order stats? ")
    q='select * from an_order where o_date> date_add(now(),interval -'+str(days)+' week)'
    mycursor.execute(q)
    myresult=mycursor.fetchall()
    print('Order ID , Costumer code , Employee code , Order date , Price , Delivery employee Id , Is deliverd')
    print('\n0- NOT DELIVERD YET\n1-DELIVERD\n')
    for x in myresult:
        print((str(x[0]))+' , '+str(x[1])+' , '+str(x[2])+' , '+str(x[3])+' , '+str(x[4])+' $ , '+str(x[5])+' , '+str(x[6]))
#------------------------------------------ INCOMES IN x LAST MONTHS -----------------------------------------#

def incomes_last_months():
    days=input("How many moths back would you like to see income stats? ")
    q='select sum(price) as income from an_order where o_date>date_add(now(),interval -'+str(days)+' month)'
    mycursor.execute(q)
    myresult=mycursor.fetchall()
    print('\n\nIncome in those months is:')
    for x in myresult:
        print(str(*x)+' $')
        

#------------------------------------------ TOP PRODUCT AMOUNT SALESMAN -----------------------------------------#

def top_product_amount():
    mycursor.execute("select p_name from person where p_id=(select p_id from employee where e_id=(select e_id from(select  p.order_id,sum(p.amount) as amount ,a.e_id from product_order p inner join an_order as a on p.order_id=a.order_id group by e_id order by amount desc) as z limit 1));")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
    
#------------------------------------------ TOP MONEY AMOUNT SALESMAN -----------------------------------------#

def top_money_amount():
    mycursor.execute("select p_name from person where p_id =(select p_id from( select p_id,sum(price) as price from an_order inner join employee on (an_order.e_id=employee.e_id) group by p_id order by price desc) as z limit 1)")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
    
#------------------------------------------ OPEN ORDERS -----------------------------------------#

def open_orders():
    mycursor.execute("select p.p_name,a.order_id from person as p inner join(select a.order_id,c.p_id from an_order as a inner join costumer as c on a.c_id=c.c_id where is_deliverd=0)as a on p.p_id=a.p_id;")
    myresult=mycursor.fetchall()
    print("(Costumer's name,order ID)")
    for x in myresult:
        print (str(x[0])+' , '+str(x[1]))
   
#------------------------------------------ COSTUMER WHO DIDNT ORDER -----------------------------------------#

def didnt_order_costumers():
    mycursor.execute("select p.p_name from person as p inner join(select p_id from costumer as c left join an_order as a on (c.c_id=a.c_id) where a.c_id is null) as d on (p.p_id=d.p_id)")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
    
#------------------------------------------ COSTUMER WHO ORDERED MORE THAN ONCE -----------------------------------------#

def returned_costumers():
    mycursor.execute("select p.p_name from person as p inner join(select p_id from costumer as c inner join(select c_id,count(c_id) as amount from an_order group by c_id having amount>1)as a on (c.c_id=a.c_id)) as b on (p.p_id=b.p_id);")
    myresult=mycursor.fetchall()
    for x in myresult:
        print (*x)
    

 #----------------------------------------- Stats menu -----------------------------------------#
def store_stats():
    true=1
    while true:
        print('\n\n\t\t\t\t\t\t Store stats:')
        print('1.Show inventory\n2.Show top amount products salesman\n3.Show top income salesman\n4.Show open orders\n5.Show cosumers who never orderd\n6.Show returned costumers\n7.Order stats for last weeks\n8.Income stats for last months\n9.Return to main menu')
        selection=input("\nPlease Select:")
        print('\n')
        if selection =='1': 
            print_inventory()
        elif selection == '2': 
            top_product_amount()
        elif selection == '3':
            top_money_amount()
        elif selection == '4': 
            open_orders()
        elif selection == '5': 
            didnt_order_costumers()
        elif selection == '6': 
            returned_costumers()
        elif selection == '7':
            order_last_weeks()
        elif selection== '8':
            incomes_last_months()
        elif selection == '9':
            break
        else: 
            print ("Unknown Option Selected!") 


#MAIN

true=1
while true:
    print('\n\n\t\t\t\t\t Animal Farm Store\n\t\t\t\t    By Gilad Meir - 313416562 \n\t\t "All animals are equal, but some animals are more equal than others."')
    print('\n\t\t\t\t\t\tMENU')
    print('1.Add products to inventory\n2.Add a new costumer\n3.Add animal for costumer\n4.add a new employee\n5.Create new order\n6.Add product to an exsisting order\n7.Give discount to an order\n8.Close deliverd order\n9.Stats\n10.Save and exit')
    selection=input("\nPlease Select:")
    if selection =='1': 
        add_product_2_inventory()
    elif selection == '2': 
        add_costumer()
    elif selection == '3':
        add_animal()
    elif selection == '4': 
        add_employee()
    elif selection == '5': 
        add_an_order()
    elif selection == '6':
        o_id=input("\nOrder's ID: ")
        add_pro_2_order(o_id)
    elif selection == '7': 
        give_discount()
    elif selection== '8':
        deliverd()
    elif selection == '9':
        store_stats()
    elif selection == '10':
        mydb.commit()
        break
    else: 
        print ("Unknown Option Selected!") 
        

