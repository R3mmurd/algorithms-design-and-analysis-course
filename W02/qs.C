# include <iostream>
# include <random>

# include <tpl_dynArray.H>

using namespace std;

using Pair = pair<int, int>;

typedef int (*Sel_Pivot)(DynArray<int> &, int, int);

int partition(DynArray<int> & a, int l, int r, Sel_Pivot sel_pivot)
{
  if (l == r)
    return l;
  
  int p = sel_pivot(a, l, r);
  
  swap(a(l), a(p));

  int i = l + 1;

  for (int j = l + 1; j <= r; ++j)
    {
      if (a(j) < a(l))
	{
	  swap(a(j), a(i));
	  ++i;
	}
    }

  swap(a(l), a(i - 1));

  return i - 1;
}

size_t quicksort(DynArray<int> & a, int l, int r, Sel_Pivot sel_pivot)
{
  if (l > r)
    return 0;

  int p = partition(a, l, r, sel_pivot);

  size_t ret = r - l;

  ret += quicksort(a, l, p - 1, sel_pivot);
  ret += quicksort(a, p + 1, r, sel_pivot);

  return ret;
}

int select_last(DynArray<int> &, int, int r)
{
  return r;
}


int select_first(DynArray<int> &, int l, int)
{
  return l;
}

int select_median(DynArray<int> & a, int l, int r)
{
  if (r - l + 1 < 3)
    return r;

  auto m = (l + r) / 2;

  const int & x = a(l);
  const int & y = a(m);
  const int & z = a(r);
  
  Pair ret;

  if (x < y)
    {
      if (y < z)
	return m;
      else if (z < x)
	return l;
      else
	return r;
    }
  else
    {
      if (x < z)
	return l;
      else if (z < y)
	return m;
      else
	return r;
    }
}

void print_a(DynArray<int> & a, int n)
{
  for (int i = 0; i < n; ++i)
    cout << a[i] << ' ';
  cout << endl;
}

void test_order(const DynArray<int> & a)
{
  int value = numeric_limits<int>::min();
  a.for_each([&value] (int item)
	     {
	       if (item < value)
		 {
		   cout << "Array is not sorted" << endl;
		   exit(0);
		 }
	       value = item;
	     });
}

void usage(char * argv[])
{
  cout << "Usage: " << argv[0] << " num-problem\n\n"
       << "num-problem:\n"
       << "1: Select first element as pivot\n"
       << "2: Select last element as pivot\n"
       << "3: Select \"median-of-three\" element as pivot\n\n";
}

int main(int argc, char * argv[])
{
  if (argc != 2)
    {
      usage(argv);
      return 1;
    }

  Sel_Pivot sel_pivot = nullptr;

  switch (stoi(argv[1]))
    {
    case 1: sel_pivot = select_first; break;
    case 2: sel_pivot = select_last; break;
    case 3: sel_pivot = select_median; break;
    default: usage(argv); return 1;
    }
  
  DynArray<int> a;

  int item;

  while (cin >> item)
    a.append(item);

  cout << quicksort(a, 0, a.size() - 1, sel_pivot) << endl;

  test_order(a);
    
  return 0;
}
