import math


def newton_raphson(function, initial_guess, n_digit_precision=6):
    """
    Finds the root of the equation using newton raphson method,
    function should have second parameter 'differentiate' which, when set to True,
    return value of function'(x) i.e. differentiated value of x
    This way the person who writes/edits the function can easily verify the
    differential of that fucntion.
    """

    x = initial_guess
    precision = 0.5 * 10**(-n_digit_precision)

    stage = 1
    while True:
        xprev = x
        x = (x - (function(x) / function(x, differentiate=True)))

        print("x{} = {}".format(stage, round(x, n_digit_precision)))
        stage += 1

        if math.fabs(x-xprev) < precision:
            return x


def bisection(function, x1, x2, n_digit_precision=6):
    """
    Find root of a function dependent on one variable. (Bisection method)
    """
    def bisection_intermidiate(x1, x2):
        return (x1 + x2) / 2

    return base_rooter(bisection_intermidiate, function, x1, x2,
                       n_digit_precision)


def regular_falsi(function, x1, x2, n_digit_precision=6):
    """
    Find root of a function dependent on one variable. (Regular Falsi method)
    """
    def regular_falsi_intermidiate(x1, x2):
        return x2 - (function(x2) * (x2 - x1)) / (function(x2) - function(x1))

    return base_rooter(regular_falsi_intermidiate, function, x1, x2,
                       n_digit_precision)


def base_rooter(intermidiate_calculation_function, function, x1, x2,
                n_digit_precision):
    """
    Find root of a function dependent on one variable. (General)
    """
    precision = 0.5 * 10**(-n_digit_precision)

    if not bool(function(x1) < 0) ^ bool(function(x2) < 0):
        # same as function(x1)*function(x2) >0
        print('No roots in the interval ({}, {})'.format(x1, x2))
        return False

    fx1 = function(x1)
    stage = 0
    while True:
        x = intermidiate_calculation_function(x1, x2)
        print("x{} = {}".format(stage, x))
        stage += 1

        fx = function(x)
        # print(fx)
        if math.fabs(fx) < precision:
            return x

        if bool(fx < 0) ^ bool(fx1 < 0):  # fx * fx1 < 0, but less expensive
            x2 = x
        else:
            x1 = x
            fx1 = fx
