def cubic(x, differentiate=False):
    if not differentiate:
        return x**3 - 4 * x - 9
    else:
        return 3 * x**2 - 4
