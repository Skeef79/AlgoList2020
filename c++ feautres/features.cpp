
//#include<algorithm>
// merge a and b into c 
merge(all(a), all(b), back_inserter(c));


//#include<algorithm>
//cycle shift, elements a[m...n-1] become first
rotate(a.begin(), a.begin() + m, a.end()); // 1,2,3,4,5 -> 3,4,5,1,2
rotate(a.rbegin(), a.rbegin() + m, a.rend()); // 1,2,3,4,5 -> 4,5,1,2,3


//coordinate compression
vector<ll>coords;
//add all possible values
sort(all(coords));
coords.resize(unique(all(coords)) - coords.begin());


//set operator overloading (modern C++20 solution by dimasidorenko)
auto cmp = [](point a, point b) { return a.x < b.x };
set<point, decltype(cmp)> st(cmp);

//working not only on C++20 by dimas
struct CMP {
	bool operator () (int a, int b) const {
		if (dist[a] != dist[b])
			return dist[a] < dist[b];
		return a < b;
	}
};
set<int, CMP> ss;



//TODO add hash overloading for unordered_set 
