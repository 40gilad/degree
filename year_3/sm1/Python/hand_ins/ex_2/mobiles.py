import pandas as pd
"""
Created on Wed Nov 23 19:45:39 2022

@author: GILAD
"""

#df.query("(f_camera>12 or camera>12) and sim==Single")




############################ TASK 1 ############################
#1
df= pd.read_csv('mobile_price_1.csv')
"""
from google.colab import files
uploadedFile = files.upload()
"""

#3
df['resolution'] = df.apply(lambda x : str(x.px_height)+'x'+str(x.px_width),axis=1)

#4
df['DPI_w']=df.apply(lambda x : (float(x.px_width)/float(x.sc_w/2.54)) if x.sc_w!=0 else 0,axis=1)

#5
df['call_ratio']=df.apply(lambda x : x.battery_power/x.talk_time,axis=1).round(2)

#6
df['memory']=df['memory']/1000

#7
print(df.describe())

#8

df['cores']=df['cores'].astype(
    pd.CategoricalDtype(['single','dual','triple','quad','penta','hexa', 'hepta','octa'],
                        ordered = True))

df['speed']=df['speed'].astype(
    pd.CategoricalDtype(['low','medium','high'],
                        ordered=True))

df['screen']=df['screen'].astype(
    pd.CategoricalDtype(['LCD','Touch'],
                        ordered=False))


############################ TASK 2 ############################
#1
df[df.camera.isnull() & df.f_camera.isnull()].shape[0]

#2
df[(df.sim.str.lower() == 'single')&((df.camera>12) | (df.f_camera>12))].battery_power.mean().round(2)

#3
a=df[(df.screen=='Touch') & (df.wifi=='none') & (df.mobile_wt > 145)].sort_values(by='price').tail(1)
print("ID: ",*a['id'],"\nprice: ",*a['price'])

#5
ndf=df[df.speed=='medium'].sample(frac=0.5,random_state=1)[
    ['id','battery_power','ram','talk_time','bluetooth','cores','sim','memory','price']].sort_index()


#6
print("Total talk time you can achive is:",ndf[['id','talk_time']].sort_values(by='talk_time').
      tail(3).talk_time.sum())

print("\nwith phones:\n",ndf[['id','talk_time']].sort_values(by='talk_time').
      tail(3).id.to_string(index=False))



