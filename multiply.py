import cv2
import pythonTest
import logging
import time

def multiply(a,b):
    print("Multiply() is called from Python!")
    c = a*b

    print("Result from Python is :  ", c)
    return c

def add(a,b):
    print("Add() is called from Python!")
    c = a + b

    print("Result from Python is :  ", c)
    return c

def imshow():
    startTime = time.time()
    print("Imshow() is called from Python!")
    image = cv2.imread("C:/FalconStorage/Magnitude1/25.png", cv2.IMREAD_GRAYSCALE)
    # cv2.imshow("magnitude", image)
    # cv2.waitKey(0)
    

    mask1 = cv2.adaptiveThreshold(image, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 9, 3)
    mask2 = cv2.adaptiveThreshold(255-image, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 9, 3)
    motion = cv2.bitwise_or(mask1, mask2)
    contours, _ = cv2.findContours(motion, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # cv2.imshow("Motion", motion)
    # cv2.waitKey(0)
    rows, cols = image.shape
    byteArray = bytearray(image)
    
    elapsed = time.time() - startTime
    print('(Python) Adaptive threshold elapsed = ', int(round(elapsed*1000)))
    return rows, cols, byteArray

def callFromAnotherScript():
    print("CallFromAnotherScript() is called from Python!")
    roi = pythonTest.getRectangle()
    print("ROI: " , roi[0], roi[1], roi[2], roi[3])
    return roi[0], roi[1], roi[2], roi[3]

imshow()