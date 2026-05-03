function F = z2(x, k)
    limit = abs(x);
    integral = romberg(0, limit, k);

    if x >= 0
        F = 0.5 + integral;
    else
        F = 0.5 - integral;
    end
end

function f = f_ts(t, c, k)
    f = c * (1 + (t ^ 2) / k) ^ (-(k + 1) / 2);
end

function I = romberg(a, b, k)
    if a == b
        I = 0;
        return;
    end

    num = my_gamma((k + 1) / 2);
    den = sqrt(k * pi) * my_gamma(k / 2);
    c = num / den;

    max_iter = 15;
    eps = 1e-8;
    R = zeros(max_iter, max_iter);
    h = b - a;

    R(1, 1) = (h / 2) * (f_ts(a, c, k) + f_ts(b, c, k));

    for i = 2 : max_iter
        h = h / 2;
        s = 0;

        for j = 1 : (2 ^ (i - 2))
            s = s + f_ts(a + (2 * j - 1) * h, c, k);
        end

        R(i, 1) = 0.5 * R(i - 1, 1) + h * s;

        for j = 2 : i
            R(i, j) = R(i, j - 1) + (R(i, j - 1) - R(i - 1, j - 1)) / (4 ^ (j - 1) - 1);
        end

        if i > 4 && abs(R(i, i) - R(i - 1, i - 1)) < eps
            I = R(i,i);
            return;
        end
    end

    I = R(max_iter, max_iter);
    warning('nie osiągnięto zbieżności w %d iteracjach', max_iter);
end

function gamm = my_gamma(z)
    if z == floor(z)
        gamm = factorial(z - 1);
    else
        gamm = sqrt(pi);
        val = z - 1;

        while val > 0
            gamm = gamm  * val;
            val = val - 1;
        end
    end
end
