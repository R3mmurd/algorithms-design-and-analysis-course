# include <iostream>

# include <gsl/gsl_rng.h>

# include <tpl_graph.H>
# include <Dijkstra.H>

using namespace std;

using Node = Graph_Node<size_t>;
using Arc = Graph_Arc<double>;
using GT = List_Graph<Node, Arc>;

DynArray<string> split_string(const string & str, char sep)
{
  DynArray<string> strs;

  size_t beg = 0;
  size_t end = str.find(sep);

  while (end != std::string::npos)
    {
      strs.append(str.substr(beg, end - beg));
      beg = end + 1;
      end = str.find(sep, beg);
    }

  strs.append(str.substr(beg, str.size() - beg));

  return strs;
}

GT::Arc * search_arc(GT::Node * s, GT::Node * t)
{
  for (GT::Node_Arc_Iterator it(s); it.has_curr(); it.next())
    {
      auto v = it.get_tgt_node();

      if (v == t)
	return it.get_curr();
    }

    for (GT::Node_Arc_Iterator it(t); it.has_curr(); it.next())
    {
      auto v = it.get_tgt_node();

      if (v == s)
	return it.get_curr();
    }

  return nullptr;
}

GT read_graph()
{
  GT ret;

  DynArray<GT::Node *> nodes;

  constexpr size_t Num_Nodes = 200;

  for (size_t i = 0; i <= Num_Nodes; ++i)
    nodes.touch(i) = nullptr;
  
  string line;

  while (getline(cin, line))
    {
      DynArray<string> split_str = split_string(line, '\t');

      size_t src_lbl = stoul(split_str(0));

      GT::Node * src = nodes(src_lbl);

      if (src == nullptr)
	{
	  src = ret.insert_node(src_lbl);
	  nodes(src_lbl) = src;
	}

      for (size_t i = 1; i < split_str.size() - 1; ++i)
	{
	  DynArray<string> adj = split_string(split_str(i), ',');

	  assert(adj.size() == 2);

	  size_t tgt_lbl = stoul(adj(0));
	  double w = stod(adj(1));
	  
	  GT::Node * tgt = nodes(tgt_lbl);
	  
	  if (tgt == nullptr)
	    {
	      tgt = ret.insert_node(tgt_lbl);
	      nodes.access(tgt_lbl) = tgt;
	    }

	  GT::Arc * a = search_arc(src, tgt);

	  if (a == nullptr)
	    a = ret.insert_arc(src, tgt, w);
	}
    }

  return ret;
}

struct Dist
{
  using Distance_Type = double;

  Distance_Type operator () (GT::Arc * a)
  {
    return a->get_info();
  }

  static const Distance_Type Max_Distance;

  static const Distance_Type Zero_Distance;
};

const Dist::Distance_Type Dist::Max_Distance =
  numeric_limits<double>::max();

const Dist::Distance_Type Dist::Zero_Distance = double(0);

# define CALL_DIJKSTRA(i) \
  assert(s != nullptr); \
  e = g.search_node([](auto p) { return p->get_info() == i; }); \
  assert(e != nullptr); \
  sstr << Dijkstra(g, s, e, path) << ','; \
  e = nullptr; \
  path.empty()

int main()
{
  GT g = read_graph();

  cout << "Num nodes: " << g.get_num_nodes() << endl
       << "Num arcs:  " << g.get_num_arcs() << endl << endl;
  
  Dijkstra_Min_Paths<GT, Dist> Dijkstra;
  Path<GT> path(g);

  stringstream sstr;

  GT::Node * s = g.search_node([](auto p) { return p->get_info() == 1; });
  GT::Node * e = nullptr;

  CALL_DIJKSTRA(7);
  CALL_DIJKSTRA(37);
  CALL_DIJKSTRA(59);
  CALL_DIJKSTRA(82);
  CALL_DIJKSTRA(99);
  CALL_DIJKSTRA(115);
  CALL_DIJKSTRA(133);
  CALL_DIJKSTRA(165);
  CALL_DIJKSTRA(188);
  CALL_DIJKSTRA(197);
  
  cout << sstr.str() << endl;
  
  return 0;
}
