# -*- coding: utf-8 -*-
"""
Created on Tue Dec 20 23:29:17 2022

@author: GILAD

import datetime as dt
import mysql.connector as S
mydb = S.connect(
   host="127.0.0.1",
   user="root",
   password="4G02m716948"
 )
mycursor=mydb.cursor();
mycursor.execute("use_DATABASE NAME")
"""

import random
import pandas as pd
import numpy as np
import os



def get_prod_rate(df,st_date=None,end_date=None):
    #returns the rate of each product bought in the given days range
    
    #filter dataframe by date
    if((st_date is not None)and(end_date is not None)):
        local_df=df[(df.Date>st_date) & (df.Date<end_date)]
    elif((st_date is None)and(end_date is not None)):
        local_df=df[(df.Date>df.Date.min()) & (df.Date<end_date)]
    elif((st_date is not None)and(end_date is None)):
        local_df=df[(df.Date>st_date) & (df.Date<df.Date.max())]
    else:
        local_df=df[(df.Date>df.Date.min()) & (df.Date<df.Date.max())]
        
    #number of days in the range of the new df
    local_df.Date=pd.to_datetime(local_df.Date)
    number_of_days= (local_df.Date.max()-local_df.Date.min()).days+1
    
    #count number of products bought in the days range
    n_products=local_df["itemDescription"].value_counts()
    customers_per_day = []
    for val in local_df.Date.unique():
        customers_per_day.append(local_df[local_df.Date==val].Member_number.unique().shape[0])
    #calc average customers per day:
    #day_counts = local_df.Date.value_counts()
    #avg_p_day = day_counts[day_counts<outlier_value].mean()
    #rate of how many purchase from each product in the days range
    return n_products/(number_of_days*(6/7)*np.mean(customers_per_day)),local_df #6 working days


def generate_buy_freq(df,n_buys_per_person=50):    
# generate unique rate to each person in the dataframe, assuming the populitation buys once in a week evarage
    freq_df=pd.DataFrame(columns=["id","rate"])
    freq_df.id=df.Member_number.unique()
    freq_df.rate=np.random.poisson(7,(freq_df.shape[0],))  
    it=0
# generate n_buys_per_person buys based on the rate
    for i,rate in enumerate(freq_df.rate):
        for n_buy in range(n_buys_per_person):
            freq_df.loc[i,'buy '+str(n_buy)]=np.random.poisson(rate,(1,))
            print("in generate_buy_freq ite= " +str(it))
            it+=1
    return freq_df

def generate_prod(prod_df,time_from_last_buy,sliced_final_df=None):
    example=[]
    for prod in prod_df:
        example.append(np.random.poisson(prod*time_from_last_buy,(1,))[0])
    return example
    

def generate_all(df,n_buys=50,**kuargs):
    prod_rate,local_df=get_prod_rate(df,**kuargs)
    
    #generated.df: id,buy_rate, days of buy_1, days of buy_2 ...days of buy_n (since last buy)
    generated_df=generate_buy_freq(local_df,n_buys)
    c_name=["id","date"]+prod_rate.index.unique().to_list()
    
    #c_name=bolumns for the final dataframe
    final_df=pd.DataFrame(columns=c_name)
    row_count=0
    it=0
    for indx,row in generated_df.iterrows():
        for column_name,k in enumerate(row):
            if row.index[column_name]=='id' or row.index[column_name]=='rate':
                continue
            print("in generate all- for&for. it= "+str(it))
            it+=1
            final_df.loc[row_count,'id']=row[0]
            final_df.loc[row_count,'date']=k
            #if(final_df[final_df['id']==row[0]].count()['id']>0):
             #   sliced_df=final_df[final_df['id']==row[0]]
            #else:
             #   sliced_df=None
            final_df.iloc[row_count,2:]=generate_prod(prod_rate,k)
            row_count+=1
    return final_df
            

"""
def get_person_rate(df,st_date=None,end_date=None):
    #returns the rate of each person's purchase in the given days range 
    
    #filter dataframe by date
    if((st_date is not None)and(end_date is not None)):
        local_df=df[(df.Date>st_date) & (df.Date<end_date)]
    elif((st_date is None)and(end_date is not None)):
        local_df=df[(df.Date>df.Date.min()) & (df.Date<end_date)]
    elif((st_date is not None)and(end_date is None)):
        local_df=df[(df.Date>st_date) & (df.Date<df.Date.max())]
    else:
        local_df=df[(df.Date>df.Date.min()) & (df.Date<df.Date.max())]
        
    #number of days in the range of the new df
    local_df.Date=pd.to_datetime(local_df.Date)
    number_of_days= (local_df.Date.max()-local_df.Date.min()).days+1
    
    #count number of persons bought in the days range
    n_persons=local_df["Member_number"].value_counts()
    return n_persons/number_of_days
"""
    
    
    
        
        
if __name__=='__main__':
    if not os.path.exists('generated_df.csv'):
        df=pd.read_csv("groceries_data.csv")
        #final_df=generate_all(df,3,st_date="2015-08-21",end_date="2015-08-29")
        final_df=generate_all(df,2)
        final_df.sort_values('id').to_csv('generated_df.csv',index=False)
    else:
        final_df.read_csv('generated_df.csv')








        
        
