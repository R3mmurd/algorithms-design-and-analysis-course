# include <iostream>
# include <tpl_dynArray.H>

using namespace std;

using ul = unsigned long;
using Array = DynArray<ul>;

ul merge(Array & a, ul l, ul m, ul r)
{
  ul i, j, k, s;

  s = r - l + 1;

  ul mid = (s - 1) / 2;

  Array b(s);

  for (i = l, k = 0; i <= m; ++i, ++k)
    b.touch(k) = a(i);

  for (j = r; j > m; ++k, --j)
    b.touch(k) = a(j);

  ul ret_val = 0;

  for (k = l, i = 0, j = s - 1; k <= r; ++k)
    {
      if (b(j) < b(i))
        {
          a(k) = b(j--);
          ret_val += mid + 1 - i;
        }
      else
	a(k) = b(i++);
    }

  return ret_val;
}

ul mergesort(Array & a, ul l, ul r)
{
  if (l >= r)
    return 0;

  ul m = (l + r) / 2;

  ul num = 0;

  num += mergesort(a, l, m);

  num += mergesort(a, m + 1, r);

  if (a(m) < a(m + 1))
    return num;

  num += merge(a, l, m, r);

  return num;
}

ul mergesort(Array & a)
{
  return mergesort(a, 0, a.size() - 1);
}

int main()
{
  Array a;
  ul n;

  while (cin >> n)
    a.append(n);      

  ul ret = mergesort(a);

  std::cout << ret << "\n";

  return 0;
}

