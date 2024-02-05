from datetime import time

import cv2
import mediapipe as mp
import os
import numpy as np
import datetime

mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose

import cv2


def black_and_white(frame):
    # Convert the frame to black and white
    bw_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # If you want to keep it as a 3-channel image (BGR) with the same values for R, G, and B
    bw_frame_bgr = cv2.cvtColor(bw_frame, cv2.COLOR_GRAY2BGR)

    return bw_frame_bgr


def smooth_image(image):
    return cv2.GaussianBlur(image, (5, 5), 0)


def sharpen_image(image):
    kernel = np.array([[-1, -1, -1],
                       [-1, 9, -1],
                       [-1, -1, -1]])
    return cv2.filter2D(image, -1, kernel)


def display_and_save_image(image, landmarks, connections, frame_number, dir_name):
    output_folder = f'ImagesOutput\\Raw\\{dir_name}'
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Render detections
    mp_drawing.draw_landmarks(image, landmarks, connections,
                              mp_drawing.DrawingSpec(color=(245, 117, 66), thickness=2, circle_radius=2),
                              mp_drawing.DrawingSpec(color=(245, 66, 230), thickness=2, circle_radius=2)
                              )

    # Add frame number to the image
    frame_number_text = f"Frame: {frame_number}"
    cv2.putText(image, frame_number_text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 2, (255, 255, 255), 2, cv2.LINE_AA)
    cv2.imshow('Mediapipe Feed', image)
    cv2.imwrite(os.path.join(output_folder, f"SlowMo_frame{frame_number}.jpg"), image)


def calculate_angle(a, b, c):
    a = np.array(a)  # First
    b = np.array(b)  # Mid
    c = np.array(c)  # End

    radians = np.arctan2(c[1] - b[1], c[0] - b[0]) - np.arctan2(a[1] - b[1], a[0] - b[0])
    angle = np.abs(radians * 180.0 / np.pi)

    if angle > 180.0:
        angle = 360 - angle

    return angle

def main(video_path="C:\\Users\\40gil\\Desktop\\degree\\year_4\\sm1\\final_project\\PoseDetect\\videos\\SlowMotion.mp4"
         ):
    dir_name = f'RUN_{datetime.datetime.now().strftime("%d%m_%H%M")}'
    # VIDEO FEED

    cap = cv2.VideoCapture(video_path)
    ## Setup mediapipe instance
    with mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0, model_complexity=2) as pose:
        counter = 0
        while cap.isOpened():
            ret, frame = cap.read()
            # Recolor image to RGB
            image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            image.flags.writeable = False

            # Make detection
            results = pose.process(image)

            # Recolor back to BGR
            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

            # Extract landmarks
            try:
                landmarks = results.pose_landmarks.landmark
            except:
                pass

                #extractin x,y values for each joint
            Lhip = [landmarks[mp_pose.PoseLandmark.RIGHT_HIP.value].x,
                        landmarks[mp_pose.PoseLandmark.RIGHT_HIP.value].y]
            Lknee = [landmarks[mp_pose.PoseLandmark.RIGHT_KNEE.value].x,
                         landmarks[mp_pose.PoseLandmark.RIGHT_KNEE.value].y]
            Lankle = [landmarks[mp_pose.PoseLandmark.RIGHT_ANKLE.value].x,
                         landmarks[mp_pose.PoseLandmark.RIGHT_ANKLE.value].y]
            angle=calculate_angle(Lhip,Lknee,Lankle)
            disp_angle=format(angle,".2f")
            # Visualize angle
            cv2.putText(image, f'Right knee degree: {disp_angle}',
                           (10,60),
                           cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2, cv2.LINE_AA
                                )

            # --------------------- OUTPUTTING THE POSE TO SCREEN AND FILE ---------------------#

            display_and_save_image(image=image, landmarks=results.pose_landmarks,
                                   connections=mp_pose.POSE_CONNECTIONS,
                                   frame_number=counter, dir_name=dir_name
                                   )
            counter += 1

            if cv2.waitKey(10) & 0xFF == ord('q'):
                # if 'q' button was pressed
                break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
