# -*- coding: utf-8 -*-
"""
Created on Wed Feb  1 00:02:35 2023

@author: GILAD
"""

import pandas as pd
import numpy as np
import datetime as dt
import seaborn as sns
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

def milli_to_time(milner):
        return dt.datetime.fromtimestamp(milner/1000).strftime('%M:%S')




df=pd.read_csv('datasets/spotify_songs_features.csv',index_col=[0])


#loudness column is a decibel scale
# Describe the dataset and features before processing:
"""
Columns: 'track_name'': nominal, ''track_id'': nominal, ''album_name': nominal,'artist_name':nominak
        explicit': categorical boolean, 'danceability: ordinal, 'energy':ordinal, 'key':nominal, 
        'loudness':ordinal,:ordinal, 'liveness':ordinal,
       'valence':ordinal, 'tempo':ordinal, 'duration':ordinal, 'timesignature':nominal
       """
#print(df.describe())



############ Drop columns ############

#track_id isnt relevant to any corelation. its absolutly random and has nothing to do with the track features
df.drop(columns='track_id',axis=1,inplace=True)


############ Convert columns ############
# ALL CONVERTION BASED ON SPOTIFY API'S AUDIO FEATURES DESCRIPTION
# https://developer.spotify.com/documentation/web-api/reference/#/operations/get-several-audio-features

#df['energy'] = np.where(df['energy'] < 0.33, 'low',np.where(df['energy'] < 0.66, 'medium', 'high'))

#df['speechiness'] = np.where(df['speechiness'] < 0.33, 'low',np.where(df['speechiness'] < 0.66, 'medium', 'high'))

#df['valence'] = np.where(df['valence'] < 0.33, 'low',np.where(df['valence'] < 0.66, 'medium', 'high'))

"""
#convert duration from milliseconds to MM:SS
df['duration']=df['duration'].apply(milli_to_time)


#turning keys from integer scale to pitches using pitch class notation
keys = {0: "C", 1: "C#/Db", 2: "D", 3: "D#/Eb", 4: "E", 5: "F", 6: "F#/Gb",
        7: "G", 8: "G#/Ab", 9: "A", 10: "A#/Bb", 11: "B"}
df["key"] = df["key"].map(keys)


# 0=minor 1= major
modes={0:"minor",1:"major"}
df["mode"]=df["mode"].map(modes)
"""
"""
#under demian, dancibillity= false, above= true
Dmedian = df['danceability'].median()
df['danceability'] = df['danceability'].apply(lambda Dmedian: True if Dmedian > 0.5 else False)

print(df.describe())

############ Distirbutions ############

#explicitness distribution
df["explicit"].value_counts().plot(kind='bar')
plt.ylabel("Amount")
plt.title("Distribution of explicitness")
plt.show()

############ Distirbutions ############

#dancebillit distribution
df["danceability"].value_counts().plot(kind='bar')
plt.ylabel("Amount")
plt.title("Distribution of danceability")
plt.show()

#loudness distribution
df["loudness"].hist(bins=50)
plt.ylabel("Amount")
plt.title("Distribution of loudness")
plt.show()

#mode distribution
df["mode"].value_counts().plot(kind='bar')
plt.ylabel("Amount")
plt.title("Distribution of mode")
plt.show()

#speechiness distribution
df["speechiness"].hist(bins=50)
plt.ylabel("Amount")
plt.title("Distribution of speechiness")
plt.show()

#acusticness distribution
df["acousticness"].hist(bins=50)
plt.ylabel("Amount")
plt.title("Distribution of acusticness")
plt.show()

#instrumentalness distribution
df["instrumentalness"].hist(bins=50)
plt.ylabel("Amount")
plt.title("Distribution of instrumentalness")
plt.show()

#liveness distribution
df["liveness"].hist(bins=50)
plt.ylabel("Amount")
plt.title("Distribution of liveness")
plt.show()

#valence distribution
df["valence"].hist(bins=100)
plt.ylabel("Amount")
plt.title("Distribution of valence")
plt.show()

#tempo distribution
df["tempo"].hist(bins=50)
plt.ylabel("Amount")
plt.title("Distribution of tempo")
plt.show()


#dutarion distribution


a=(pd.DataFrame(df['duration'].apply(lambda x: int(x.split(':')[0]) * 60 + int(x.split(':')[1]))))
duration = a['duration'].to_numpy()
plt.hist(duration, bins= 60)
plt.xlabel('Duration (seconds)')
plt.title("Distribution of duration")
plt.ylim(0, 25000)
plt.xlim(0,1200)
plt.show()


#timesignature distribution
df["timesignature"].value_counts().plot(kind='bar')
plt.ylabel("Amount")
plt.title("Distribution of timesignature")
plt.show()
zz=2
"""
corr = df.corr()
sns.heatmap(corr,xticklabels = corr.columns, yticklabels = corr.columns, cmap="Blues", vmax=0.3, center=0,
            square=True, linewidths=.5, cbar_kws={"shrink": .8})
# Cleanse and preprocess the dataset
# ...

# Describe the dataset and features after processing
print("Dataset after processing:")
print(df.describe())

