import numpy as np

import cv2

def arrayreset(array):
    a = array[:, 0:len(array[0] - 2):3]
    b = array[:, 1:len(array[0] - 2):3]
    c = array[:, 2:len(array[0] - 2):3]
    a = a[:, :, None]
    b = b[:, :, None]
    c = c[:, :, None]
    m = np.concatenate((a, b, c), axis=2)
    
    return m

def init(image):

    # print(image)
    img = arrayreset(image)
   
    # array=cv2.imread("C:/Users/DELL/Desktop/aaa.png",1)

    # img=cv2.cvtColor(rgbImg,cv2.COLOR_GRAY2BGR)
    # print(img.shape)
    # print(img)
    # cv2.imshow("test",np.array(rgbImg,dtype = np.uint8))
    
    cv2.imwrite("C:/Users/DELL/Desktop/c.png",img)
    # cv2.waitKey(1000)
    
    value =img.shape[1]
    return value



