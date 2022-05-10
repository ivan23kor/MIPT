import cv2 as cv
import numpy as np
import os
from matplotlib import pyplot as plt


def improve(image_filename):
    img = cv.imread(image_filename,0)
    # img = cv.cvtColor(img, cv.COLOR_BGRA2BGR)
    img = cv.bilateralFilter(img,11,11,3)
    ret,threshold = cv.threshold(img,240,255,cv.THRESH_TOZERO)

    cv.imwrite(image_filename, threshold)


def preprocess(image_filename):
    if image_filename[-3:] == 'pdf':
        os.system('pdftoppm {0} {1} -jpeg'.format(image_filename,
                                                  image_filename[:-4]))
        image_filename = image_filename[:-3] + 'jpeg'
        os.system('mv {0} {1}'.format(image_filename[:-5] + '-1.jpg',
                                      image_filename))

    # improve(image_filename)
