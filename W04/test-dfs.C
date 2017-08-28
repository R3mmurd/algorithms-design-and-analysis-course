# include <iostream>

# include <dfs.H>

using namespace std;

using Node = Graph_Node<char>;
using Arc  = Graph_Arc<Empty_Class>;
using GT   = List_Graph<Node, Arc>;
using DGT  = List_Digraph<Node, Arc>;

template <class G>
void print_graph(G & g, const string & name)
{
  if (g.is_digraph())
    cout << "Digraph ";
  else
    cout << "Graph ";

  cout << name << endl << g.get_num_nodes() << " nodes\n";

  for (typename G::Node_Iterator it(g); it.has_curr(); it.next())
    cout << it.get_curr()->get_info() << endl;

  cout << g.get_num_arcs() << " arcs\n";
    
  for (typename G::Arc_Iterator it(g); it.has_curr(); it.next())
    {
      auto a = it.get_curr();
      auto s = g.get_src_node(a);
      auto t = g.get_tgt_node(a);
      cout << s->get_info() << " -- " << t->get_info() << endl;
    }

  cout << endl;
}

# define PRINT(g) print_graph(g, #g)

int main()
{
  GT g1;
  
  auto g1s = g1.insert_node('s');
  auto g1a = g1.insert_node('a');
  auto g1b = g1.insert_node('b');
  auto g1c = g1.insert_node('c');
  auto g1d = g1.insert_node('d');
  auto g1e = g1.insert_node('e');

  g1.insert_arc(g1s, g1a);
  g1.insert_arc(g1s, g1b);
  g1.insert_arc(g1a, g1c);
  g1.insert_arc(g1a, g1b);
  g1.insert_arc(g1c, g1e);
  g1.insert_arc(g1c, g1d);
  g1.insert_arc(g1b, g1d);
  g1.insert_arc(g1d, g1e);
  
  PRINT(g1);

  cout << "Depth first search on g1...\n";
  dfs<GT>(g1s, [](auto p) { cout << p->get_info() << endl; });
  cout << "Done!\n\n";

  g1.reset_nodes();
  g1.reset_arcs();
  
  cout << "Depth first search recursive on g1...\n";
  dfs_rec<GT>(g1s, [](auto p) { cout << p->get_info() << endl; });
  cout << "Done!\n\n";

  DGT g2;

  auto g2s = g2.insert_node('s');
  auto g2v = g2.insert_node('v');
  auto g2w = g2.insert_node('w');
  auto g2t = g2.insert_node('t');

  g2.insert_arc(g2s, g2v);
  g2.insert_arc(g2s, g2w);
  g2.insert_arc(g2v, g2t);
  g2.insert_arc(g2w, g2t);

  PRINT(g2);

  cout << "Computing topological sort on g2...\n";
  topological_sort(g2);
  cout << "Done!\n";

  g2.for_each_node([](auto p) {
      cout << "f(" << p->get_info() << ") = " << NODE_COUNTER(p) << endl;
    });

  DGT g3;

  auto g3a = g3.insert_node('A');
  auto g3b = g3.insert_node('B');
  auto g3c = g3.insert_node('C');
  auto g3d = g3.insert_node('D');
  auto g3e = g3.insert_node('E');
  auto g3f = g3.insert_node('F');
  auto g3g = g3.insert_node('G');
  auto g3h = g3.insert_node('H');
  auto g3i = g3.insert_node('I');
  auto g3j = g3.insert_node('J');
  auto g3k = g3.insert_node('K');

  g3.insert_arc(g3b, g3a);
  g3.insert_arc(g3a, g3d);
  g3.insert_arc(g3b, g3c);
  g3.insert_arc(g3c, g3d);
  g3.insert_arc(g3e, g3b);
  g3.insert_arc(g3d, g3e);
  g3.insert_arc(g3e, g3g);
  g3.insert_arc(g3e, g3h);
  g3.insert_arc(g3g, g3f);
  g3.insert_arc(g3f, g3g);
  g3.insert_arc(g3h, g3i);
  g3.insert_arc(g3i, g3j);
  g3.insert_arc(g3j, g3k);
  g3.insert_arc(g3k, g3i);

  PRINT(g3);

  cout << "Computing strong components on g3...\n";
  auto l = kosaraju(g3);
  cout << "Done!\n";

  size_t counter = 0;

  l.mutable_for_each([&counter](GT & sc) {
      stringstream s;
      s << "Component " << ++counter << endl;
      print_graph(sc, s.str());
    });

  DGT g4;

  auto g4a = g4.insert_node('A');
  auto g4b = g4.insert_node('B');
  auto g4c = g4.insert_node('C');
  auto g4d = g4.insert_node('D');
  auto g4e = g4.insert_node('E');
  auto g4f = g4.insert_node('F');
  auto g4g = g4.insert_node('G');
  auto g4h = g4.insert_node('H');
  auto g4i = g4.insert_node('I');

  g4.insert_arc(g4a, g4b);
  g4.insert_arc(g4b, g4c);
  g4.insert_arc(g4c, g4a);

  g4.insert_arc(g4b, g4d);

  g4.insert_arc(g4d, g4e);
  g4.insert_arc(g4e, g4f);
  g4.insert_arc(g4f, g4d);

  g4.insert_arc(g4e, g4g);

  g4.insert_arc(g4g, g4h);
  g4.insert_arc(g4h, g4i);
  g4.insert_arc(g4i, g4g);

  PRINT(g4);

  cout << "Computing strong components on g4...\n";
  auto l2 = kosaraju(g4);
  cout << "Done!\n";

  counter = 0;

  l2.mutable_for_each([&counter](GT & sc) {
      stringstream s;
      s << "Component " << ++counter << endl;
      print_graph(sc, s.str());
    });
  
  return 0;
}
