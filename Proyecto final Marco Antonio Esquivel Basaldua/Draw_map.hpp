#include <vector>
using namespace std;


class Draw_map{
    private:
        int obsts_0, obsts_1, obsts_15, spaces;
        vector<vector<double> > mapa;

    public:
        Draw_map(int,int,int,int);
        void fillMapa();
        void graphCairo();
        vector<vector<double> > get_mapa();
};
