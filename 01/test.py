import subprocess
def check(expr,result):
    out=subprocess.run(["./calc",expr],stdout=subprocess.PIPE)
    if out.stdout.decode('ascii')!=result:
        print('error {0} != {1}, got {2}'.format(expr,result,out.stdout.decode('ascii')))
check('2+2','4')
check('w','Bad input')
check('2+','Bad input')
max_int='214748364'
check(max_int+'7',max_int+'7')
check(max_int+'8','Overflow')
check('-'+max_int+'8','-'+max_int+'8')
check('-'+max_int+'9','Overflow')
check('-'+max_int+'8'+'+'+max_int+'7','-1')
check(max_int+'7'+'+'+max_int+'7','-2') # Переполнение, нам сказали использовать для вычислений int, так что словить
                                        # переполнение сложно
check('1-1--1--1','2')
check('--5','Bad input')
check('5*5*5*5*5*5*5/5/5/5/5/5','25')
check('1+1*2 +1*2*2 +1*2*2*2 + 1*2*2*2*2 +1*2*2*2*2*2 + 1*2*2*2*2*2*2 + 1*2*2*2*2*2*2*2','255')
check('+','Bad input')
check('         2 +      2              *              9               -                 -1  ','21')
check('2++2','Bad input')
check('2---2','Bad input')
check('5**2','Bad input')
check('2+2+','Bad input')
check('             5    ','5')
check('','Bad input')
check('1+1-1+1+a+1-1','Bad input')
check('1+0+0+0*0+190000*0','1')
check('5+6*5/5*0','5')
check('4+3/0','Division by zero')
