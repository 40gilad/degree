import pandas as pd
import os
import numpy as np
from pathlib import Path
from datetime import datetime


# region Mediapipe
import mediapipe as mp
import cv2

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(max_num_hands=1, min_detection_confidence=0.8)


def crop_images(path=None, size=(128, 128)):
    # Create the new directory path
    if path is None:
        new_dir = Path(
            r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\cropped_' +
            str(size)
            .replace('(', '')
            .replace(',', 'X')
            .replace(' ', '') + datetime.now().strftime("%H_%M_%S")
        )
    else:
        new_dir = Path(path)

    # Create the new directory if it doesn't exist
    new_dir.mkdir(parents=True, exist_ok=True)

    # Path to the original images directory
    original_images_dir = Path(r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\pre_cropped_images')

    # Loop through all directories in the original images directory
    for dir_name in os.listdir(original_images_dir):
        if dir_name == 'asl_alphabet_test':
            for img_name in os.listdir(original_images_dir / dir_name):
                print(f'-{img_name}')
                img_path = original_images_dir /dir_name / img_name

                this_path=new_dir / dir_name
                this_path.mkdir(parents=True, exist_ok=True)

                # Load and crop the image
                img = cv2.imread(str(img_path))
                if img is not None:
                    cropped_img = cut_image(img, size)

                    # Save the cropped image to the new location
                    new_img_path = this_path / img_name
                    cv2.imwrite(str(new_img_path), cropped_img)
            continue
        #else: continue
        print(f'--------------{dir_name}')
        dir_path = original_images_dir / dir_name
        if os.path.isdir(dir_path):
            new_subdir = new_dir / dir_name
            new_subdir.mkdir(parents=True, exist_ok=True)

            # Loop through all subdirectories in the current directory
            for subdir_name in os.listdir(dir_path):
                print(f'------{subdir_name}')
                subdir_path = dir_path / subdir_name
                if os.path.isdir(subdir_path):
                    new_subsubdir = new_subdir / subdir_name
                    new_subsubdir.mkdir(parents=True, exist_ok=True)

                    # Loop through all images in the current subdirectory
                    for img_name in os.listdir(subdir_path):
                        print(f'-{img_name}')
                        img_path = subdir_path / img_name

                        # Load and crop the image
                        img = cv2.imread(str(img_path))
                        if img is not None:
                            cropped_img = cut_image(img, size)

                            # Save the cropped image to the new location
                            new_img_path = new_subsubdir / img_name
                            cv2.imwrite(str(new_img_path), cropped_img)


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


# endregion


def create_train_meta_data():
    df = pd.DataFrame()
    images_list = []
    labels_list = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\cropped_128X128)18_57_14\asl_alphabet_train'
    class_encoding = {}
    weights = []
    lable_class_encoding = []
    class_counter = 0
    for dir in os.listdir(images_dir):
        if len(dir) > 1:
            continue
        class_encoding[dir] = class_counter
        class_counter += 1
        for img in os.listdir(os.path.join(images_dir, dir)):
            images_list.append(os.path.join(images_dir, dir, img))
            labels_list.append(dir)
            lable_class_encoding.append(class_encoding[dir])
            weights.append(1)
    df["filename"] = images_list
    df["label"] = labels_list
    df['class_encoding'] = lable_class_encoding
    df['weights'] = weights

    # ----------- df2 ---------------#
    df2 = pd.DataFrame()
    images_list = []
    labels_list = []
    weights = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\cropped_128X128)18_57_14\arabic_to_english'
    lable_class_encoding = []
    for dir in os.listdir(images_dir):
        if len(dir) > 1:
            continue
        for img in os.listdir(os.path.join(images_dir, dir)):
            images_list.append(os.path.join(images_dir, dir, img))
            labels_list.append(dir)
            lable_class_encoding.append(class_encoding[dir])
            weights.append(10)
    df2["filename"] = images_list
    df2["label"] = labels_list
    df2['class_encoding'] = lable_class_encoding
    df2['weights'] = weights

    final_df = pd.concat([df, df2], ignore_index=True)
    final_df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)
    # df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)
    return class_encoding


def create_test_meta_data(class_encoding):
    df = pd.DataFrame()
    images_list = []
    labels_list = []
    lable_class_encoding = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\cropped_128X128)18_57_14\asl_alphabet_test'
    for img in os.listdir(images_dir):
        cur_label = img.split('_')[0]
        if len(cur_label) > 1:
            continue
        images_list.append(os.path.join(images_dir, img))
        labels_list.append(cur_label)
        lable_class_encoding.append(class_encoding[cur_label])

    df["filename"] = images_list
    df["label"] = labels_list
    df['class_encoding'] = lable_class_encoding

    df2 = pd.DataFrame()
    images_list = []
    labels_list = []
    lable_class_encoding = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\cropped_128X128)18_57_14\hebrew_to_english'
    for dir in os.listdir(images_dir):
        if len(dir) > 1:
            continue
        for img in os.listdir(os.path.join(images_dir, dir)):
            cur_label = img[0]
            images_list.append(os.path.join(images_dir, dir, img))
            labels_list.append(cur_label)
            lable_class_encoding.append(class_encoding[cur_label])

    df2["filename"] = images_list
    df2["label"] = labels_list
    df2['class_encoding'] = lable_class_encoding

    final_df = pd.concat([df, df2], ignore_index=True)
    final_df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)
    # df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)


def create_test_meta_data_2(class_encoding):
    df = pd.DataFrame()
    images_list = []
    labels_list = []
    lable_class_encoding = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\arabic_to_english'
    for dir in os.listdir(images_dir):
        for img in os.listdir(os.path.join(images_dir, dir)):
            cur_label = dir
            if len(cur_label) > 1:
                continue
            images_list.append(os.path.join(dir, img))
            labels_list.append(cur_label)
            lable_class_encoding.append(class_encoding[cur_label])

    df["filename"] = images_list
    df["label"] = labels_list
    df['class_encoding'] = lable_class_encoding
    df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)


if __name__ == '__main__':
    #crop_images()
    class_encoding = create_train_meta_data()
    create_test_meta_data(class_encoding)
    create_test_meta_data_2(class_encoding)
