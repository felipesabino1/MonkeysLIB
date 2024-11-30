#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

template<class T> using ordset = tree<
T,
null_type,
less<T>,
rb_tree_tag,
tree_order_statistics_node_update>;

ordset<int> os;