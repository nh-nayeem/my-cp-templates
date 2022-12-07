struct GCD_type {ll x, y, g; };
GCD_type ex_GCD(ll a, ll b)
{
    ll x = 1, xx = 0, y = 0, yy = 1;
    while (b) {
        ll q = a / b;
        ll t = b; b = a % b, a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    return {x, y, a};
}
int modinv(int a, int m) {
    return (ex_GCD(a, m).x % m + m) % m;
}
pair<int, int> crt(pair<int, int> u, pair<int, int> v) {
    // res = u.ff, lcm = u.ss, r[i] = v.ff , p[i] = v.ss, d = g;
    auto z = ex_GCD(u.ss, v.ss);
    ll x1 = z.x, g = z.g;
    assert((v.ff - u.ff) % g == 0);
    u.ff = (u.ff + x1 * (v.ff - u.ff) / g % (v.ss / g) * u.ss);
    u.ss = u.ss / g * v.ss;
    u.ff = (u.ff % u.ss + u.ss) % u.ss;
    return u;
}
