# -*- coding: utf-8 -*-
"""
Created on Fri Jan 27 00:42:26 2023

@author: GILAD
"""
import ezshop_algo_api as ez
import pandas as pd
"""
 
"""
if __name__=="__main__":
    df=pd.read_csv('df_with_time_from_last_buy.csv')
    zevel=df[df.id==1000]
    aa=ez.get_empty_products_list()
    newList=next(iter(ez.get_list_by_id(1000,42).iloc[:,2:-1].to_dict(orient='index').values()))
    secList=next(iter(ez.get_list_by_id(1000,43).iloc[:,2:-1].to_dict(orient='index').values()))
    ez.add_list(1,newList)
    ez.add_list(1,secList)
    #predicted['whole milk']=20
    #ez.add_list(1,predicted)
    zz=ez.predict_list(1, 10)
    ez.add_list(1, zz)
    b=ez.get_list_by_id(1)
    w=1