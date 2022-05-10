import math
# def egcd(a, b):
#     if a == 0:
#         return (b, 0, 1)
#     else:
#         g, y, x = egcd(b % a, a)
#         return (g, x - (b // a) * y, y)

# def modinv(a, m):
#     g, x, y = egcd(a, m)
#     if g != 1:
#         raise Exception('modular inverse does not exist')
#     else:
#         return x % m

import os


global answer_file


def fprint(string):
    answer_file.write(str(string) + '\n')


def solve(problems, image_filename):
    global answer_file
    answer_filename = image_filename[:-4] + '_ANSWER.txt'
    answer_filename = os.path.join(os.getcwd(), answer_filename)

    answer_file = open(answer_filename, 'w+')
    for i in range(11):
        globals().get('problem{0}_solve'.format(i + 1))(problems[i])
    answer_file.close()

    return answer_filename


def euq(a, b):
    q = ['-', '-']
    r = [a, b]
    s = [1, 0]
    t = [0, 1]

    A = a
    B = b
    fprint(' q[i]\tr[i]\ts[i]\tt[i]')
    ###### ?
    i = 0
    while (A != 1 and B != 1):
        if A < 1 or B < 1:
            fprint('Euclidean algorithm broke down.')
            fprint('Don\'t trust this solution from now upon.')
            break

        i = i + 1
        if A > B:
            r.append(A % B)
            q.append(A // B)
            A %= B
        else:
            r.append(B % A)
            q.append(B // A)
            B %= A

    for i in range(2, len(r)):
        s.append(s[i - 2] - q[i] * s[i - 1])
        t.append(t[i - 2] - q[i] * t[i - 1])
    for i in range(len(r)):
        fprint(' {0}\t{1}\t{2}\t{3}'.format(q[i], r[i], s[i], t[i]))
    fprint('\n  {} = {}^(-1) mod {}'.format(t[-1], r[1], r[0]))
    return t[-1]


def problem1_solve(array1):
    try:
        fprint('Task 1')
        fprint(str(array1))

        px1 = float(array1[0].split('/')[0]) / float(array1[0].split('/')[1])
        px2 = float(array1[1].split('/')[0]) / float(array1[1].split('/')[1])
        pz1 = float(array1[2].split('/')[0]) / float(array1[2].split('/')[1])
        pz2 = float(array1[3].split('/')[0]) / float(array1[3].split('/')[1])

        fprint('(a):')
        log_px1 = math.log(px1, 2)
        log_px2 = math.log(px2, 2)
        fprint('\tlog(px1) = log({0}) = {1}'.format(px1, log_px1))
        fprint('\tlog(px2) = log({0}) = {1}'.format(px2, log_px2))
        fprint('\t[ANSWER] I(x1) = -log(px1) = -log({0}) = {1}'.format(px1,
                                                                      -log_px1))
        fprint('\t[ANSWER] I(x2) = -log(px2) = -log({0}) = {1}'.format(px2,
                                                                      -log_px2))
        fprint('* log from now upon is log_2 (log base 2)')
        fprint('-'*60)

        fprint('(b):')
        fprint('\t[ANSWER] H(X) = -px1*log(px1) - px2*log(px2) = {0} + {1} = {2}'.format(
                        -log_px1*px1, -log_px2*px2, -log_px1*px1 -log_px2*px2))
        log_pz1 = math.log(pz1, 2)
        log_pz2 = math.log(pz2, 2)
        fprint('log(pz1) = log({0}) = {1}'.format(pz1, log_pz1))
        fprint('log(pz2) = log({0}) = {1}'.format(pz2, log_pz2))
        fprint('\t[ANSWER] H(Z) = -pz1*log(pz1) - pz2*log(pz2) = {0} + {1} = {2}'.format(
                        -log_pz1*pz1, -log_pz2*pz2, -log_pz1*pz1 -log_pz2*pz2))
        py1 = px1*pz1 + px2*pz2
        py2 = px1*pz2 + px2*pz1
        log_py1 = math.log(py1, 2)
        log_py2 = math.log(py2, 2)
        fprint('First, calculate y')
        fprint('py1 = px1*pz1 + px2*pz2 = {0}'.format(py1))
        fprint('py2 = px1*pz2 + px2*pz1 = {0}'.format(py2))
        fprint('log(py1) = log(px1*pz1 + px2*pz2) = {0}'.format(log_py1))
        fprint('log(py2) = log(px1*pz2 + px2*pz1) = {0}'.format(log_py2))
        fprint('\t[ANSWER] H(Y) = -py1*log(py1) - py2*log(py2) = {0} + {1} = {2}'.format(
                        -log_py1*py1, -log_py2*py2, -log_py1*py1 -log_py2*py2))
        fprint('-'*60)

        fprint('(c):')
        fprint('\t[ANSWER] 0. Because the plain text and cryptokey are'
               + ' independent.')
        fprint('H(X,Z) = H(X) - H(X|Z) = H(X) - H(X) = 0')
        fprint('-'*60)

        H_x = -(px1 * math.log(px1, 2) + px2 * math.log(px2, 2))
        H_y = -(py1 * math.log(py1, 2) + py2 * math.log(py2, 2))
        H_z = -(pz1 * math.log(pz1, 2) + pz2 * math.log(pz2, 2))

        fprint('(d):')
        fprint('I(x,y) = H(y) - H(y|x)')
        fprint('H(y|x) = - (x1*z1*log_2(z1) + x2*z2*log_2(z2) + x1*z2*log_2(z2) + x2*z1*log_2(z1))')
        H_y_cond_x = -(px1 * pz1 * math.log(pz1, 2) + px2 * pz2 * math.log(pz2, 2) + px1 * pz2 * math.log(pz2, 2) + px2 * pz1 * math.log(pz1, 2))
        fprint('H(y|x) = - ({0}*{1}*log_2({1}) + {2}*{3}*log_2({3}) + {0}*{3}*log_2({3}) + {2}*{1}*log_2({1})) = {4} '.format(array1[0], array1[2], array1[1], array1[3], H_y_cond_x))
        I_x_cond_y = H_y - H_y_cond_x
        fprint('[ANSWER] (d) mutual information text-encrypted_text {0}'.format(I_x_cond_y))
        fprint('-'*60)

        fprint('(e):')
        fprint('I(z,y) = H(y) - H(y|z)')
        fprint('H(y|z) = - (z1*x1*log_2(x1) + z2*x2*log_2(x2) + z1*x2*log_2(x2) + z2*x1*log_2(x1))')
        H_y_cond_z = -(pz1 * px1 * math.log(px1, 2) + pz2 * px2 * math.log(px2, 2) + pz1 * px2 * math.log(px2, 2) + pz2 * px1 * math.log(px1, 2))
        fprint('H(y|z) = - ({0}*{1}*log_2({1}) + {2}*{3}*log_2({3}) + {0}*{3}*log_2({3}) + {2}*{1}*log_2({1})) = {4} '.format(array1[2], array1[0], array1[3], array1[1], H_y_cond_z))
        I_z_cond_y = H_y - H_y_cond_z
        fprint('[ANSWER] (e) mutual information key-encrypted_text {0}'.format(I_z_cond_y))
        fprint('-'*60)

        fprint('(f):')
        fprint('\tThis part is for geeks, gays and adventurists.')
        fprint('-'*60)

    except TypeError as type_error:
        fprint('Your input parameters were bad.')
        fprint('For geeks: {0}'.format(str(type_error)))
    except Exception as e:
        fprint('\tTask 1 NOT solved \n')
        fprint('For geeks: {0}'.format(str(e)))


# second task: Next two elements of Linear Congruential Method
def problem2_solve(array2):
    try:
        fprint(' Task 2')
        fprint(str(array2))

        Num1 = int(array2[0])
        Num2 = int(array2[1])
        Num3 = int(array2[2])
        Mod = int(array2[3])

        fprint('sequence: {0}, {1}, {2}'.format(Num1, Num2, Num3))
        fprint('X_n+1 = A * X_n + B')

        fprint('{0} = A*{1} + B mod {2}'.format(Num2, Num1, Mod))
        fprint('{0} = A*{1} + B mod {2} \n'.format(Num3, Num2, Mod)  )

        temp1 = (Num2 - Num3) % Mod
        temp2 = (Num1 - Num2) % Mod
        fprint('intermediate calculations:')
        fprint('A = ({0} - {1}) / ({2} - {3}) mod {4}'.format(Num2, Num3, Num1, Num2, Mod)   )
        fprint('Evklid algorithm')
        fprint(' ({0} - {1})^(-1) mod {2} \n'.format(Num1, Num2, Mod))
        temp2_inverse = euq(Mod, temp2)
        A = (temp1 * temp2_inverse) % Mod
        fprint('A = {1} * {0} mod {2}'.format(temp1, temp2_inverse, Mod))

        fprint('\nB = {0} - {1} * {2} mod {3}'.format(Num2, A, Num1, Mod)    )
        B = (Num2 - A * Num1) % Mod
        fprint('\ncoefficients: A = {0}, B = {1}'.format(A, B))

        Num4 = (A*Num3 + B) % Mod
        Num5 = (A*Num4 + B) % Mod
        fprint('[ANSWER] next two elements: ... {0}, {1}'.format(Num4, Num5))

        fprint('============================================================== \n')

    except Exception, e:
        fprint('     Task 2 NOT solved \n')
        #print str(e)


# third task: Next bits of sequence
# only for m(x) = 5
def problem3_solve(array3):
    try:
        fprint(' Task 3')
        fprint(str(array3))
        fprint('bits sequence: {0}'.format(' '.join(array3)))

        bit_seq = map(int, array3)
        C0 = 1
        C5 = 1
        fprint('equation: m(x) = c5*x^5 + c4*x^4 + c3*x^3 + c2*x^2 + c1*x^1 + c0*x^0')
        fprint('c5 = 1 and c0 = 1')
        fprint('x^0 = x^5 + c4*x^4 + c3*x^3 + c2*x^2 + c1*x^1')
        fprint('system of equations:')
        for i in xrange(0, 6):
            fprint(' {0} = {1} + c4 * {2} + c3 * {3} + c2 * {4} + c1 * {5} '.format(bit_seq[i + 5], bit_seq[i], bit_seq[i + 1], bit_seq[i + 2], bit_seq[i + 3], bit_seq[i + 4])              )

        C = [[0,0,0,0], [0,0,0,1], [0,0,1,0], [0,0,1,1], [0,1,0,0], [0,1,0,1], [0,1,1,0], [0,1,1,1],
             [1,0,0,0], [1,0,0,1], [1,0,1,0], [1,0,1,1], [1,1,0,0], [1,1,0,1], [1,1,1,0], [1,1,1,1]]

        for coef in C:
            i = 0
            for i in xrange(0, 6):
                if (bit_seq[i + 5] !=  (bit_seq[i] + coef[3] * bit_seq[i + 1] + coef[2] * bit_seq[i + 2] + coef[1] * bit_seq[i + 3] + coef[0] * bit_seq[i + 4]) % 2):
                    break

            if i < 5:
                continue
            C4 = coef[3]
            C3 = coef[2]
            C2 = coef[1]
            C1 = coef[0]
            break

        fprint('coefficients: c5 = {0}, c4 = {1}, c3 = {2}, c2 = {3}, c1 = {4}, c0 = {5} \n'.format(C5, C4, C3, C2, C1, C0))

        fprint('next bit x^0 =  c5*x^5 + c4*x^4 + c3*x^3 + c2*x^2 + c1*x^1')
        next_five = []
        for i in xrange(6, 11):

            bit = (C5*bit_seq[i] + C4*bit_seq[i + 1] + C3*bit_seq[i + 2] + C2*bit_seq[i + 3] + C1*bit_seq[i + 4]) % 2
            fprint(' next {0}-th bit: {1} = {2} + {3} + {4} + {5} + {6}'.format(i + 6, bit, C5*bit_seq[i], C4*bit_seq[i + 1], C3*bit_seq[i + 2], C2*bit_seq[i + 3], C1*bit_seq[i + 4]))
            bit_seq.append(bit)
            next_five.insert(i - 6, bit)

        fprint('[ANSWER] next five bits of sequence: ... {0}'.format(' '.join(map(str, next_five))))

        fprint('============================================================== \n')
    except Exception, e:
        fprint('     Task 3 NOT solved \n')
        fprint(str(e))

# fourth task: finding a witnesses for the compositeness
def problem4_solve(array4):
    try:
        fprint(' Task 4')
        fprint(str(array4))
        Num1 = int(array4[0])
        Num2 = int(array4[1])
        Num3 = int(array4[2])
        Mod = int(array4[3])
        # ? num ** (p-1) = 1 % Mod
        s = 1
        r = (Mod - 1) / 2
        while r % 2 == 0 :
            r = r / 2
            s = s + 1

        Nums = [Num1, Num2, Num3]

        fprint('[figure] ** (p-1) = 1 mod p: ')
        fprint('figures to check: {0}'.format(' '.join(map(str, Nums))))
        fprint('testing Miller a^(p-1) != 1 or (x^2 = 1 mod p and x != +-1):')
        fprint('{0} = {1} * 2^{2}'.format(Mod - 1, r, s) )
        fprint('s = {0}, r = {1}'.format(s, r))
        fprint('everything mod p = {0}'.format(Mod))

        fprint('a^r, (a^r)^2, ... , a^(r * 2^s) = a^(p-1) \n')
        for num in Nums:

            bits = bin(r)[2:]
            fprint(' intermediate calculations:')
            fprint('  {0} = {1}'.format(r, bin(r)))
            temp = 1
            for i in bits:
                temp_print = temp
                temp = (temp ** 2 * num ** int(i)) % Mod

                fprint('  {0}^2 * {1}^{2} mod {3} = {4}'.format(temp_print, num, i, Mod, temp))



            for i in xrange(0,s + 1):
                ans = (num ** (r * 2 ** i)) % Mod
                fprint(' {0}^{1} = {2}'.format(num, r * 2 ** i, ans))
            # Miller test
	    temp_if = num ** (r * 2 ** 1) % Mod
            if (num ** (Mod-1) % Mod != 1) or ((  num ** (r * 2 ** 2) % Mod == 1) and ((  temp_if - Mod != -1) or (  temp_if % Mod == 1)) ) :
                fprint('[ANSWER] {0} is NOT witness for the compositeness of {1}'.format(num, Mod)           )
            else :
                fprint('[ANSWER] {0} is witness for the compositeness of {1} by Miller'.format(num, Mod)     )

        fprint('============================================================== \n')
    except Exception, e:
        fprint('     Task 4 NOT solved \n')
        fprint(str(e))


# fifth task: RSA decription
def problem5_solve(array5):
    try:
        fprint(' Task 5')
        fprint(str(array5))
        n = int(array5[0])
        e = int(array5[1])
        c = int(array5[2])
        fprint('public key: ({0}, {1}), c = {2} \n '.format(e, n, c))

        fprint('generating p and q : n = p*q')
        i = 2
        while i < n :
            if n % i == 0 :
                p = i
                break
            i = i + 1
        q = n / p
        fprint(' p = {0}, q = {1} \n '.format(p, q))

        fprint('F(n) = (p - 1)(q - 1)')
        F_n = (p - 1) * (q - 1)
        fprint(' F(n) = {0} \n '.format(F_n))

        fprint('d = e^(-1) mod F(n)')
        fprint('d = {0}^(-1) mod {1}'.format(e, F_n)     )
        fprint('intermediate calculations:')

        fprint('Evklid algorithm:')
        fprint(' {0}^(-1) mod {1} \n'.format(e, F_n))
        d = euq(F_n, e)

        fprint('\nprivate key: ({0}, {1}) \n '.format(d, n))

        fprint('m = c^d mod n')
        fprint('m = {0}^{1} mod {2}'.format(c, d, n))
        fprint('intermediate calculations:')
	d = d % F_n
        fprint(' {0} = {1}'.format(d, bin(d)))
        bits = bin(d)[2:]
        temp = 1
        for i in bits:
            temp_print = temp
            temp = (temp ** 2 * c ** int(i)) % n
            fprint(' {0}^2 * {1}^{2} mod {3} = {4}'.format(temp_print, c, i, n, temp)    )

        m = (c ** d) % n
        fprint('[ANSWER] decrypted message: m = {0}'.format(m))

        fprint('============================================================== \n')

    except Exception, e:
        fprint('     Task 5 NOT solved \n')
        #print str(e)


# sixth task: RSA encryption
def problem6_solve(array6):
    try:
        fprint(' Task 6')
        fprint(str(array6))
        n = int(array6[0])
        e = int(array6[1])
        m = int(array6[2])

        fprint('public key: ({0}, {1}), m = {2} \n '.format(e, n, m))
        fprint('c = m ^ e mod n')
        fprint('c = {0}^{1} mod {2}'.format(m, e, n))

        bits = bin(e)[2:]
        fprint('intermediate calculations:')
        fprint(' {0} = {1}'.format(e, bin(e)))
        temp = 1
        for i in bits:
            temp_print = temp
            temp = (temp ** 2 * m ** int(i)) % n
            fprint(' {0}^2 * {1}^{2} mod {3} = {4}'.format(temp_print, m, i, n, temp))

        c = (m ** e) % n
        fprint('[ANSWER] encrypted message: c = {0}'.format(c))

        fprint('============================================================== \n')
    except Exception, e:
        fprint('     Task 6 NOT solved \n')
        #print str(e)


# seventh task: L-gamal encryption
def problem7_solve(array7):
    try:
        fprint(' Task 7')
        fprint(str(array7))

        p = int(array7[0])
        g = int(array7[1])
        y = int(array7[2])
        x = int(array7[3])
        M = int(array7[4])
        k = int(array7[5])
        fprint('a = g^k mod p')
        fprint('a = {0}^{1} mod {2}'.format(g, k, p))

        bits = bin(k)[2:]
        fprint('intermediate calculations:')
        fprint(' {0} = {1}'.format(k, bin(k)))
        temp = 1
        for i in bits:
            temp_print = temp
            temp = (temp ** 2 * g ** int(i)) % p
            fprint(' {0}^2 * {1}^{2} mod {3} = {4}'.format(temp_print, g, i, p, temp))

        a = (g ** k) % p
        fprint('[ANSWER] a = {0} \n'.format(a))

        fprint('b = M * y^k mod p')
        fprint('b = {0} * {1}^{2} mod {3}'.format(M, y, k, p))

        fprint(' intermediate calculations:')
        fprint('  {0} = {1}'.format(k, bin(k)))
        temp = 1
        for i in bits:
            temp_print = temp
            temp = (temp ** 2 * y ** int(i)) % p
            fprint('  {0}^2 * {1}^{2} mod {3} = {4}'.format(temp_print, y, i, p, temp)   )

        fprint('b = {0} * {1} mod {2}'.format(M, temp, p))
        b = (M * y ** k) % p
        fprint('[ANSWER] b = {0}'.format(b))

        fprint('============================================================== \n')
    except Exception, e:
        fprint('     Task 7 NOT solved \n')
        #print str(e)


# eighth task: L-gamal signature
def problem8_solve(array8):
    try:
        fprint(' Task 8')
        fprint(str(array8))
        p = int(array8[0])
        g = int(array8[1])
        y = int(array8[2])
        x = int(array8[3])
        M = int(array8[4])
        k = int(array8[5])
        fprint('a = g^k mod p')
        fprint('a = {0}^{1} mod {2}'.format(g, k, p))

        bits = bin(k)[2:]
        fprint('intermediate calculations:')
        fprint(' {0} = {1}'.format(k, bin(k)))
        temp = 1
        for i in bits:
            temp_print = temp
            temp = (temp ** 2 * g ** int(i)) % p
            fprint(' {0}^2 * {1}^{2} mod {3} = {4}'.format(temp_print, g, i, p, temp))

        a = (g ** k) % p
        fprint('[ANSWER] a = {0} \n'.format(a))

        fprint('b = (M - x * a) * k^(-1) mod p-1')
        fprint('b = ({0} - {1} * {2}) * {3}^(-1) mod {4}'.format(M, x, a, k, p-1))
        fprint('intermediate calculations:')
        fprint('Evklid algorithm:')
        fprint(' {0}^(-1) mod {1} \n'.format(k, p-1))
        k_inverse = euq(p-1, k)

        b = ((M - x * a) * k ** (-1)) % (p-1)
        temp = (M - x * a) % (p-1)
        fprint('b = {1} * {0} mod {2}'.format(temp, k_inverse, p-1) )
        fprint('[ANSWER] b = {0}'.format(b))
        fprint('============================================================== \n')
    except Exception, e:
        fprint('     Task 8 NOT solved \n')
        #print str(e)


answers9 = []
# ninth task: elliptic curve - find points
def problem9_solve(array9):
    try:
        fprint(' Task 9')
        fprint(str(array9))
        a = int(array9[0])
        b = int(array9[1])
        Mod = int(array9[2])
        global answers9
        a = a % Mod
        b = b % Mod
        fprint('y^2 = x^3 + {0} * x + {1} \n'.format(a, b))
        for x in xrange(0,Mod):
            y_sqr = (x ** 3 + a * x + b) % Mod
            fprint('\n[x = {0}] y^2 = {1}'.format(x, y_sqr))

            for i in xrange(1, Mod):
                if i ** 2 % Mod == y_sqr :
                    y = i
                    fprint(' {0}^2 = {1} mod {2}'.format(y, y_sqr, Mod))
                    fprint(' [ANSWER] (x, y) = ({0}, {1}) '.format(x, y))
                    answers9.append([x, y])

        fprint('============================================================== \n')
    except Exception, e:
        fprint('     Task 9 NOT solved \n')
        #print str(e)

# tenth task: elliptic curve - is given point generator
def problem10_solve(array10):
    try:
        fprint(' Task 10')
        fprint(str(array10))
        x = int(array10[0])
        y = int(array10[1])
        a = int(array10[2])
        b = int(array10[3])
        Mod = int(array10[4])
        answers10 = []

        fprint('Given point ({0}, {1})'.format(x, y))
        fprint('Curve: y^2 = x^3 {0}x {1}, mod = {2}'.format(a, b, Mod))
        answers10.append([x, y])

        fprint('S = (3 * x^2 + a) / (2 * y) mod {0}'.format(Mod))
        fprint('intermediate calculations:')

        fprint('Evklid algorithm:')
        temp = 2 * y % Mod
        fprint(' {0}^(-1) mod {1} \n'.format(temp, Mod))
        temp_inverse = euq(Mod, temp)

        fprint('S = (3 * {0}^2 + {1}) * {2} mod {3}'.format(x, a, temp_inverse, Mod))
        S = ((3 * x ** 2  + a) * temp_inverse) % Mod
        fprint('S = {0} \n'.format(S))

        fprint('x_N = S^2 - x - x mod {0}'.format(Mod))
        fprint('x_N = {0}^2 - {1} - {1} mod {2}'.format(S, x, Mod))
        x_N = (S ** 2 - x - x) % Mod
        fprint('x_N = {0} \n'.format(x_N))

        fprint('y_N = -(y + S * (x_N - x)) mod {0}'.format(Mod))
        fprint('y_N = -({0} + {1} * ({2} - {3})) mod {4}'.format(y, S, x_N, x, Mod))
        y_N = -(y + S * (x_N - x)) % Mod
        fprint('y_N = {0}'.format(y_N))

        fprint('next point ({0}, {1}) \n'.format(x_N, y_N))
        answers10.append([x_N, y_N])


        while True or (answers9 != answers10):

            if (x_N - x != 0) :

                x_K = x_N
                y_K = y_N

                fprint('S = ({0} - {1}) / ({2} - {3}) mod {4}'.format(y_K, y, x_K, x, Mod))
                fprint('Evklid algorithm:')
                temp = x_K - x % Mod
                fprint(' {0}^(-1) mod {1} \n'.format(temp, Mod))
                temp_inverse = euq(Mod, temp)
                S = ((y_K - y) * temp_inverse) % Mod
                fprint('S = {0}'.format(S))

                fprint('x_N = {0}^2 - {1} - {2} mod {3}'.format(S, x, x_K, Mod))
                x_N = (S ** 2 - x - x_K) % Mod
                fprint('x_N = {0}'.format(x_N))

                fprint('y_N = -({0} + {1} * ({2} - {3})) mod {4}'.format(y_K, S, x_N, x_K, Mod))
                y_N = -(y_K + S * (x_N - x_K)) % Mod
                fprint('y_N = {0} '.format(y_N))

                fprint('next point ({0}, {1}) \n'.format(x_N, y_N))
                if [x_N, y_N] in answers10:
                    fprint('point ({0}, {1}) is generator of SUBGROUP: {2}'.format(x, y, answers10))
                    break
                answers10.append([x_N, y_N])
                if answers9 == answers10:
                    fprint('point ({0}, {1}) is generator of GROUP: {2}'.format(x, y, answers10))
                    break
            else:
                fprint('point ({0}, {1}) is generator of SUBGROUP: {2}'.format(x, y, answers10))
                break
        fprint('')
        fprint( answers9)

        fprint('============================================================== \n')

    except Exception, e:
        fprint('     Task 10 NOT solved \n')
        fprint( str(e)        )


# eleventh task: elliptic curve - find signature
def problem11_solve(array11):
    try:
        fprint(' Task 11')
        fprint('{0}\n'.format(str(array11)))
        m = int(array11[0])
        a = int(array11[1])
        b = int(array11[2])
        mod = int(array11[3])
        x_G = int(array11[4])
        y_G = int(array11[5])
        size = int(array11[6])
        x_Q = int(array11[7])
        y_Q = int(array11[8])
        k = int(array11[9])

        fprint('S = (3 * x^2 + a) / (2 * y) mod {0}'.format(mod))
        fprint('S = (3 * {0}^2 + {1}) / (2 * {2}) mod {3}\n'.format(x_G, a, y_G, mod))
        fprint('Euclidean algorithm:')
        denom = 2 * y_G % mod  # denominator of S
        fprint(' {0}^(-1) mod {1}:'.format(denom, mod))
        denom_inverse = euq(mod, denom)
        S = ((3 * x_G ** 2  + a) * denom_inverse) % mod
        fprint('S = {0}'.format(S))

        fprint('x_C = S^2 - x_G - x_G mod {0}'.format(mod))
        fprint('x_C = {0}^2 - {1} - {1} mod {2}'.format(S, x_G, mod))
        x_C = (S ** 2 - x_G - x_G) % mod
        fprint('x_C = {0} \n'.format(x_C))

        fprint('y_C = -(y_G + S * (x_C - x_G)) mod {0}'.format(mod))
        fprint('y_C = -({0} + {1} * ({2} - {3})) mod {4}'.format(y_G, S, x_C, x_G, mod))
        y_C = -(y_G + S * (x_C - x_G)) % mod
        fprint('y_C = {0}'.format(y_C))
        fprint('C({0}, {1})\n'.format(x_C, y_C))

        # Point d*G
        x_D_prev = x_C
        y_D_prev = y_C
        d = k
        MAX_CYCLE_COUNT = 10
        while (x_D_prev !=  x_Q) or (y_D_prev != y_Q):
            d += 1
            fprint('d = {0}'.format(d))
            if d > MAX_CYCLE_COUNT:
                fprint('Points d*G and Q have irreversibly diverged.')
                raise Exception('Reason: Too many cycles')
                break

            if x_D_prev != x_G or y_D_prev != y_G:
                fprint('S = (y_G - y_D_prev) / (x_G - x_D_prev) = {0}'
                       + ' / {1}'.format(y_G - y_D_prev, x_G - x_D_prev))
                denom = (x_G - x_D_prev) % mod  # denominator of S
                fprint('\t{0}^(-1) mod {1}:'.format(denom, mod))
                denom_inverse = euq(mod, denom)
                S = ((y_G - y_D_prev) * denom_inverse) % mod
                fprint('S = {0}'.format(S))
            else:
                fprint('S = (3 * {0}^2 + {1}) / (2 * {2}) mod {3}\n'.format(x_G, a, y_G, mod))
                denom = 2 * y_G % mod  # denominator of S
                fprint(' {0}^(-1) mod {1}:'.format(denom, mod))
                denom_inverse = euq(mod, denom)
                S = ((3 * x_G ** 2  + a) * denom_inverse) % mod
                fprint('S = {0}'.format(S))

            x_D = (S**2 - x_D_prev - x_G) % mod
            fprint('x_D = S^2 - x_D_prev - x_G = {0}^2 - {1} - {2} = {3}'.format(S,
                                                            x_D_prev, x_G, x_D))
            y_D = (-y_G - S*(x_D - x_G)) % mod
            # y_D = (-(y_G + S*(x_D_prev - x_G))) % mod
            fprint('y_D = -(y_G + S*(x_D_prev - x_G)) = -({0} + {1}*({2} - {3})) = {4}'.format(
                                                    y_G, S, x_D_prev, x_G, y_D))
            x_D_prev = x_D
            y_D_prev = y_D
            fprint('-'*11)

        fprint('(Q = {0}*G)\n'.format(d) )
        signature = (x_C * d + k * m) % size
        fprint('signature = (x_C * d + k * m) mod n = ({0} * {1} + {2} * {3})'
               + ' mod {4} = {5}'.format(x_C, d, k, m, size, signature))
        fprint('[ANSWER] e-sign = (x_C, sign) = ({0}, {1})'.format(x_C, signature))

    except Exception, e:
        fprint('     Task 11 NOT solved \n')
        fprint( str(e))

    fprint('{0}\n'.format('='*60))


# if __name__ == '__main__':
#     global answer_file
#     answer_file = open('ANSWER.txt', 'w+')
#     # problem11_solve(['5', '-2', '-9', '11', '4', '5', '15', '3', '1', '2'])
#     problem11_solve(['5', '-2', '-9', '11', '7', '1', '15', '10', '5', '2'])
#     answer_file.close()
# #     problems = [['1/5', '4/5', '1/5', '4/5'], ['371', '455', '137', '499'], ['0', '0', '1', '1', '0', '0', '0', '0', '1', '0', '1'], ['17', '68', '88', '145'], ['77', '37', '39'], ['55', '13', '29'], ['11', '8', '10', '5', '3', '0'], ['11', '6', '9', '4', '7', '3'], ['-2', '-9', '11'], ['1', '1', '-2', '-9', '11'], ['5', '-2', '-9', '11', '4', '5', '15', '3', '1', '2']]
