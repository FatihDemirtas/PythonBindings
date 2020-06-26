import cv2

def ImShow():
    image = cv2.imread("C:/FalconStorage/Magnitude1/25.png")
    print('imshow() function is called!')
    # cv2.imshow("Frame25", image)
    # cv2.waitKey(0)

def tempFunc():
    print('TempFunc() function is called from another script!')


def getRectangle():
    image = cv2.imread("C:/FalconStorage/Magnitude1/25.png")
    roi = cv2.selectROI(image)
    return roi