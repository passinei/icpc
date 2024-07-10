# Sheet

## Template

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    return 0;
}
```

## Indexed Set

```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<
    int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update
> indexed_set;
```

```cpp
int idx = c.order_of_key(key);
auto it = c.find_by_order(idx);
```

## Random

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
```

```cpp
random_device rd;
mt19937 rng(rd());
```

```cpp
int x = rng() % lim;
shuffle(a.begin(), a.end(), rng);
```