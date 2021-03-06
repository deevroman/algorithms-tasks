// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#ifdef LOCAL
    #define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <iomanip>
#include <cassert>
#include <random>
#include <numeric>
using namespace std;

// #define debug(x) std::cout << #x << ": " << x << endl;
template<class TH> void _dbg(const char *sdbg, TH h) { cerr << sdbg << '=' << h << endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
    while (*sdbg != ',') cerr << *sdbg++;
    cerr << '=' << h << ','; _dbg(sdbg+1, a...);
}
#ifdef LOCAL
    #define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
    #define debug(...)
#endif

#define EXIT return 0;
#define pb push_back
#define sip setprecision(10) << fixed
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vint;

const int INF = (int)1e9 + 1;
const ll LINF = (ll)1e18 + 1;

template <typename T1, typename T2>
std::istream& operator>>(std::istream &in, pair<T1, T2> &oth) {
       in >> oth.first >> oth.second;
       return in;
}
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, const pair<T1, T2> &oth) {
    out << oth.first << ' ' << oth.second;
    return out;
}

template <typename T>
std::istream& operator>>(std::istream &in, std::vector<T> &v) {
    for (auto &now : v)
        in >> now;
    return in;
}
template <typename T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &v) {
    for (auto &now : v)
        out << now << ' ';
    out << "\n";
    return out;
}
template <typename T>
std::ostream& operator<<(std::ostream &out, const std::set<T> &v) {
    for (auto &now : v)
        out << now << ' ';
    out << "\n";
    return out;
}

void get_time() {
    cout << 1. * clock()/CLOCKS_PER_SEC    << endl;
}

template<typename T>
T Myceil(T a, T b) {
    return (a+b-1)/b;
}

template<typename T1, typename T2>
T1 max(T1 a, T2 b) {
    return a > b ? a : b;
}

template<typename T1, typename T2>
T1 min(T1 a, T2 b) {
    return a < b ? a : b;
}

template<typename T1, typename T2>
T1 gcd(T1 a, T2 b) {
    while (a && b) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

template <typename T1>
T1 bpow(T1 a, ll n, ll mod) {
    a %= mod;
    T1 res = 1;
    while (n) {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

std::mt19937 RAND(48);

struct pairhash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const{
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};


/*
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
    assert((mpos += n) <= MAX_MEM);
    return (void *)(mem + mpos - n);
}
inline void operator delete ( void * ) noexcept { }
*/


// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int main(){
    faster;
    int n;
    cin >> n;
    
    return 0;
}