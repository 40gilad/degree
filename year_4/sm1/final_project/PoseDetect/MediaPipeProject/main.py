import mediapipe as mp
import os
import numpy as np
import datetime
import cv2
import math

# region Colors

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE = (255, 0, 0)
RED = (0, 0, 255)
CYAN = (255, 255, 0)
YELLOW = (0, 255, 255)
MAGENTA = (255, 0, 255)
GREEN = (0, 255, 0)
PURPLE = (128, 0, 128)
ORANGE = (0, 165, 255)
PINK = (147, 20, 255)
INDIGO = (75, 0, 130)
VIOLET = (238, 130, 238)
GRAY = (127, 127, 127)

# endregion

# region Globals
mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose
camalogo_path = None


# endregion

# region Support functions

def create_output_folder(output_folder):
    output_folder = f'FramesOutput\\{output_folder}'
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)


# endregion

# region Image Menipulation
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


def add_cama_logo(frame):
    # Logo is PNG Only
    # Put the logo in the top right corner of the image

    if camalogo_path:
        try:
            logo = cv2.imread(camalogo_path, cv2.IMREAD_UNCHANGED)

            # Extract alpha channel from the logo
            alpha_channel = logo[:, :, 2]

            # Resize logo to fit a reasonable fraction of the frame
            logo_size = (int(frame.shape[1] // 10), int(frame.shape[0] // 13))
            resized_logo = cv2.resize(logo, logo_size)

            # Define the region in the top right corner for the logo
            top_right_y, top_right_x = 5, 5
            roi = frame[top_right_y:top_right_y + resized_logo.shape[0],
                  -resized_logo.shape[1] - top_right_x:-top_right_x]

            # Create a mask for the logo
            logo_alpha = resized_logo[:, :, 2] / 255.0
            background_alpha = 1.0 - logo_alpha

            # Blend the logo and the frame
            for c in range(0, 3):
                roi[:, :, c] = (background_alpha * roi[:, :, c] +
                                logo_alpha * resized_logo[:, :, c])
        except:
            return frame

    return frame


# endregion

# region Frames Analyze
def display_and_save_image(image, landmarks, connections, frame_number, dir_name, display_window_name="Mediapipe Feed",
                           to_save=True):
    output_folder = f'FramesOutput\\{dir_name}'

    # Render detections
    mp_drawing.draw_landmarks(image, landmarks, connections,
                              mp_drawing.DrawingSpec(color=(245, 117, 66), thickness=2, circle_radius=2),
                              mp_drawing.DrawingSpec(color=(245, 66, 230), thickness=2, circle_radius=2)
                              )

    # Add frame number to the image
    frame_number_text = f"Frame: {frame_number}"
    cv2.putText(image, frame_number_text, (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 0), 5, cv2.LINE_AA)

    add_cama_logo(image)
    cv2.imshow(display_window_name, image)
    if to_save:
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


# endregion


# region Main
def main(source_video_dir_path, video_name, to_save=False):
    output_dir_name = f'{video_name}_{datetime.datetime.now().strftime("Date-%d.%m_Time-%H.%M")}'
    video_path = f'{source_video_dir_path}\\{video_name}.mp4'
    if to_save:
        create_output_folder(output_folder=output_dir_name)

    # VIDEO FEED

    cap = cv2.VideoCapture(video_path)
    ## Setup mediapipe instance
    with mp_pose.Pose(min_detection_confidence=0.9, min_tracking_confidence=0.9, model_complexity=2) as pose:
        frame_counter = -1
        meta_counter = 0
        slap_counter = 1
        start_angle = 0
        while cap.isOpened():
            frame_counter += 1
            ret, frame = cap.read()
            # Recolor image to RGB
            image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            image.flags.writeable = False

            # Make detection
            results = pose.process(image)

            # Recolor back to BGR
            image.flags.writeable = True
            image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
            image = cv2.resize(image, (960, 540))

            # Extract landmarks
            try:
                landmarks = results.pose_landmarks.landmark
            except:
                landmarks = None
            if landmarks is None:
                continue
                # extracting x,y values for each joint
            Lshoulder = [landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER.value].x,
                         landmarks[mp_pose.PoseLandmark.LEFT_SHOULDER.value].y]
            Rshoulder = [landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER.value].x,
                         landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER.value].y]
            Relbow = [landmarks[mp_pose.PoseLandmark.RIGHT_ELBOW.value].x,
                      landmarks[mp_pose.PoseLandmark.RIGHT_ELBOW.value].y]

            RsoulderPos = [format(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER.value].x, ".2f"),
                           format(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER.value].y, ".2f"),
                           format(landmarks[mp_pose.PoseLandmark.RIGHT_SHOULDER.value].z, ".3f")]

            angle = calculate_angle(Lshoulder, Rshoulder, Relbow)
            disp_angle = format(angle, ".2f")
            # Visualize angle
            cv2.putText(image, f'Right Shoulder degree: {disp_angle}',
                        (10, 90),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, PURPLE, 2, cv2.LINE_AA
                        )

            cv2.putText(image, f'Right Shoulder Position x: {RsoulderPos[0]}',
                        (10, 120),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (67, 246, 79), 2, cv2.LINE_AA
                        )

            cv2.putText(image, f'                       y: {RsoulderPos[1]}',
                        (10, 150),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (67, 246, 79), 2, cv2.LINE_AA
                        )

            cv2.putText(image, f'                       z: {RsoulderPos[2]}',
                        (10, 180),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (67, 246, 79), 2, cv2.LINE_AA
                        )

            # --------------------- OUTPUTTING THE POSE TO SCREEN AND FILE ---------------------#

            display_and_save_image(image=image, landmarks=results.pose_landmarks,
                                   connections=mp_pose.POSE_CONNECTIONS,
                                   frame_number=frame_counter, dir_name=output_dir_name,
                                   display_window_name=video_name,
                                   to_save=to_save
                                   )

            # region angular veolcity with known frames to mesure:

            # slap1: frames 170-207
            if slap_counter == 1:
                if frame_counter == 170:
                    start_angle = disp_angle
                elif frame_counter == 207:
                    delta_angle = float(start_angle) - float(disp_angle)
                    delta_time = (206 - 170) / 30  # frames delta/fps
                    print(f'slap{slap_counter}:\n'
                          f'time took to slap: {delta_time} s\n'
                          f'angle of slap: {delta_angle} deg\n'
                          f'angular velocity: {math.radians(delta_angle / delta_time)} rad/s \n')
                    slap_counter += 1

            # slap2: frames 280-311
            elif slap_counter == 2:
                if frame_counter == 280:
                    start_angle = disp_angle
                elif frame_counter == 311:
                    delta_angle = float(start_angle) - float(disp_angle)
                    delta_time = (311 - 280) / 30  # frames delta/fps
                    print(f'slap{slap_counter}:\n'
                          f'time took to slap: {delta_time} s\n'
                          f'angle of slap: {delta_angle} deg\n'
                          f'angular velocity: {math.radians(delta_angle / delta_time)} rad/s \n')
                    slap_counter += 1

            # slap3: frames 390-420

            elif slap_counter == 3:
                if frame_counter == 390:
                    start_angle = disp_angle
                elif frame_counter == 420:
                    delta_angle = float(start_angle) - float(disp_angle)
                    delta_time = (420 - 390) / 30  # frames delta/fps
                    print(f'slap{slap_counter}:\n'
                          f'time took to slap: {delta_time} s\n'
                          f'angle of slap: {delta_angle} deg\n'
                          f'angular velocity: {math.radians(delta_angle / delta_time)} rad/s \n')
                    slap_counter += 1

            # slap4: frames 487-511

            elif slap_counter == 4:
                if frame_counter == 487:
                    start_angle = disp_angle
                elif frame_counter == 511:
                    delta_angle = float(start_angle) - float(disp_angle)
                    delta_time = (511 - 487) / 30  # frames delta/fps
                    print(f'slap{slap_counter}:\n'
                          f'time took to slap: {delta_time} s\n'
                          f'angle of slap: {delta_angle} deg\n'
                          f'angular velocity: {math.radians(delta_angle / delta_time)} rad/s \n')
                    slap_counter += 1

            # endregion

            if cv2.waitKey(10) & 0xFF == ord('q'):
                # if 'q' button was pressed
                break

    cap.release()
    cv2.destroyAllWindows()


# endregion

if __name__ == '__main__':
    camalogo_path = r"C:\Users\40gil\Desktop\degree\year_4\sm1\final_project\CamaLogo.png"
    main(source_video_dir_path="C:\\Users\\40gil\\Desktop\\degree\\year_4\\sm1\\final_project\\PoseDetect\\videos",
         video_name="ImgainarySlap_Gilad", to_save=True)

    # region My 30fps video data:

    # slap1: frames 170-206

    # slap2: frames 280-311

    # slap3: frames 390-420

    # slap4: frames 487-511

    # endregion
