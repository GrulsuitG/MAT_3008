import cv2
import numpy as np
#import matplotlib.pyplot as plt
# Bi-Linear interpolation


def bilinear(img, M, N, ax, ay):
    
    # get position of resized image
    y = np.arange(N).repeat(M).reshape(N, -1)
    x = np.tile(np.arange(M), (N, 1))
    # get position of original position
    y = (y / ay)
    x = (x / ax)
    ix = np.floor(x).astype(int)
    iy = np.floor(y).astype(int)
    ix = np.minimum(ix, int(M/ax)-2)
    iy = np.minimum(iy, int(N/ay)-2)
    # get distance
    dx = x - ix
    dy = y - iy
    dx = np.repeat(np.expand_dims(dx, axis=-1), 3, axis=-1)
    dy = np.repeat(np.expand_dims(dy, axis=-1), 3, axis=-1)
    # interpolation

    out = (1-dx) * (1-dy) * img[iy, ix] + dx * (1 - dy) * img[iy, ix+1] + (1 - dx) * dy * img[iy+1, ix] + dx * dy * img[iy+1, ix+1]
    out = np.clip(out, 0, 255)
    out = out.astype(np.uint8)
    return out

# Read image

def main():
    img = cv2.imread("test.jpg").astype(float)
    h, w, c = img.shape
    
    # Bilinear interpolation
    while True :
        M = int(input("input the width : "))
        N = int(input("input the height : "))
        
        if (M < w) or (N < h) :
            
            print("input bigger number than current input")
            print("image width : " + str(w))
            print("image height : " + str(h))
            
        else :
            break
        
    
    out = bilinear(img, M, N, float(M/w), float(N/h))

    # Save result
    cv2.imwrite("out.jpg", out)

if __name__ == "__main__":
    main()
