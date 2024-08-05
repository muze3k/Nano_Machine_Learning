from numpy import random
import matplotlib.pyplot as plt
#import seaborn as sns
import numpy as np
import tensorflow as tf
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.models import Model

model = tf.keras.models.load_model("esp32.h5")

testData = np.array([ 0.72779332,  1.12606976, -0.31331522, -0.05345183, -0.02599893])

predict = model.predict(np.expand_dims(testData, axis=0))

print(predict)