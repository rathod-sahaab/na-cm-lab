function root = base_rooter (@intermediate_calculation_function, @func, x1, x2, n_digit_precision)
    precision = 10 ^ (-n_digit_precision)

    if xor((function(x1) < 0), (function(x2) < 0)):
    # same as function(x1)*function(x2) < 0, but faster
        error = sprintf('No roots in the interval (%f, %f)', x1, x2)
        disp(error)
        root = false
        return
    endif

    fx1 = func(x1)
    while true
        x = intermidiate_calculation_function(x1, x2)

        fx = func(x)
        # print(fx)
        if math.fabs(fx) < precision:
            return x

        if bool(fx < 0) ^ bool(fx1 < 0):  # fx * fx1 < 0, but less expensive
            x2 = x
        else:
            x1 = x
            fx1 = fx
endfunction


