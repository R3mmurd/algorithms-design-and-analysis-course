# ifndef DFS_H
# define DFS_H

# include <tpl_graph.H>
# include <tpl_dynListStack.H>

template <class GT, class Op>
void dfs(typename GT::Node * s, const Op & op)
{
  op(s);
  NODE_BITS(s).set_bit(Depth_First, true);
  DynListStack<typename GT::Node *> stack;
  stack.push(s);

  while (not stack.is_empty())
    {
      auto u = stack.pop();

      for (typename GT::Node_Arc_Iterator it(u); it.has_curr(); it.next())
	{
	  auto a = it.get_curr();

	  if (IS_ARC_VISITED(a, Depth_First))
	    continue;

	  ARC_BITS(a).set_bit(Depth_First, true);

	  auto v = it.get_tgt_node();

	  if (IS_NODE_VISITED(v, Depth_First))
	    continue;

	  op(v);

	  NODE_BITS(v).set_bit(Depth_First, true);

	  stack.push(v);
	}
    }
}

template <class GT, class Op>
void dfs_rec(typename GT::Node * s, const Op & op)
{
  if (IS_NODE_VISITED(s, Depth_First))
    return;

  op(s);
  NODE_BITS(s).set_bit(Depth_First, true);

  for (typename GT::Node_Arc_Iterator it(s); it.has_curr(); it.next())
    {
      auto a = it.get_curr();

      if (IS_ARC_VISITED(a, Depth_First))
	continue;

      ARC_BITS(a).set_bit(Depth_First, true);

      auto t = it.get_tgt_node();

      dfs_rec<GT, Op>(t, op);
    }
}

template <class GT>
void topological_sort_rec(typename GT::Node * s, long & curr_lbl)
{
  if (IS_NODE_VISITED(s, Depth_First))
    return;

  NODE_BITS(s).set_bit(Depth_First, true);

  for (typename GT::Node_Arc_Iterator it(s); it.has_curr(); it.next())
    {
      auto t = it.get_tgt_node();

      if (IS_NODE_VISITED(t, Depth_First))
	continue;

      topological_sort_rec<GT>(t, curr_lbl);
    }

  NODE_COUNTER(s) = curr_lbl--;
}

template <class GT>
void topological_sort(GT & g)
{
  g.reset_nodes();

  long curr_lbl = g.get_num_nodes();

  for (typename GT::Node_Iterator it(g); it.has_curr(); it.next())
    {
      auto p = it.get_curr();
      
      if (IS_NODE_VISITED(p, Depth_First))
	continue;

      topological_sort_rec<GT>(p, curr_lbl);
    }
}

template <class GT>
void dfs_rec(typename GT::Node * s, DynArray<typename GT::Node *> & df)
{
  if (IS_NODE_VISITED(s, Depth_First))
    return;

  NODE_BITS(s).set_bit(Depth_First, true);

  for (typename GT::Node_Arc_Iterator it(s); it.has_curr(); it.next())
    {
      auto t = it.get_tgt_node();
      
      if (IS_NODE_VISITED(t, Depth_First))
	continue;
      
      dfs_rec<GT>(t, df);
    }

  df.append(s);
  NODE_COUNTER(s) = df.size();
}

template <class GT>
DynArray<typename GT::Node *> dfs(GT & g)
{
  g.reset_nodes();
  g.reset_arcs();

  DynArray<typename GT::Node *> ret;

  for (typename GT::Node_Iterator it(g); it.has_curr(); it.next())
    {
      auto p = it.get_curr();

      if (IS_NODE_VISITED(p, Depth_First))
	continue;

      dfs_rec<GT>(p, ret);
    }

  return ret;
}

template <class GT>
GT invert_digraph(GT & g)
{
  GT inv_g;

  for (typename GT::Arc_Iterator it(g); it.has_curr(); it.next())
    {
      auto a = it.get_curr();

      auto s = g.get_src_node(a);
      auto inv_t = mapped_node<GT>(s);

      if (inv_t == nullptr)
	{
	  inv_t = new typename GT::Node(s);
	  inv_g.insert_node(inv_t);
	  GT::map_nodes(s, inv_t);
	}

      auto t = g.get_tgt_node(a);
      auto inv_s = mapped_node<GT>(t);

      if (inv_s == nullptr)
	{
	  inv_s = new typename GT::Node(t);
	  inv_g.insert_node(inv_s);
	  GT::map_nodes(t, inv_s);
	}

      auto inv_a = inv_g.insert_arc(inv_s, inv_t, a->get_info());
      GT::map_arcs(a, inv_a);
    }

  return inv_g;
}

template <class GT>
void build_strong_component(typename GT::Node * s, GT & sg)
{
  if (IS_NODE_VISITED(s, Depth_First))
    return;

  auto p = sg.insert_node(s->get_info());
  GT::map_nodes(s, p);

  NODE_BITS(s).set_bit(Depth_First, true);

  for (typename GT::Node_Arc_Iterator it(s); it.has_curr(); it.next())
    {
      auto a = it.get_curr();

      if (IS_ARC_VISITED(a, Depth_First))
	continue;

      auto t = it.get_tgt_node();

      build_strong_component(t, sg);
    }
}

template <class GT>
DynList<GT> kosaraju(GT & g)
{ 
  auto df = dfs(g);

  GT inv_g = invert_digraph<GT>(g);

  DynList<GT> ret;

  for (size_t i = df.size(); i > 0; --i)
    {
      auto v = mapped_node<GT>(df(i - 1));

      assert(v != nullptr);

      if (IS_NODE_VISITED(v, Depth_First))
	continue;

      GT sc;
      build_strong_component(v, sc);
      ret.append(move(sc));
    }

  return ret;
}

# endif // DFS_H
