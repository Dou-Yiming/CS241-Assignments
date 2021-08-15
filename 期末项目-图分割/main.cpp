#include "Graph_generator.h"
#include "Graph_reader.h"
#include "Save_sub_graph.h"
#include "ver_algorithm.h"
#include "swap_optimization.h"
#include "checker.h"
#include "edge_algorithm.h"
#include "path.h"
#include <ctime>

vector<vector<string>> ans;
void generate();
Graph_reader read();
void calc_ver_algorithm(Graph_reader &reader);
void calc_edge_algorithm(Graph_reader &reader);
void save_to_buffer(Graph_cutter *&cutter);
void save_ans(int num_of_sub_graph);
void save_sub_graph(Graph_reader &reader);
void check();
void op();
void calc_path();

const int RANGE_OF_DELTA = 20;
const int NUM_OF_LOOP = 100;
int main()
{
    generate();
    Graph_reader reader = read();
    calc_ver_algorithm(reader);
    // op();
    save_sub_graph(reader);
    check();
    calc_path();
    calc_edge_algorithm(reader);
}

void generate()
{
    printf("*******************************\n");
    cout << "input the num of ver and edge:\n";
    int num_of_ver, num_of_edge;
    cin >> num_of_ver >> num_of_edge;
    generator g(num_of_ver, num_of_edge);
    g.save();
    cout << "data saved!\n";
    printf("*******************************\n\n");
}
Graph_reader read()
{
    printf("*******************************\n");
    cout << "input the address:\n";
    string address = "data\\in.txt";
    //cin >> address;
    Graph_reader r(address);
    printf("data loaded!\n");
    printf("*******************************\n\n");
    return r;
}
void calc_ver_algorithm(Graph_reader &reader)
{
    printf("*******************************\n");
    cout << "input the size of subgraph:\n";
    int size_of_sub_graph;
    cin >> size_of_sub_graph;

    Graph_cutter *cutter = new Graph_cutter(reader);
    double final_loss = cutter->ver_algorithm(size_of_sub_graph, 0);
    printf("     current loss:%lf\n", final_loss);
    save_to_buffer(cutter);
    save_ans(cutter->get_num_of_root());

    int seed = 123;
    for (int i = 0; i < NUM_OF_LOOP; ++i)
    {
        srand(seed);
        int delta = rand() % RANGE_OF_DELTA;
        printf("%d: running with delta=%d", i, delta);
        Graph_cutter *_cutter = new Graph_cutter(reader);
        time_t begin, end;
        begin = clock();
        double tmp_loss = _cutter->ver_algorithm(size_of_sub_graph, delta);
        end = clock();
        printf("   run time: %d ms", end - begin);
        if (tmp_loss < final_loss)
        {
            save_to_buffer(_cutter);
            save_ans(_cutter->get_num_of_root());
            final_loss = tmp_loss;
            cout << "   Updated!";
        }
        printf("     current loss:%lf\n", final_loss);
        delete _cutter;
        seed = seed * seed + clock();
        seed %= 123;
    }

    printf("Final loss:%lf\n", final_loss);
    printf("*******************************\n\n");
}
void calc_edge_algorithm(Graph_reader &reader)
{
    printf("*******************************\n");
    printf("Now let's test another algorithm based on edge!\n");
    cout << "input the size of subgraph:\n";
    int size_of_sub_graph;
    cin >> size_of_sub_graph;

    Graph_cutter_edge *cutter = new Graph_cutter_edge(reader);
    double final_loss = cutter->another_algorithm(size_of_sub_graph);
    cout << "Final loss:" << final_loss << endl;
    printf("*******************************\n\n");
}
void save_to_buffer(Graph_cutter *&cutter)
{
    ans.clear();
    int num_of_root = cutter->get_num_of_root();
    for (int i = 0; i < num_of_root; ++i)
    {
        vector<string> tmp;
        string line;
        for (auto &ver : cutter->get_ver_vct())
        {
            if (cutter->get_tag()[ver] == cutter->get_root_vct()[i])
            {
                line = to_string(ver);
                tmp.push_back(line + " ");
            }
            line.clear();
        }
        ans.push_back(tmp);
    }
}
void save_ans(int num_of_sub_graph)
{
    string str = "data\\output.txt";
    ofstream ofile(str);
    for (int i = 0; i < num_of_sub_graph; ++i)
    {
        for (auto &it : ans[i])
            ofile << it;
        ofile << "\n";
    }
    ofile.close();
}
void save_sub_graph(Graph_reader &reader)
{
    printf("*******************************\n");
    printf("saving subgraphs...\n");
    Graph_merge m("data\\in.txt", "data\\output.txt");
    printf("saved!\n");
    printf("*******************************\n\n");
}
void check()
{
    printf("*******************************\n");
    printf("checking correctness...\n");
    try
    {
        ftc::Checker<double> ck("data\\in.txt");
        ck.check("data\\output.txt", std::cout);
    }
    catch (ftc::Error e)
    {
        e.print_error();
    }
    printf("*******************************\n\n");
}
void op()
{
    printf("*******************************\n");
    printf("Swap-optimizaion starts!\n");
    string origin = "data\\in.txt", sub = "data\\output.txt";
    swap_optimization op(origin, sub);
    op.optimize();
    printf("*******************************\n\n");
}
void calc_path()
{
    printf("*******************************\n");
    printf("print the nodes connected with the input\n");
    printf("input the node:");
    int ver;
    cin >> ver;
    Graph_merge m1("data\\in.txt", "data\\output.txt");
    path p1(m1);
    p1.print_node_connected(ver);

    printf("\nprint the shortest path between the nodes input\n");
    printf("input the nodes:");
    int ver1, ver2;
    cin >> ver1 >> ver2;
    Graph_merge m2("data\\in.txt", "data\\output.txt");
    path p2(m2);
    p2.print_shortest_path(ver1, ver2);
    printf("*******************************\n\n");
}