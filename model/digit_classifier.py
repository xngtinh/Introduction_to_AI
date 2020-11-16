import numpy as np
from tensorflow.keras.layers import Dense, Input
from tensorflow.keras.models import Model
from tensorflow.keras.losses import SparseCategoricalCrossentropy
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.metrics import SparseCategoricalAccuracy
from tensorflow.keras.callbacks import EarlyStopping
from tensorflow.keras.models import load_model


class DigitClassifier:
    def __init__(self):
        self.model = None

    def build_model(self):
        input_layer = Input(shape=784)
        dense_layer_0 = Dense(512, activation='relu')(input_layer)
        dense_layer_1 = Dense(256, activation='relu')(dense_layer_0)
        dense_layer_2 = Dense(128, activation='relu')(dense_layer_1)
        dense_layer_3 = Dense(64, activation='relu')(dense_layer_2)
        dense_layer_4 = Dense(32, activation='relu')(dense_layer_3)
        output_layer = Dense(10, activation='softmax')(dense_layer_4)
        self.model = Model(input_layer, output_layer)
        print(self.model.summary())

        loss = SparseCategoricalCrossentropy()
        optimizer = Adam(learning_rate=1e-3)

        self.model.compile(loss=loss, optimizer=optimizer, metrics=[SparseCategoricalAccuracy()])

    def load_model(self):
        self.model = load_model('test.json')

    def save_model(self):
        self.model.save('test.json')

    def train(self, x, y, **kwargs):
        es = EarlyStopping(monitor='val_loss', mode='min', verbose=1, patience=5)
        self.model.fit(x, y, validation_split=0.2, batch_size=32, epochs=50, callbacks=[es])

    def predict(self, x_test):
        """
        :param x_test: a numpy array with dimension (N,D)
        :return: a numpy array with dimension (N,)
        """

        y_predict = self.model.predict(x_test, batch_size=32)
        return y_predict.argmax(axis=1)
