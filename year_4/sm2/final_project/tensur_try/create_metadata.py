import pandas as pd
import os


def create_train_meta_data():
    df = pd.DataFrame()
    images_list = []
    labels_list = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\asl_alphabet_train\asl_alphabet_train'
    class_encoding = {}
    lable_class_encoding = []
    class_counter = 0
    for dir in os.listdir(images_dir):
        if len(dir) > 1:
            continue
        class_encoding[dir] = class_counter
        class_counter += 1
        for img in os.listdir(os.path.join(images_dir, dir)):
            images_list.append(os.path.join(dir, img))
            labels_list.append(dir)
            lable_class_encoding.append(class_encoding[dir])
    df["filename"] = images_list
    df["label"] = labels_list
    df['class_encoding']=lable_class_encoding
    df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)
    return class_encoding


def create_test_meta_data(class_encoding):
    df = pd.DataFrame()
    images_list = []
    labels_list = []
    lable_class_encoding = []
    images_dir = r'C:\Users\40gil\Desktop\degree\year_4\sm2\final_project\asl_alphabet_test\asl_alphabet_test'
    for img in os.listdir(images_dir):
        cur_label = img.split('_')[0]
        if len(cur_label) > 1:
            continue
        images_list.append(img)
        labels_list.append(cur_label)
        lable_class_encoding.append(class_encoding[cur_label])

    df["filename"] = images_list
    df["label"] = labels_list
    df['class_encoding']=lable_class_encoding
    df.to_csv(os.path.join(images_dir, 'metadata.csv'), index=False)


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
    class_encoding=create_train_meta_data()
    # create_test_meta_data(class_encoding)
    create_test_meta_data_2(class_encoding)
