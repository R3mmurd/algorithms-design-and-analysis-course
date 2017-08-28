# include <iostream>

# include <bfs.H>

using namespace std;

using Node = Graph_Node<char>;
using Arc  = Graph_Arc<Empty_Class>;
using GT   = List_Graph<Node, Arc>;

void print_graph(GT & g, const string & name)
{
  cout << "Graph " << name << endl
       << g.get_num_nodes() << " nodes\n";

  for (GT::Node_Iterator it(g); it.has_curr(); it.next())
    cout << it.get_curr()->get_info() << endl;

  cout << g.get_num_arcs() << " arcs\n";
    
  for (GT::Arc_Iterator it(g); it.has_curr(); it.next())
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
  g1.insert_arc(g1d, g1e)
  
  PRINT(g1);

  cout << "Breadth first search...\n";
  bfs<GT>(g1s, [](auto p) { cout << p->get_info() << endl; });
  cout << "Done!\n";
  
  cout << "Computing distance from " << g1s->get_info()
       << " to all of other nodes of g1...\n";
  compute_dist_bfs(g1, g1s);

  cout << "Done!\n";

  for (GT::Node_Iterator it(g1); it.has_curr(); it.next())
    {
      auto v = it.get_curr();
      cout << "dist(" << v->get_info() << ") = " << NODE_COUNTER(v) << endl;
    }

  cout << endl;

  GT g2;

  auto g2a = g2.insert_node('a');
  auto g2b = g2.insert_node('b');
  auto g2e = g2.insert_node('e');
  auto g2d = g2.insert_node('d');
  
  g2.insert_arc(g2a, g2b);
  g2.insert_arc(g2d, g2b);
  g2.insert_arc(g2a, g2e);
  g2.insert_arc(g2a, g2d);
  g2.insert_arc(g2e, g2d);
  
  auto g2c = g2.insert_node('c');
  auto g2f = g2.insert_node('f');
  auto g2h = g2.insert_node('h');

  g2.insert_arc(g2c, g2h);
  g2.insert_arc(g2c, g2f);
  g2.insert_arc(g2h, g2f);
  
  auto g2g = g2.insert_node('g');
  auto g2i = g2.insert_node('i');

  g2.insert_arc(g2g, g2i);

  PRINT(g2);

  cout << "Computing connected components of g2...\n";
  DynList<GT> cc = connected_components(g2);
  cout << "Done!\n";

  size_t counter = 0;
  
  cc.mutable_for_each([&counter](GT & c) {
      stringstream s;
      s << "Component " << ++counter;
      print_graph(c, s.str());
      cout << endl;
    });
  
  return 0;
}
