# -*- coding: utf-8 -*-
"""
Created on Sat Feb  4 15:34:00 2023

@author: GILAD - 313416562
@author: SHAHAR - 314868977
"""

import itertools
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn import metrics
from sklearn.linear_model import LogisticRegression


def plot_dist(arr, target_path, nbins, xlabel, ylabel):
    fig = plt.figure(figsize=(15, 10))
    ax = fig.add_subplot(1, 1, 1)
    counts, centers = np.histogram(arr, bins=nbins)
    ax.hist(arr, bins=nbins, label='Histogram', alpha=0.5)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.grid()
    ax.axvline(arr.mean(), 0, counts.max(), color='red', label='mean', linewidth=3)
    ax.axvline(arr.mean() - arr.std(), color='green', label='std', linewidth=3)
    ax.axvline(arr.mean() + arr.std(), color='green', linewidth=3)
    ax.legend(loc='upper left')
    ax.set_title('Histogram for song ' + xlabel)
    fig.savefig(target_path)
    plt.close('all')


def plot_corr(corr, target_path, **kwargs):
    plt.figure(figsize=(15, 15))
    sns.set(font_scale=2)
    sns_fig = sns.heatmap(corr, xticklabels=corr.columns, yticklabels=corr.columns, cmap="hot",
                          square=True, linewidths=.5, cbar_kws={"shrink": .8})
    fig = sns_fig.get_figure()
    fig.savefig(target_path)
    plt.close('all')


def plot_stats_from_df(df, main_path, verb=True):
    for ind, col in df.iteritems():
        plot_dist(col.to_numpy(), main_path + '\\' + ind + '_hist.png', 100, xlabel=ind, ylabel='counts')
    plot_corr(df.corr(), main_path + '\\features_corr.png')


def plot_corr_between_feat(df, col1, col2, target_path):
    arr1 = df[col1].to_numpy()
    arr2 = df[col2].to_numpy()
    fig = plt.figure(figsize=(15, 15))
    ax = fig.add_subplot(1, 1, 1)
    ax.scatter(arr1, arr2, label='Data points')
    ax.set_xlabel(col1, fontsize=20)
    ax.set_ylabel(col2, fontsize=20)

    a, b = np.polyfit(arr1, arr2, 1)  # linear args
    a_2, b_2, c_2 = np.polyfit(arr1, arr2, 2)  # sec order polynom args
    arr1_vec = np.arange(arr1.min(), arr1.max(), 0.01)  # set vector with 0.01 "jumps"

    ax.plot(arr1_vec,
            arr1_vec * a + b, 'r', label='Linear fit')

    ax.plot(arr1_vec,
            (arr1_vec ** 2) * a_2 + b_2 * arr1_vec + c_2,
            'g', label='2 order polynom fit')

    ax.set_title(
        'scatter plot of ' + col1 + ' and ' + col2 + ' corr coef= ' + str(np.round(np.corrcoef(arr1, arr2)[0, 1], 2)),
        fontsize=25)

    ax.tick_params(axis='both', which='major', labelsize=15)
    ax.legend()
    ax.set_ylim(arr2.min(), arr2.max())
    fig.savefig(target_path + '\\' + 'corr_' + col1 + '_' + col2 + '.png')
    plt.close('all')


if __name__ == "__main__":
    # Insert after the " r' " the path you wish to save all the figures
    target = r'C:\Users\40gil\OneDrive\Desktop\degree\year_3\sm1\Python\final_assig\figures'

    # Insert the path of the raw_dataset to read it
    df = pd.read_csv('datasets/raw_dataset.csv', index_col=[0])

    # dropping irrelevant columns
    col_to_drop = ['track_id', 'album_name', 'explicit', 'key', 'mode_feat', 'duration', 'timesignature']
    df.drop(columns=col_to_drop, axis=1, inplace=True)

    # split to train and test
    df_trn, df_tst = train_test_split(df, test_size=0.1, random_state=1)

    plot_stats_from_df(df_trn.iloc[:, 2:-1], target)


    cols = df_trn.iloc[:, 2:-1].keys()
    for col_name1, col_name2 in itertools.combinations(cols, 2):
        plot_corr_between_feat(df_trn, col_name2, col_name1, target)


    # Binerize danceability for train and test after plotting the train set with danceability actual value
    median_dance_trash = df_trn.danceability.median()
    df_trn.loc[df_trn.danceability >= median_dance_trash, 'danceability'] = 1
    df_trn.loc[df_trn.danceability < median_dance_trash, 'danceability'] = 0
    df_tst.loc[df_tst.danceability >= median_dance_trash, 'danceability'] = 1
    df_tst.loc[df_tst.danceability < median_dance_trash, 'danceability'] = 0

    log_reg = LogisticRegression()

    # numpy arrying all train features
    valence_feat = df_trn.valence.to_numpy()
    energy_feat = df_trn.energy.to_numpy() ** 2
    loudness_feat = df_trn.loudness.to_numpy()
    feat_mat = np.stack((valence_feat, energy_feat, loudness_feat)).T
    target_class = df_trn.danceability.to_numpy()

    # numpy arrying all test features
    valence_feat_tst = df_tst.valence.to_numpy()
    energy_feat_tst = df_tst.energy.to_numpy() ** 2
    loudness_feat_tst = df_tst.loudness.to_numpy()
    feat_mat_tst = np.stack((valence_feat_tst, energy_feat_tst, loudness_feat_tst)).T
    tst_labels = df_tst.danceability.to_numpy()

    # fitting a logistic regression for training
    log_reg.fit(feat_mat, target_class)

    # predict a logistic regression
    tst_pred = log_reg.predict(feat_mat_tst)

    # showing result of prediction
    sns.set(font_scale=1)
    confusion_matrix = metrics.confusion_matrix(tst_labels, tst_pred)
    cm_display = metrics.ConfusionMatrixDisplay(confusion_matrix=confusion_matrix,
                                                display_labels=['Undanceable', 'Danceable'])
    cm_display.plot()
    plt.title('accuracy= ' + str(np.round((confusion_matrix[0, 0] + confusion_matrix[1, 1]) / confusion_matrix.sum(), 2)))
    plt.savefig(target + '\\' + 'confusion_matrix.png')
    plt.show()

    # Binerize the danceability on the df and save to a new dataset
    median_dance = df.danceability.median()
    df.loc[df.danceability >= median_dance, 'danceability'] = 1
    df.loc[df.danceability < median_dance, 'danceability'] = 0
    df.to_csv('datasets/ready_dataset.csv')

