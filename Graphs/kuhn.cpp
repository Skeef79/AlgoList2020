vector<vector<int>>g;
vector<int>mt;
vector<bool>used;

int n, m; 

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	
	for(auto to:g[v])
		if (mt[to] == -1 || dfs(mt[to])) {
			mt[to] = v;
			return true;
		}
	return false;
}

int kuhn() {
	fill(all(r),-1);
	int ans = 0;
	for (int v = 0; v < n; v++) {
		fill(all(used), false);
		if (dfs(v))
			ans++;
	}
	return ans;
}
