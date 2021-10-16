#include <vector>
#include <queue>
#include <utility>

using namespace std;


class Hunting{
    private:
        bool found;
        double pathCost;
        vector<vector<double> > mapaNew;
        vector<vector<double> > mapa;
        priority_queue <pair<double,pair<int,int> > > searching;
        pair<int,int> hunter;
        pair<int,int> prey;

    public:
        Hunting(vector<vector<double> >, pair<int,int>, pair<int,int>);
        void A_star();
        void graphCairo();
        double dist_eucl(pair<int,int>);
        void first_search(int,int,int,int);
        void second_search(int,int,int,int);
        void writePath(vector<pair<int,int> >);
};
