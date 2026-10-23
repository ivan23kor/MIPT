import cv2 as cv
import numpy as np
from pathlib import Path
import subprocess
from matplotlib import pyplot as plt


def improve(image_filename):
    img = cv.imread(image_filename,0)
    # img = cv.cvtColor(img, cv.COLOR_BGRA2BGR)
    img = cv.bilateralFilter(img,11,11,3)
    ret,threshold = cv.threshold(img,240,255,cv.THRESH_TOZERO)

    cv.imwrite(image_filename, threshold)


def preprocess(image_filename):
    if image_filename[-3:] == 'pdf':
        source = Path(image_filename).resolve()
        prefix = source.with_suffix('')
        subprocess.run(
            ['pdftoppm', '-f', '1', '-singlefile', '-jpeg', str(source), str(prefix)],
            check=True,
        )
        Path(str(prefix) + '.jpg').replace(source.with_suffix('.jpeg'))

    # improve(image_filename)
