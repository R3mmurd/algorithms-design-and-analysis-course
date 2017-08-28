# ifndef BFS_H
# define BFS_H

# include <limits>

# include <tpl_graph.H>
# include <htlist.H>
# include <tpl_dynListQueue.H>

template <class GT, class Op>
void bfs(typename GT::Node * s, const Op & op)
{
  op(s);
  NODE_BITS(s).set_bit(Breadth_First, true);
  DynListQueue<typename GT::Node *> queue;
  queue.put(s);

  while (not queue.is_empty())
    {
      auto u = queue.get();

      for (typename GT::Node_Arc_Iterator it(u); it.has_curr(); it.next())
	{
	  auto a = it.get_curr();

	  if (IS_ARC_VISITED(a, Breadth_First))
	    continue;

	  ARC_BITS(a).set_bit(Breadth_First, true);

	  auto v = it.get_tgt_node();

	  if (IS_NODE_VISITED(v, Breadth_First))
	    continue;

	  op(v);

	  NODE_BITS(v).set_bit(Breadth_First, true);

	  queue.put(v);
	}
    }
}

template <class GT>
void compute_dist_bfs(GT & g, typename GT::Node * s)
{
  g.reset_nodes();
  g.reset_arcs();
  
  for (typename GT::Node_Iterator it(g); it.has_curr(); it.next())
    {
      auto v = it.get_curr();
      NODE_COUNTER(v) = (v == s ? 0 : std::numeric_limits<long>::max());
    }
  
  NODE_BITS(s).set_bit(Breadth_First, true);
  DynListQueue<typename GT::Node *> queue;
  queue.put(s);
  
  while (not queue.is_empty())
    {
      auto u = queue.get();

      for (typename GT::Node_Arc_Iterator it(u); it.has_curr(); it.next())
	{
	  auto a = it.get_curr();

	  if (IS_ARC_VISITED(a, Breadth_First))
	    continue;

	  ARC_BITS(a).set_bit(Breadth_First, true);

	  auto v = it.get_tgt_node();

	  if (IS_NODE_VISITED(v, Breadth_First))
	    continue;

	  NODE_COUNTER(v) = NODE_COUNTER(u) + 1;
	  NODE_BITS(v).set_bit(Breadth_First, true);
	  queue.put(v);
	}
    }
}

template <class GT>
GT build_component(typename GT::Node * s)
{
  assert(not IS_NODE_VISITED(s, Breadth_First));

  GT ret;

  auto ret_s = mapped_node<GT>(s);

  if (ret_s == nullptr)
    {
      ret_s = ret.insert_node(s->get_info());
      GT::map_nodes(s, ret_s);
    }

  NODE_BITS(s).set_bit(Breadth_First, true);
  DynListQueue<typename GT::Node *> queue;
  queue.put(s);

  while (not queue.is_empty())
    {
      auto u = queue.get();

      for (typename GT::Node_Arc_Iterator it(u); it.has_curr(); it.next())
	{
	  auto a = it.get_curr();

	  if (IS_ARC_VISITED(a, Breadth_First))
	    continue;
	  
	  ARC_BITS(a).set_bit(Breadth_First, true);

	  auto v = it.get_tgt_node();

	  auto ret_u = mapped_node<GT>(u);
	  assert(ret_u != nullptr);
	  
	  auto ret_v = mapped_node<GT>(v);

	  if (ret_v == nullptr)
	    {
	      ret_v = ret.insert_node(v->get_info());
	      GT::map_nodes(v, ret_v);
	    }

	  auto ret_a = mapped_arc<GT>(a);

	  if (ret_a == nullptr)
	    {
	      ret_a = ret.insert_arc(ret_u, ret_v, a->get_info());
	      GT::map_arcs(a, ret_a);
	    }

	  if (IS_NODE_VISITED(v, Breadth_First))
	    continue;
	  
	  NODE_BITS(v).set_bit(Breadth_First, true);

	  queue.put(v);
	}
    }

  return ret;
}

template <class GT>
DynList<GT> connected_components(GT & g)
{
  g.reset_nodes();
  g.reset_arcs();
  
  DynList<GT> ret;

  for (typename GT::Node_Iterator it(g); it.has_curr(); it.next())
    {
      auto v = it.get_curr();

      if (IS_NODE_VISITED(v, Breadth_First))
	continue;

      ret.append(build_component<GT>(v));
    }

  return ret;
}

# endif // BFS_H
