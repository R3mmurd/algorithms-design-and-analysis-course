# include <iostream>

# include <gsl/gsl_rng.h>

# include <tpl_graph.H>
# include <Karger.H>

using namespace std;

using Node = Graph_Node<size_t>;
using Arc = Graph_Arc<Empty_Class>;
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

  strs.append(str.substr(beg - 1, str.size() - beg));

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

      size_t src_lbl = stoul(split_str.access(0));

      GT::Node * src = nodes.access(src_lbl);

      if (src == nullptr)
	{
	  src = ret.insert_node(src_lbl);
	  nodes.access(src_lbl) = src;
	}

      for (size_t i = 1; i < split_str.size() - 1; ++i)
	{
	  size_t tgt_lbl = stoul(split_str.access(i));
	  
	  GT::Node * tgt = nodes.access(tgt_lbl);
	  
	  if (tgt == nullptr)
	    {
	      tgt = ret.insert_node(tgt_lbl);
	      nodes.access(tgt_lbl) = tgt;
	    }

	  GT::Arc * a = search_arc(src, tgt);

	  if (a == nullptr)
	    a = ret.insert_arc(src, tgt);
	}
    }

  return ret;
}

int main()
{
  GT g = read_graph();

  cout << "Num nodes: " << g.get_num_nodes() << endl
       << "Num arcs:  " << g.get_num_arcs() << endl << endl;
  
  DynList<GT::Node *> vs;
  DynList<GT::Node *> vt;
  DynList<GT::Arc *> cut;
  
  size_t minimum = Karger_Min_Cut<GT>()(g, vs, vt, cut, 2000);
  cout << "Min cut size: " << minimum << endl;
  
  return 0;
}
