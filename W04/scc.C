# include <iostream>

# include <tpl_dynArray.H>
# include <tpl_graph.H>
# include <dfs.H>

using namespace std;

using Node = Graph_Node<long>;
using Arc  = Graph_Arc<Empty_Class>;
using DGT  = List_Digraph<Node, Arc>;

DGT read_graph()
{
  DynArray<DGT::Node *> nodes;
  nodes.set_default_initial_value(nullptr);
  
  DGT ret;

  size_t i = 1;
  long s_idx, t_idx;

  while (cin >> s_idx >> t_idx)
    {
      if (i % 10000 == 0)
	cout << i << ": " << s_idx << " -- " << t_idx << endl;

      ++i;

      auto s = nodes.touch(s_idx);

      if (s == nullptr)
	{
	  s = ret.insert_node(s_idx);
	  nodes(s_idx) = s;
	}

      auto t = nodes.touch(t_idx);

      if (t == nullptr)
	{
	  t = ret.insert_node(t_idx);
	  nodes(t_idx) = t;
	}
      
      ret.insert_arc(s, t);
    }

  return ret;
}

int main()
{
  cout << "Reading graph...\n";
  DGT g = read_graph();
  cout << "Done!\n";
  
  cout << "Num nodes: " << g.get_num_nodes() << endl
       << "Num arcs:  " << g.get_num_arcs() << endl;

  cout << "Computing strong connected components...\n";
  DynList<DGT> scc = kosaraju(g);
  cout << scc.size() << " strong connected components\n";
  cout << "Done!\n";

  cout << "Sorting components...\n";
  mergesort(scc, [](auto & a, auto & b) {
      return a.get_num_nodes() > b.get_num_nodes();
    });
  cout << "Done!\n";

  size_t i = 0;

  cout << "Result\n";
  for (DynList<DGT>::Iterator it(scc); it.has_curr() and i < 5; it.next(), ++i)
    cout << it.get_curr().get_num_nodes() << endl;
  
  return 0;
}
