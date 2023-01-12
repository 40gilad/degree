# -*- coding: utf-8 -*-
"""
Created on Thu Jan  5 23:27:02 2023

@author: GILAD
"""
import pandas as pd
import numpy as np
import os


def df_to_mat(df,col_index):
    #transfer to matrix
    mat=df.iloc[:,col_index[0]:col_index[1]].to_numpy()
    zz=3
    return mat

def find_nearest_neigb(df_trn,df_val,df_tst):
    hits_arr=[]
    counter=0
    for ind,row in df_tst.iterrows():
        print(counter/df_tst.shape[0])
        cur_df_trn_meta_data=df_trn[df_trn.date==row.date].iloc[:,[2,-1]]
        #row.date=days from last buy of each costumer
        cur_df_trn_meta_data=cur_df_trn_meta_data[cur_df_trn_meta_data.Buying_index>0]
        cur_df_trn_meta_data.Buying_index=cur_df_trn_meta_data.Buying_index-1
        cur_df_trn=df_trn.iloc[cur_df_trn_meta_data.index-1,:]
        cur_df_mat=df_to_mat(cur_df_trn,[4,170])
        cur_vec=df_val[(df_val.Buying_index==row.Buying_index-1) & (df_val.id==row.id)].to_numpy().squeeze()[4:170]
        dist=np.mean(np.abs(cur_df_mat-cur_vec),axis=1)
        #mean dist from each row to the curr costumer list
        minimal_dist_index=np.argmin(dist)
        closest_subject=cur_df_trn.iloc[minimal_dist_index,[2,-1]]
        predicted_list=df_trn[(df_trn.id==closest_subject[0])&(df_trn.Buying_index==closest_subject[1]+1)]
        number_of_hits=np.where((predicted_list.to_numpy().squeeze()[4:170]-row.to_numpy().squeeze()[4:170])==0)[0].shape[0]
        hits_arr.append(number_of_hits)
        print(number_of_hits)
        counter+=1
    return hits_arr
    

if __name__=="__main__":
    trn_size=47
    val_size=1
    tst_size=1
    df=pd.read_csv("generated_with_buying_index.csv")
    trn_set=df[(df.Buying_index<=trn_size)].reset_index()
    val_set=df[(df.Buying_index>trn_size) & (df.Buying_index<=trn_size+val_size)].reset_index()
    tst_set=df[(df.Buying_index>trn_size+val_size) & (df.Buying_index<=50)].reset_index()
    result_arr=find_nearest_neigb(trn_set,val_set,tst_set)
    zz=1
    