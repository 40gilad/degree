from datetime import time

import cv2
import mediapipe as mp
import os
import numpy as np
import datetime

mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose


def sharpen_image(image):
    kernel = np.array([[-1, -1, -1],
                       [-1, 9, -1],
                       [-1, -1, -1]])
    return cv2.filter2D(image, -1, kernel)


video_path = "C:\\Users\\40gil\\Desktop\\degree\\year_4\\sm1\\final_project\\PoseDetect\\videos\\SlowMotion.mp4"
dir_name=f'RUN_{datetime.datetime.now().strftime("%d%m_%H%M")}'
# VIDEO FEED

cap = cv2.VideoCapture(video_path)
## Setup mediapipe instance
with mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.1) as pose:
    counter=0
    while cap.isOpened():
        ret, frame = cap.read()

        # Recolor image to RGB
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image.flags.writeable = False

        en_image = sharpen_image(sharpen_image(image))

        # Make detection
        results = pose.process(image)
        output_folder = f'..\\ImagesOutput\\Raw\\{dir_name}'

        # Make detection
        en_results = pose.process(en_image)
        en_output_folder = f'..\\ImagesOutput\\Enhanced\\{dir_name}'

        if not os.path.exists(output_folder):
            os.makedirs(output_folder)

        if not os.path.exists(en_output_folder):
            os.makedirs(en_output_folder)

        # Recolor back to BGR
        image.flags.writeable = True
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        # Recolor back to BGR
        en_image.flags.writeable = True
        en_image = cv2.cvtColor(en_image, cv2.COLOR_RGB2BGR)

        # Render detections
        mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS,
                                  mp_drawing.DrawingSpec(color=(245, 117, 66), thickness=2, circle_radius=2),
                                  mp_drawing.DrawingSpec(color=(245, 66, 230), thickness=2, circle_radius=2)
                                  )

        # Render detections
        mp_drawing.draw_landmarks(en_image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS,
                                  mp_drawing.DrawingSpec(color=(245, 117, 66), thickness=2, circle_radius=2),
                                  mp_drawing.DrawingSpec(color=(245, 66, 230), thickness=2, circle_radius=2)
                                  )
        cv2.imwrite(os.path.join(output_folder, f"SlowMo_frame{counter}.jpg"), image)
        cv2.imwrite(os.path.join(en_output_folder, f"SlowMo_frame{counter}.jpg"), en_image)

        counter += 1

        cv2.imshow('Mediapipe Feed', image)
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()
