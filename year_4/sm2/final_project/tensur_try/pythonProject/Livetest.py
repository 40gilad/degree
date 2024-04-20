import cv2
import numpy as np
from PIL import Image
import mediapipe as mp
import matplotlib.pyplot as plt
import tensorflow as tf
import os

os.environ['CUDA_VISIBLE_DEVICES'] = ''
loaded_model_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\running_outputs\bs=32_ts=(128, 128)_valSplit=0.2_lr=0.001_epochs=120_10_51_04\bs=32_ts=(128, 128)_valSplit=0.2_lr=0.001_epochs=120.h5'
loaded_model = tf.keras.models.load_model(loaded_model_dir)

class_to_letter = ['A','B', 'C','D','E' ,'F', 'G', 'H', 'I','J' ,'K', 'L', 'M', 'N','O', 'P','Q' ,'R', 'S', 'T','U','V', 'W','X','Y','Z' 'nothing']


def cut_image(image, size=(128, 128)):
    """
    :param image: cv2 image
    :return: cv2 image (hand)
    """
    image = image.astype(np.uint8)
    processed_image = hands.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    if processed_image.multi_hand_landmarks:
        hand_landmarks = processed_image.multi_hand_landmarks[0]
        x_coords = [landmark.x for landmark in hand_landmarks.landmark]
        y_coords = [landmark.y for landmark in hand_landmarks.landmark]
        x_min, x_max = min(x_coords), max(x_coords)
        y_min, y_max = min(y_coords), max(y_coords)

        x_min_adjust = int(x_min * image.shape[1] - 80)
        y_min_adjust = int(y_min * image.shape[0] - 80)
        x_max_adjust = int(x_max * image.shape[1] + 80)
        y_max_adjust = int(y_max * image.shape[0] + 80)
        if x_min_adjust < 0:
            x_min_adjust = int(x_min * image.shape[1] - 15)
            if x_min_adjust < 0:
                x_min_adjust = 0
        if y_min_adjust < 0:
            y_min_adjust = int(y_min * image.shape[0] - 15)
            if y_min_adjust < 0:
                y_min_adjust = 0
        x_min = x_min_adjust
        y_min = y_min_adjust
        x_max = x_max_adjust
        y_max = y_max_adjust
        hand_region = image[y_min:y_max, x_min:x_max]
        hand_region_uint8 = hand_region.astype(np.uint8)
    else:
        hand_region_uint8 = image.astype(np.uint8)
    hand_region_bgr = cv2.cvtColor(hand_region_uint8, cv2.COLOR_RGB2BGR)
    hand_region_bgr = cv2.resize(hand_region_bgr, dsize=size)
    return hand_region_bgr




# Function to make a prediction on a single image
def predict_image(image):
    if image is None:
        return "No image provided"

    if image is None:
        return "Failed to transform image"


    # Make a prediction on the single image
    image = np.expand_dims(image, axis=0)
    raw_pred = loaded_model.predict(image)
    pred = raw_pred.argmax(axis=1)
    print(f"Predicted class = + {pred[0]}")
    return class_to_letter[pred[0]]


# Initialize the MediaPipe hand detector
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(static_image_mode=False, max_num_hands=1, min_detection_confidence=0.5)

# Initialize the MediaPipe drawing utilities
mp_drawing = mp.solutions.drawing_utils

# Open the webcam
cap = cv2.VideoCapture(0)

while True:
    # Capture a frame from the webcam
    ret, frame = cap.read()

    if cv2.waitKey(1) & 0xFF == ord('s'):
        # Use MediaPipe to detect the hand and pose in the frame
        hand_region = cut_image(frame)

        predicted_letter = predict_image(hand_region)
        print(f'predicted_letter= {predicted_letter}')

    # Display the frameb
    cv2.imshow('Real-time ASL Prediction', frame)

    # Exit the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close all windows
cap.release()
cv2.destroyAllWindows()
