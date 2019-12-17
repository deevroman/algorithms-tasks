
namespace Geomic{
    const ld eps = 1e-12;
    bool eq(ld x, ld y){
        return x == y;
        return fabs(x - y) < eps;
    }
    struct Point{
        ld x, y;
        Point(ld x_, ld y_) {
            x = x_;
            y = y_;
        }
        Point() {
            x = 0.0;
            y = 0.0;
        }
        ld dist(const Point& oth) const {
            return hypotf(x - oth.x, y - oth.y);
        }
        ld evklid_dist(const Point& oth) const{
            return fabs(x - oth.x) + fabs(y - oth.y);
        }
        friend std::istream& operator >> (std::istream &in, Point &P) {
            in >> P.x >> P.y;
            return in;
        }
        friend std::ostream& operator << (std::ostream &out, const Point &P) {
            out << P.x << ' ' << P.y;
            return out;
        }
        bool operator< (const Point &oth) const {
            return x < oth.x || (eq(x, oth.x) && y < oth.y);
        }
        bool operator== (const Point &oth) const {
            return eq(x, oth.x) && eq(y, oth.y);
        }
    };
    struct Vector{
        ld x, y;
        Vector(ld x_, ld y_) {
            x = x_;
            y = y_;
        }
        Vector(const Point& A, const Point& B) {
            x = B.x - A.x;
            y = B.y - A.y;
        }
        Vector() {
            x = 0;
            y = 0;
        }
        Vector operator +(const Vector& oth) const {
            return Vector(x + oth.x, y + oth.y);
        }
        Vector operator *(ld k) const {
            return Vector(x * k, y * k);
        }

        ld operator %(const Vector& oth) const {
            return x * oth.y - y * oth.x;
        }
        ld operator *(const Vector& oth) const {
            return x * oth.x + y * oth.y;
        }

        ld length() const {
            return hypotl(x, y);
        }
        Vector standart() const {
            return Vector(x / length(), y / length());
        }

        Vector normal() const {
            return Vector(-y, x);
        }
        bool is_parallel(const Vector& oth) const{
            return eq(normal() % oth.normal(), 0);
        }
        friend std::istream & operator >> (std::istream & in, Vector& V) {
            in >> V.x >> V.y;
            return in;
        }
        friend std::ostream & operator << (std::ostream & out, const Vector& V) {
            out << V.x << ' ' << V.y;
            return out;
        }
    };
    struct LineABC {
        ld a, b, c;
        LineABC(){}
        LineABC(ld a_, ld b_, ld c_){
            a = a_;
            b = b_;
            c = c_;
        }
        LineABC(const Point& A, const Point& B) {
            a = A.y - B.y;
            b = B.x - A.x;
            c = -(a * A.x + b * A.y);
        }
        void normalization(){
            ld d = hypotf(a, b);
            a /= d;
            b /= d;
            c /= d;
        }
        Vector normal() const{
            return Vector(a, b);
        }
        Point intersection(const LineABC& oth) const {
            ld q = a * oth.b - b * oth.a;
            return Point((b * oth.c - c * oth.b) / q,
                            (c * oth.a - a * oth.c) / q);
        }
        bool is_parallel(const LineABC &oth){
            return eq(normal() % oth.normal(), 0);
        }
        int in(Point A){ // TODo
            Vector v(Point(0, c/(-b)), 
                        Point(1000, (a*1000 + c)/(-b)));
            Vector v2(Point(0, c/(-b)), 
                        Point(A.x, A.y));
            ld ps = v % v2;
            if(eq(ps, 0))
                return 0;
            else if(ps > eps)
                return 1;
            else 
                return -1;
        }
        friend std::istream & operator >> (std::istream & in, LineABC& L) {
            in >> L.a >> L.b >> L.c;
            return in;
        }
        friend std::ostream & operator << (std::ostream & out, const LineABC& L) {
            out << L.a << ' ' << L.b << ' ' << L.c;
            return out;
        }
    };
    struct Line {
        Point A;
        Point B;
        Line(const Point& A_, const Point& B_) {
            A = A_;
            B = B_;
        }
        Vector direction() const {
            return Vector(A, B);
        }
        bool is_parallel(const Line& oth) const {
            return eq(direction() % oth.direction(), 0);
        }
        bool is_coincide(const Line& oth) const {
            return eq(is_parallel(oth) && direction() % Vector(A, oth.A), 0);
        }
        Point intersection(const Line& oth) const {
            if (is_parallel(oth)) {
                // throw exception 
                return Point(INF, INF);
            }
            return LineABC(A, B).intersection(LineABC(oth.A, oth.B));
        }
    };

    struct Polygon {// thanks to Mike Mirzayanov
        vector<Point> vertex;
        int size;
        Polygon(){}
        Polygon(vector<Point> &p){
            vertex = p; // can optimize
            vertex.push_back(vertex[0]);
            size = p.size();
        }
        vector<Polygon> split(LineABC line){
            int i1 = -1, i2 = -1;
            vector<Point> now_vertex = vertex;
            for(int i = 0; i < size; i++){
                LineABC seg = LineABC(vertex[i], vertex[i+1]);
                if(!seg.is_parallel(line)){
                    Point p = seg.intersection(line);
                    if(eq(Vector(vertex[i], p) % Vector(vertex[i], vertex[i+1]), 0)){
                        if(min(vertex[i].x, vertex[i+1].x) <= p.x && p.x <= max(vertex[i].x, vertex[i+1].x)
                        && min(vertex[i].y, vertex[i+1].y) <= p.y && p.y <= max(vertex[i].y, vertex[i+1].y)){ // FIXME
                            if(i1 == -1){
                                i1 = i + 1;
                            } else{
                                i2 = i + 1;                             
                            }
                            i++;
                            now_vertex.insert(now_vertex.begin() + i, p);
                        }
                    }
                }
            }
            if(i2 == -1){
                vector<Polygon> ans = {*this};
                return ans;
            } else{
                vector<Point> p1;
                for(int i = i1; i <= i2; i++){
                    p1.push_back(now_vertex[i]);
                }
                p1.push_back(now_vertex[i1]);
                vector<Point> p2;
                for(int i = i2; i <= i1; (i++)%now_vertex.size()){
                    p1.push_back(now_vertex[i]);
                }
                p1.push_back(now_vertex[i2]);
                vector<Polygon> ans = {Polygon(p1), Polygon(p2)};
                return ans;
            }
        }
        bool vip(){
            ll DIR = Vector(vertex[size-2], vertex[0]) 
                    % Vector(vertex[0], vertex[1]);
            for(int i = 0; i < size - 2; i++){
                ll dir = Vector(vertex[i], vertex[i+1]) 
                    % Vector(vertex[i+1], vertex[i+2]);
                if(dir * DIR < 0){
                    return false;
                }
            }
            return true;
        }
        bool in(Point p){
            ld sum = 0;
            for (int i = 0; i < size; ++i) {
                auto v1 = Vector(p, vertex[i]);
                auto v2 = Vector(p, vertex[i+1]);
                sum += asin((v1 % v2) / v1.length() / v2.length());
            }
            return !eq(sum, 0.0);
        }
        ld get_sq(){
            ld S = 0;
            for(int i = 2; i < size; i++){
                S += Vector(vertex[1], vertex[i]) % Vector(vertex[1], vertex[i+1]); 
            }
            return S / 2.0;
        }
        friend std::ostream & operator << (std::ostream & out, const Polygon& P) {
            for (int i = 0; i < P.size; ++i) {
                out << P.vertex[i] << "\n";
            }
            return out;
        }
    };
    Polygon get_ch(vector<Point> v){
        sort(v.begin(), v.end());
        auto left = v[0], right = v.back();
        auto terminator = Vector(left, right);
        vector<Point> up = {left}, down = {left};
        for(int i = 1; i < (int)v.size(); i++){
            if(terminator % Vector(left, v[i]) >= 0){
                while(true){
                    if(up.size() == 1){
                        up.push_back(v[i]);
                        break;
                    }
                    auto prev = Vector(up[up.size()-2], up[up.size()-1]);
                    auto now = Vector(up.back(), v[i]);
                    if(prev % now >= 0){
                        up.pop_back();
                    } else {
                        up.push_back(v[i]);
                        break;
                    }
                }
            }
            if (terminator % Vector(left, v[i]) <= 0) {
                while(true) {
                    if (down.size() == 1) {
                        down.push_back(v[i]);
                        break;
                    }
                    auto prev = Vector(down[down.size() - 2], down[down.size() - 1]);
                    auto now = Vector(down.back(), v[i]);
                    if (prev % now <= 0) {
                        down.pop_back();
                    } else {
                        down.push_back(v[i]);
                        break;
                    }
                }
            }
        }
        down.reserve(down.size() +  up.size() - 2);
        for(int i = (int)up.size() - 2; i > 0; i--){
            down.push_back(up[i]);
        }
        return Polygon(down);
    }
}
