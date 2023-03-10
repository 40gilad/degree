# -*- coding: utf-8 -*-
"""
Created on Tue Jan 24 10:46:13 2023

@author: GILAD
"""

import pandas as pd
import numpy as np
import os
import matplotlib.pyplot as plt
import seaborn as sns
plt.style.use('classic')

test_df=pd.read_csv('tst_df.csv')
predictions_df=pd.read_csv('predictions_df.csv')
hits=np.load('pred_result_arr.npy')

#plt.hist(hits,bins=[90,100,110,115,120,125,130,135,140,145,150,155,160,166]()
plt.hist(hits,bins=60,label='Histogram')
plt.xlabel('list hits')
plt.ylabel('counts')
plt.axvline(hits.mean(),0,160,color='red',label='mean',linewidth=3)
plt.axvline(hits.mean()-hits.std(),color='green',label='std',linewidth=3)
plt.axvline(hits.mean()+hits.std(),color='green',linewidth=3)
plt.ylim(0,260)
plt.legend(loc='upper left')

plt.show()


zz=3