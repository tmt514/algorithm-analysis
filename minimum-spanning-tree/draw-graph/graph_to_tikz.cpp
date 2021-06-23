#include <bits/stdc++.h>
using namespace std;

const double SQUARED_TARGET_DISTANCE = 3.0;

struct Config {
  bool show_node_label = true;

  Config(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
      string s = string(argv[i]);
      if (s == "-no-node-label") show_node_label = false;
    }
  }
};



class Vector {
 public:
  double x, y;
  Vector(double _x = 0, double _y = 0) {
    x = _x;
    y = _y;
  }
  Vector(mt19937& rng, double L = 0.0, double R = 100.0) {
    x = uniform_real_distribution<double>(L, R)(rng);
    y = uniform_real_distribution<double>(L, R)(rng);
  }
  Vector operator+(const Vector& p) const { return Vector(x + p.x, y + p.y); }
  Vector operator-(const Vector& p) const { return Vector(x - p.x, y - p.y); }

  Vector operator*(const double k) const { return Vector(k * x, k * y); }
  friend Vector operator*(const double k, const Vector p) {
    return Vector(k * p.x, k * p.y);
  }
  Vector operator/(const double k) const { return Vector(x / k, y / k); }

  double squared_length() { return x * x + y * y; }

  // If the distance is too close, make it farther.
  double get_elastic_coefficient(double squared_target_distance = SQUARED_TARGET_DISTANCE) {
    double d = squared_length();
    if (fabs(d - squared_target_distance) <= 0.01)
      return 0;
    else if (d >= 2*squared_target_distance) {
      double& s = squared_target_distance;
      return sqrtl(sqrtl(s / (d-s)));
      // return s / sqrtl(d * (d-s));
    } else if (d >= squared_target_distance) {
      double& s = squared_target_distance;
      return (d-s) / sqrtl(s * d) / 2.0;
    } else
      return -sqrtl(squared_target_distance / d - 0.99) * 4;
  }

  string generate_latex_string() {
    ostringstream o;
    o << std::fixed;
    o << "(" << x << ", " << y << ")";
    return o.str();
  }
};

typedef Vector Point;

class Vertex {
 public:
  string label;
  string math_mode_label;
  string node_style;
  Point location;

  // A vertex can be named with prefix-suffix.
  Vertex(int suffix, string prefix = "v") {
    label = prefix + to_string(suffix);
    math_mode_label = prefix + "_{" + to_string(suffix) + "}";
    node_style = "n";
  }

  // Or simply give entire label name. By default the math_mode_label is the
  // same as label. If is_math is set to be false then a \text wrapper is to be
  // added to the math_mode_label.
  Vertex(string label, bool is_math = true) {
    this->label = label;
    if (!is_math) {
      math_mode_label = "\\text{" + label + "}";
    } else {
      math_mode_label = label;
    }
  }
};

class Edge {
 public:
  shared_ptr<Vertex> u, v;
  string edge_style;

  Edge(shared_ptr<Vertex> u, shared_ptr<Vertex> v) {
    this->u = u;
    this->v = v;
    edge_style="e";
  }

  shared_ptr<Vertex> get_other_endpoint(shared_ptr<Vertex> x) {
    if (u->label == x->label)
      return v;
    else
      return u;
  }
};

class Graph {
 public:
  vector<shared_ptr<Vertex>> V;
  unordered_map<string, int> vertex_label_to_array_location;
  vector<shared_ptr<Edge>> E;
  vector<vector<shared_ptr<Edge>>> Adj;

  void add_vertex(int id) {
    int t = V.size();
    V.push_back(make_shared<Vertex>(id));
    Adj.push_back(vector<shared_ptr<Edge>>());
    string label = to_string(id);
    vertex_label_to_array_location[label] = t;
  }

  void add_edge(int u, int v) {
    string label_u = to_string(u);
    string label_v = to_string(v);
    int loc_u = vertex_label_to_array_location[label_u];
    int loc_v = vertex_label_to_array_location[label_v];
    auto e = make_shared<Edge>(V[loc_u], V[loc_v]);
    E.push_back(e);
    Adj[loc_u].push_back(e);
    Adj[loc_v].push_back(e);
  }

  void compute_location_2d(mt19937& rng) {
    int n = V.size();
    for (int i = 0; i < n; i++) V[i]->location = Point(rng, 0.0, 100.0);
    int ITERATIONS = 10000;
    double STEPSIZE = 0.05;
    for (int _ = 0; _ < ITERATIONS; ++_) {
      vector<int> permutation(n);
      iota(permutation.begin(), permutation.end(), 0);
      shuffle(permutation.begin(), permutation.end(), rng);

      for (int i : permutation) {
        Vector Vtotal(0.0, 0.0);
        auto Vi = V[i];
        for (auto e : Adj[i]) {
          auto Vj = e->get_other_endpoint(Vi);
          Vector Vdiff = Vj->location - Vi->location;
          // printf("  (%.5f, %.5f) -- (%.5f, %.5f)\n", Vi->location.x,
          // Vi->location.y, Vj->location.x, Vj->location.y);
          Vtotal = Vtotal + Vdiff * Vdiff.get_elastic_coefficient();
        }
        for (auto Vj : V) {
          if (Vi != Vj) {
            Vector Vdiff = Vj->location - Vi->location;
            if (Vdiff.squared_length() <= SQUARED_TARGET_DISTANCE) {
              Vtotal = Vtotal + Vdiff * Vdiff.get_elastic_coefficient();
            }
          }
        }
        Vi->location = Vi->location + Vtotal * STEPSIZE;
      }
      // STEPSIZE=max(0.001, STEPSIZE*0.99);
    }
  }

  vector<string> latex_defined_colors;
  vector<string> color_labels;
  vector<bool> used_colors;
  void generate_colors(mt19937& rng) {
    // For each connected component, choose a color and fill all the vertices and edges with that color.
    vector<vector<double>> vertex_colors(V.size());
    for (int i = 0; i < V.size(); i++) {
      vertex_colors[i].resize(3);
      double r = uniform_real_distribution<double>(0.0, 1.0)(rng);
      double g = uniform_real_distribution<double>(0.0, 1.0)(rng);
      double b = uniform_real_distribution<double>(0.0, 1.0)(rng);

      vertex_colors[i][0] = r / (r + g + b);
      vertex_colors[i][1] = g / (r + g + b);
      vertex_colors[i][2] = b / (r + g + b);
    }
    latex_defined_colors.resize(V.size());
    color_labels.resize(V.size());
    for(int i=0;i<V.size();i++) {
      ostringstream o;
      o << fixed << "\\definecolor{customcolor"
      << to_string(i) << "}{rgb}{"
      << vertex_colors[i][0] << ", "
      << vertex_colors[i][1] << ", "
      << vertex_colors[i][2] << "}";
      latex_defined_colors[i] = o.str();
      color_labels[i] = "customcolor" + to_string(i);
    }
    used_colors.clear();
    used_colors.resize(V.size(), false);
  }
  string generate_all_color_strings() {
    string s = "";
    for (int i = 0; i < latex_defined_colors.size(); i++) {
      if (used_colors[i])
        s += latex_defined_colors[i] + "\n";
    }
    return s;
  }

  string generate_latex_drawing(shared_ptr<Config> config) {
    string result = "";
    int n = V.size();

    result += "\\begin{pgfonlayer}{foreground}";

    for (int i = 0; i < n; i++) {
      string node_label = config->show_node_label?
        "{$" + V[i]->math_mode_label + "$}" :
        "{}";
      result += "\\node[" + V[i]->node_style + "](" + V[i]->label + ") at " +
                V[i]->location.generate_latex_string() + 
                node_label + ";\n";
    }

    result += "\\end{pgfonlayer}";

    for (auto e : E) {
      result += "\\draw[" + e->edge_style + "] (" + e->u->label + ") -- (" + e->v->label + ");\n";
    }

    return result;
  }


  void highlight_mst_edges(mt19937& rng) {
    // Initialize color palette.
    if (latex_defined_colors.empty())
      generate_colors(rng);

    vector<pair<double, shared_ptr<Edge>>> weighted_edges;
    for(auto e : E) {
      weighted_edges.push_back({
        (e->u->location - e->v->location).squared_length(),
        e
      });
    }
    sort(weighted_edges.begin(), weighted_edges.end(),
    [&](auto A, auto B) { if (A.first != B.first) return A.first < B.first;  return false; });
    vector<int> g(V.size());
    iota(g.begin(), g.end(), 0);
    auto FIND = [&](int x) {
      vector<int> _stack;
      while (g[x] != x) { _stack.push_back(x); x = g[x]; }
      for (auto y : _stack) g[y] = x;
      return x;
    };
    auto UNION = [&](int x, int y) { g[FIND(x)] = FIND(y); };
    unordered_map<string, int> vid;
    for(int i=0;i<V.size();i++) vid[V[i]->label] = i;
    int n = V.size();
    int target = n-6;
    for(auto it : weighted_edges) {
      
      shared_ptr<Vertex> u = it.second->u;
      shared_ptr<Vertex> v = it.second->v;
      int ulabel = vid[u->label];
      int vlabel = vid[v->label];
      if (FIND(ulabel) != FIND(vlabel)) {
        // E is a tree edge.
        UNION(ulabel, vlabel);
        it.second->edge_style = "e2";

        if (--target <= 0) break;

      } else {
        // E is a non-tree edge.
        it.second->edge_style = "e";
      }
    }

    for (int i = 0; i < n; i++) {
      V[i]->node_style="n,draw=" + color_labels[FIND(i)] + ",fill=" + color_labels[FIND(i)] + "!20!white";
      used_colors[FIND(i)] = true;
    }
    for (auto it : E) {
      int ulabel = vid[it->u->label];
      int vlabel = vid[it->v->label];
      if (it->edge_style == "e2") {
        it->edge_style = "line width=4pt,color=" + color_labels[FIND(ulabel)];
      }
    }
  }


};

unique_ptr<Graph> read_graph_from_stdin() {
  int n, m;
  cin >> n >> m;
  auto G = make_unique<Graph>();
  for (int i = 1; i <= n; i++) G->add_vertex(i);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    G->add_edge(x, y);
  }
  return G;
}

void output_graph(unique_ptr<Graph> G, shared_ptr<Config> config) {

  string node_style =
  config->show_node_label?
  "minimum size=20pt, inner sep=0.5pt, circle, draw=black, fill=white, line width=2pt" :
  "minimum size=6pt, inner sep=0pt, circle, draw=black, fill=black";

  string tikzset = "n/.style={" + node_style + "}, \
                    e2/.style={color=red, line width=4pt}, \
                    e/.style={color=gray}";

  string all_colors_strings = G->generate_all_color_strings();

  string result = R"(
\documentclass{standalone}
\usepackage{tikz}

\pgfdeclarelayer{foreground}
\pgfdeclarelayer{background}
\pgfsetlayers{background,main,foreground}
)"
+ 
all_colors_strings
+ R"(
\tikzset {)"+ tikzset
+R"(}
\begin{document}
\begin{tikzpicture}
)" + G->generate_latex_drawing(config) +
                  R"(
\end{tikzpicture}
\end{document}
)";
  cout << result;
}

int main(int argc, char* argv[]) {
  auto config = make_shared<Config>(argc, argv);
  auto G = read_graph_from_stdin();
  mt19937 rng(58);
  G->compute_location_2d(rng);
  G->highlight_mst_edges(rng);
  output_graph(move(G), move(config));
  return 0;
}