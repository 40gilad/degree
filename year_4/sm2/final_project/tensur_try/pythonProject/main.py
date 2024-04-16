# region create_models

import sys
import os
import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras.layers import Input, MaxPooling2D, Conv2D, Dense, LeakyReLU, BatchNormalization, \
    AveragePooling2D, GlobalAveragePooling2D, Cropping2D, Flatten, Multiply, ReLU, ELU, GlobalMaxPooling2D, Concatenate, \
    Softmax, DepthwiseConv2D, Activation
from tensorflow.keras.applications import resnet50, efficientnet, mobilenet
from tensorflow.keras.models import Model, load_model
from tensorflow.keras.optimizers import SGD, Adam
from tensorflow.keras.activations import relu
from tensorflow.keras import backend as K


def create_resnet50(input_shape, lr, n_classes):
    base_model = resnet50.ResNet50(weights='imagenet', include_top=False, input_shape=input_shape)
    for l in base_model.layers:
        l.trainable = False
    input = Input(shape=input_shape)
    x = resnet50.preprocess_input(input)
    x = base_model(x)
    x = GlobalAveragePooling2D()(x)
    x = Dense(n_classes, activation='softmax')(x)
    model = Model(inputs=input, outputs=x)
    model.compile(loss='categorical_crossentropy',optimizer='SGD',metrics=['accuracy'])
    return model


# endregion


# region main
import os
from pathlib import Path
from datetime import datetime
from keras.models import load_model
from sklearn.model_selection import train_test_split
import pandas as pd
import numpy as np
import tensorflow as tf
import shutil
from tensorflow.keras.preprocessing.image import ImageDataGenerator

import matplotlib.pyplot as plt

if __name__ == '__main__':
    project_name = 'letters'
    dataset_name = 'aaa'

    # -- paths ----
    train_path = Path(
        r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\asl_alphabet_train\asl_alphabet_train')  # path to train images directory
    train_metapath = train_path / 'metadata.csv'
    test_path = Path(
        r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\asl_alphabet_test\asl_alphabet_test')  # path to test images directory
    test_metapath = test_path / 'metadata.csv'

    # -- params ----
    bs = 32  # batch size
    ts = (50, 50)  # target size
    x_col = 'filename'  # the column in the dataframe that contains the path to the images
    y_col = 'class_encoding'
    validation_split = 0.2  # train validation split
    lr = 1e-3
    epochs = 1
    steps = 100

    tag = 'kaki'  # run tag

    # --- dirs ---
    tagdir = Path(
        r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project') / f'{tag}_{datetime.now().strftime("%H_%M_%S")}'
    tagdir.mkdir(exist_ok=True, parents=True)
    plotsdir = tagdir / 'plots'
    plotsdir.mkdir(exist_ok=True, parents=True)

    # --- read and preprocess metadata ----
    df_trn = pd.read_csv(train_metapath)  # get metadata
    df_tst = pd.read_csv(test_metapath)  # get metadata

    df_trn['filename'] = df_trn.filename.apply(lambda f: str(train_path / f))
    df_trn.class_encoding = df_trn.class_encoding.astype(str)
    df_tst['filename'] = df_tst.filename.apply(lambda f: str(test_path / f))
    df_tst.class_encoding = df_tst.class_encoding.astype(str)


    df_tst_pp = df_tst.copy()
    df_trn_pp, df_val_pp = train_test_split(df_trn, test_size=validation_split,
                                            random_state=666)

    # --- make gens ----
    trn_gen = ImageDataGenerator(rotation_range=10, width_shift_range=5, height_shift_range=5, zoom_range=0.1,
                                 channel_shift_range=10, shear_range=10).flow_from_dataframe(df_trn_pp,
                                                                                             x_col='filename',
                                                                                             y_col='class_encoding',
                                                                                             target_size=ts,
                                                                                             class_mode='categorical')
    val_gen = ImageDataGenerator().flow_from_dataframe(df_val_pp, x_col='filename', y_col='class_encoding',
                                                       target_size=ts, class_mode='categorical')
    tst_gen = ImageDataGenerator().flow_from_dataframe(df_tst_pp, x_col='filename', y_col='class_encoding',
                                                       target_size=ts, shuffle=False, class_mode='categorical')

    fit_dict = {
        'epochs': epochs,
        'steps_per_epoch': int(np.minimum(np.floor(df_trn_pp.shape[0] / bs), steps)),
        'verbose': 1
    }
    reduce_lr_cb = tf.keras.callbacks.ReduceLROnPlateau(monitor='val_loss', mode='min', factor=np.sqrt(0.1),
                                                        min_delta=1e-4, patience=5, min_lr=1e-5, verbose=1, cooldown=3)
    earlystop_cb = tf.keras.callbacks.EarlyStopping(monitor='val_accuracy', mode='max', min_delta=1e-4,
                                                    patience=15, verbose=1, baseline=None, restore_best_weights=True)
    callbacks = [reduce_lr_cb, earlystop_cb]
    model = create_resnet50(input_shape=(ts[0], ts[1], 3), lr=lr, n_classes=26)
    # --- fit model ---
    model.fit(trn_gen, validation_data=val_gen, callbacks=callbacks, **fit_dict)

    # -- save model --
    fn = tagdir / f'{tag}.h5'
    model.save(fn)
    print(f'Model saved to : {fn}')
    # --- evaluate ---
    dfval = evaluate_multi(model, gen_val, df_val_pp, class_encoding_in_val, x_col, y_col, plotsdir, prefstr='Val')
    dftst = evaluate_multi(model, gen_test, df_tst_pp, class_encoding_in_test, x_col, y_col, plotsdir, prefstr='Test')

    # --- save results ---
    dftst.to_csv(tagdir / 'dftst.csv')
    dfval.to_csv(tagdir / 'dfval.csv')

    shutil.copy(__file__, tagdir / 'script.py')
    shutil.copy(Path(os.environ['DL_PATH']) / 'algo/projects/murata/phase_2/gen.py', tagdir / 'gen.py')
    shutil.copy(Path(os.environ['DL_PATH']) / 'algo/projects/murata/phase_2/models_playground.py', tagdir / 'models.py')
    print('Done!!!')

# endregion
