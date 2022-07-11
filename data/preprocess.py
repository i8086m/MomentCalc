import cv2
import numpy as np
import sys


def bgr2gray(img: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def main():
    args = sys.argv[1:]

    if len(args) == 3:
        file_name = args[0]
        save_name = args[1]
        mode = args[2]

        img = bgr2gray(cv2.imread(file_name))
        size_y, size_x = img.shape

        if mode == 'bytes':
            with open(save_name, 'wb') as file:
                file.write(img.tobytes())
        elif mode == 'numbers':
            with open(save_name, 'w') as file:
                for y in range(size_y):
                    file.write(' '.join([str(img[y, x]) for x in range(size_x)]) + '\n')
        else:
            print('Invalid mode')

        print('{} ok'.format(save_name))

    else:
        print('Invalid args')


if __name__ == '__main__':
    main()
