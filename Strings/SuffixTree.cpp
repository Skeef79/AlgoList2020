
const int maxn = 1e4;
char s[maxn];
map<int, int> to[maxn];
int len[maxn], fposs[maxn], link[maxn];
int node; // вершина в который мы сейчас стоим
int pos; // на сколько  надо спустится по ребру чтобы дойти до текущего символа
int sz = 1, n = 0;
 
int make_node(int _pos, int _len)
{
    // ну тут мы просто ставим начало и длину ребра и увеличиваем размер дерева на 1
    fposs[sz] = _pos;
    len [sz] = _len;
    return sz++;
}
 
void go_edge()// спуск по ребру
{
    cerr << len[to[node][s[n - pos]]];
    // если перехода не будет, то to[node][s[n - pos]] = 0, а len[0] = inf
    while(pos > len[to[node][s[n - pos]]])  // пока мы можем полностью пройти по ребру и не дойдем до нужной позиции
    {
        node = to[node][s[n - pos]]; //  переходим в следующую вершину по ребру
        pos -= len[node]; // Теперь осталось пройти pos меньше на длину ребра
    }
}
 
void add_letter(int c){
    s[n++] = c;// что это за говно зачем
    pos++;
    int last = 0; // вершина из которой мы притопали в текущую ветку, по дефолту 0, когда когда нет прошлоый вершины, для которой нужно скрафтить ссылку, потому что ссылку из 0 мы не юзаем, так что если будем в ней что-то перетыкивать, мы ничего не  заруиним
    while(pos > 0) // пока не прошли сколько надо
    {
        go_edge(); // переходим по ребрам, пока можем полностью пройти по ребру
        int edge = s[n - pos]; // по какой букве надо идти
        int kek = to[node][edge];
        int &v = to[node][edge]; //ВНИМАНИЕ ТУТ ССЫЛКА номер вершины в которую пойдем по ребру
        int t = s[fposs[v] + pos - 1]; // символ в который мы придем на ребре
        if(v == 0) // перехода нет(по свойству расширения поддерева такое возможно только если нам надо сходить из вершины по 1 добавляемому символу),то есть мы стоим в вершине, надо скрафтить лист, но новой вершины-разветвления не появится
        {
            v = make_node(n - pos, inf); // крафтим его
            link[last] = node; // ставим суффссылку для прошлой созданной вершины
            last = 0; // так как новую вершину мы не создавали, никакая вершина не ждет крафта суффссылки
        }
        else if(t == c) // если мы смогли перейти по новому символу
        {
            link[last] = node; // то ставим из прошлой ссылку текущую и завершаем итерацию по добавлению этого символа
            return;
        }
        else // мы не прошли по символу и надо крафтить новую вершину
        {
            int u = make_node(fposs[v], pos - 1); // мы крафтим новую вершину - разветвление и дописываем все, что осталось, кроме дописываемого символа, который улетит в другую часть разветвления - лист
            to[u][c] = make_node(n - 1, inf); // а теперь вершину лист
            to[u][t] = v;// а это мы добавляем вторую ветку разветвления, в которой было все старое содержимое до добавления символа
            // а теперь меняем начало и длину этой ветки
            fposs[v] += pos - 1;   // мы отошли на pos-1 для крафта u, так что начало сдвигается вперед
            len [v] -= pos - 1; // а длина наоборот уменьшается
            v = u; // теперь топнули в разветвление заодно изменили to, которое передавали по ссылке
            link[last] = u; // поставили суффиксную ссылку прошлой созданной вершине
            last = u; // мы на этом ходе скарфтили вершину u, она теперь ждет постановки суффиксной сссылки
        }
        if(node == 0) // если пришли в корень надо минусануться и по ссылке не ходить
            pos--;
        else
            node = link[node]; // переходим по суффиксной ссылке
    }
}
 
int main()
{
    freopen("input.txt", "r", stdin);
    len[0] = inf;
    string s;
    cin >> s;
    int ans = 0;
    for(int i = 0; i < s.size(); i++) // добавляем по символу
        add_letter(s[i]);
    for(int i = 1; i < sz; i++)
        ans += min((int)s.size() - fposs[i], len[i]);
    cout << ans << "\n";
}