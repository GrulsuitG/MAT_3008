import numpy as np

def main():
    #array initialize
    x_mat = np.array([[.0, .0, .0],
                      [.0, .0, .0],
                      [.0, .0, .0]])
    y_mat = np.array([[.0, .0, .0],
                      [.0, .0, .0],
                      [.0, .0, .0]])
    ax = np.array([.0, .0, .0])
    ay = np.array([.0, .0, .0])

    for i in range(1, 4):
        filename = "fitdata" + str(i) + ".dat"
        f = open(filename, 'r')
        lines = f.readlines()
        for l in lines :
            # solve
            # (x^2 x^2 x) (a1)   (xx')
            # (x^2 x^2 x) (a2) = (xx')
            # (x   x   1) (a3)   (x')
            num = l.split();
            x = float(num[0])
            y = float(num[1])
            x2 = x*x
            y2 = y*y
            xp = float(num[2])
            yp = float(num[3])
            xxp = x*xp
            yyp = y*yp
            x_mat_temp = np.array( [[x2, x2, x],
                                    [x2, x2, x],
                                    [x, x, 1]]) 
            y_mat_temp = np.array( [[y2, y2, y],
                                    [y2, y2, y],
                                    [y, y, 1]]) 
            ax_t = np.array([xxp, xxp, xp])
            ay_t = np.array([yyp, yyp, yp])
            ax += ax_t
            ay += ay_t
            x_mat += x_mat_temp
            y_mat += y_mat_temp
            
        u, s, vh = np.linalg.svd(x_mat)
        s = np.array([1/s[0], 1/s[1], 1/s[2]])
        s = np.diag(s)
        x_i = np.dot(vh.T , np.dot(s, u.T))
        a1 = np.dot(x_i, ax)
        
        u, s, vh = np.linalg.svd(y_mat)
        s = np.array([1/s[0], 1/s[1], 1/s[2]])
        s = np.diag(s)
        y_i = np.dot(vh.T , np.dot(s, u.T))
        a2 = np.dot(y_i, ay)
        
        ans = np.concatenate((a1,a2)) 
        print("solution of", filename)
        
        print("a1:", ans[0])
        print("a2:", ans[1])
        print("a3:", ans[2])
        print("a4:", ans[3])
        print("a5:", ans[4])
        print("a6:", ans[5])

        print()


if __name__ == "__main__":
    main()

