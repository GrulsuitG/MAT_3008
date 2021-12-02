import numpy as np

def func_x(x, y, a):
    return numerator_x(x,y,a)/denominator(x,y,a)

def func_y(x,y,a):
    return numerator_y(x,y,a)/denominator(x,y,a)

def numerator_x(x,y,a):
    return a[0][0]*x+a[0][1]*y+a[0][2]

def numerator_y(x,y,a):
    return a[1][0]*x+a[1][1]*y+a[1][2]

def denominator(x,y,a):
    return a[2][0]*x+a[2][1]*y+1

def main():
    for i in range(1, 4):
        filename = "fitdata" + str(i) + ".dat"
        f = open(filename, 'r')
        lines = f.readlines()
        x_arr = np.array([])
        y_arr = np.array([])
        xp_arr = np.array([])
        yp_arr = np.array([])
        for l in lines :
            num = l.split();
            x = float(num[0])
            y = float(num[1])
            xp = float(num[2])
            yp = float(num[3])
        
            x_arr = np.append(x_arr, x)
            y_arr = np.append(y_arr, y)
            xp_arr = np.append(xp_arr, xp)
            yp_arr = np.append(yp_arr, yp)

        
        a_cur = np.random.randn(3,3)
        a_cur[2][2] = .0
        chi_x,chi_y = chi_square(x_arr, y_arr, xp_arr, yp_arr, a_cur)
        lamdax = 0.001
        lamday = 0.001
        while True:
            g_x, g_y, h_x, h_y = get_gradient_hessian(x_arr, y_arr, xp_arr, yp_arr, a_cur)
            mh_x = h_x + np.eye(5,5)*lamdax
            
            while True:
                if np.linalg.det(mh_x) != 0:
                    mh_x_inv = np.linalg.inv(mh_x)
                    break
                else :
                    mh_x += 0.01

            mh_y = h_y + np.eye(5,5)*lamday
            while True:
                if np.linalg.det(mh_y) != 0:
                    mh_y_inv = np.linalg.inv(mh_y)
                    break
                else :
                    mh_y += 0.01
            da_x = np.dot(mh_x_inv,g_x.T)
            da_y = np.dot(mh_y_inv,g_y.T)
            
            da = np.array([ [da_x[0],da_x[1],da_x[2]],
                            [da_y[0],da_y[1],da_y[2]],
                            [(da_x[3]+da_y[3])/2, (da_x[4]+da_y[4])/2, 0]])
            m = da.mean()
            if abs(m) < 0.001 :
                break;

            a_next = da + a_cur

            next_chi_x, next_chi_y = chi_square(x_arr, y_arr, xp_arr, yp_arr, a_next)
            if next_chi_x >= chi_x:
                lamdax *= 10
            else :
                lamdax /= 10
            if next_chi_y >= chi_y:
                lamday *= 10
            else :
                lamday /= 10

            a_cur = a_next

        print_sol(a_cur, i)

def print_sol(a, i):
    print("solution", i)

    print("a11 :", a[0][0])
    print("a12 :", a[0][1])
    print("a13 :", a[0][2])
    print("a21 :", a[1][0])
    print("a22 :", a[1][1])
    print("a23 :", a[1][2])
    print("a31 :", a[2][0])
    print("a32 :", a[2][1])

    print()
    

def chi_square(x_arr,y_arr,xp_arr,yp_arr,a):
    
    length = len(x_arr)
    chi_x = .0
    chi_y = .0
    for i in range(length):
        x = x_arr[i]
        y = y_arr[i]
        xp = xp_arr[i]
        yp = yp_arr[i]

        fx = func_x(x,y,a)
        e_x = xp - fx

        fy = func_y(x,y,a)
        e_y = yp - fy

        chi_x += e_x*e_x
        chi_y += e_y*e_y

    return chi_x, chi_y

def get_gradient_hessian(x_arr, y_arr, xp_arr, yp_arr, a):
    length = len(x_arr)
    gradient_x = np.zeros(5)
    gradient_y = np.zeros(5)
    hessian_x = np.full((5,5), .0)
    hessian_y = np.full((5,5), .0)
    for i in range(length):
        x = x_arr[i]
        y = y_arr[i]
        xp = xp_arr[i]
        yp = yp_arr[i]

        fx = func_x(x,y,a)
        e_x = xp - fx
        
        fy = func_y(x,y,a)
        e_y = yp - fy

        deno = denominator(x,y,a)
        
        dfda11 = x/deno
        dfda12 = y/deno
        dfda13 = 1/deno

        dfda21 = dfda11
        dfda22 = dfda12
        dfda23 = dfda13

        dfda21 = dfda11
        dfda22 = dfda12
        dfda23 = dfda13
        
        dfxda31 = -x*fx/deno
        dfxda32 = -y*fx/deno
        dfyda31 = -x*fy/deno
        dfyda32 = -y*fy/deno

        
        tmp_gradient_x = np.array([e_x*dfda11, e_x*dfda12, e_x*a[0][2]/deno, e_x*dfxda31, e_x*dfxda32])

        tmp_gradient_y = np.array([e_y*dfda21, e_y*dfda22, e_y*a[0][2]/deno, e_y*dfyda31, e_y*dfyda32])

        tmp_hessian_x = np.array([[dfda11*dfda11, dfda11*dfda12, dfda11*dfda13, dfda11*dfxda31, dfda11*dfxda32],
                                [dfda12*dfda11, dfda12*dfda12, dfda12*dfda13, dfda12*dfxda31, dfda12*dfxda32],
                                [dfda13*dfda11, dfda13*dfda12, dfda13*dfda13, dfda13*dfxda31, dfda13*dfxda32],
                                [dfxda31*dfda11, dfxda31*dfda12, dfxda31*dfda13, dfxda31*dfxda31, dfxda31*dfxda32],
                                [dfxda32*dfda11, dfxda32*dfda12, dfxda32*dfda13, dfxda32*dfxda31, dfxda32*dfxda32]])

        tmp_hessian_y = np.array([[dfda21*dfda21, dfda21*dfda22, dfda21*dfda23, dfda21*dfyda31, dfda21*dfyda32],
                                [dfda22*dfda21, dfda22*dfda22, dfda22*dfda23, dfda22*dfyda31, dfda22*dfyda32],
                                [dfda23*dfda21, dfda23*dfda22, dfda23*dfda23, dfda23*dfyda31, dfda23*dfyda32],
                                [dfyda31*dfda21, dfyda31*dfda22, dfyda31*dfda23, dfyda31*dfyda31, dfyda31*dfyda32],
                                [dfyda32*dfda21, dfyda32*dfda22, dfyda32*dfda23, dfyda32*dfyda31, dfyda32*dfyda32]])
        gradient_x += -2 * tmp_gradient_x
        gradient_y += -2 * tmp_gradient_y

        hessian_x += tmp_hessian_x
        hessian_y += tmp_hessian_y
    

    return gradient_x, gradient_y, hessian_x, hessian_y
       
     

if __name__ == "__main__":
    main()

