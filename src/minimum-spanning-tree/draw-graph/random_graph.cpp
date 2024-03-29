#include <bits/stdc++.h>
using namespace std;

class Vector {
 public:
  double x, y;
  Vector(double _x = 0, double _y = 0) {
    x = _x;
    y = _y;
  }
  Vector(mt19937& rng, double X = 0.0, double Y = 100.0) {
    x = uniform_real_distribution<double>(0.0, X)(rng);
    y = uniform_real_distribution<double>(0.0, Y)(rng);
  }
  Vector operator+(const Vector& p) const { return Vector(x + p.x, y + p.y); }
  Vector operator-(const Vector& p) const { return Vector(x - p.x, y - p.y); }

  Vector operator*(const double k) const { return Vector(k * x, k * y); }
  friend Vector operator*(const double k, const Vector p) {
    return Vector(k * p.x, k * p.y);
  }
  Vector operator/(const double k) const { return Vector(x / k, y / k); }

  double squared_length() { return x * x + y * y; }
};

// Generates random simple graph. In order to provide better visualization, we
// generate random points on a plane and connect them if they are close to each
// other.
int main(int argc, char* argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Usage: ./random_graph [n=10] [W=100.0] [H=50.0]\n");
    return 0;
  }
  int n = atoi(argv[1]);
  double W = atof(argv[2]);
  double H = atof(argv[3]);

  mt19937 rng(58);
  vector<Vector> v;
  // vector<pair<int, int>> E;
  for (int i = 0; i < n; i++) {
    v.push_back(Vector(rng, W, H));
  }
  set<pair<int, int>> E;
  for (int i = 0; i < n; i++) {
    vector<pair<double, int>> dist;
    for(int j=0;j<n;j++) if(j!=i) {
      dist.push_back({ (v[i]-v[j]).squared_length(), j });
    }
    sort(dist.begin(), dist.end());
    for(int j=0;j<5 && j <dist.size();j++) {
      assert(i != dist[j].second);
      E.insert({i+1, dist[j].second+1});
      E.insert({dist[j].second+1, i+1});
    }
  }
  fprintf(stderr, "%d edges!\n", (int)E.size() / 2);
  printf("%d %d\n", n, (int)E.size() / 2);
  for (auto it: E) {
    if (it.first < it.second) {
      printf("%d %d\n", it.first, it.second);
    }
  }

  return 0;
}