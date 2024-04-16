import sys
import os
import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras.layers import Input,MaxPooling2D,Conv2D, Dense, LeakyReLU, BatchNormalization,\
    AveragePooling2D,GlobalAveragePooling2D,Cropping2D,Flatten, Multiply, ReLU, ELU, GlobalMaxPooling2D, Concatenate, Softmax, DepthwiseConv2D, Activation
from tensorflow.keras.applications import resnet50, efficientnet, mobilenet
from tensorflow.keras.models import Model, load_model
from tensorflow.keras.optimizers import SGD, Adam
from tensorflow.keras.activations import relu
from tensorflow.keras import backend as K


def create_resnet50(input_shape, lr, n_classes):
    base_model=resnet50.ResNet50(weights='imagenet', include_top=False, input_shape=input_shape)
    input=base_model.input

    zz=1