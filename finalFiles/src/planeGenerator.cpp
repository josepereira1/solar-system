#include <Point.h>
#include <vector>

using namespace std;

vector<TAD_POINT> getPointsOfPlane(int side) {
    float c = side / 2.0;
    vector<TAD_POINT> l;
        
    l.push_back(POINT(c,0.0,-c));
    l.push_back(POINT(-c,0.0,-c));
    l.push_back(POINT(-c,0.0,c));
    l.push_back(POINT(-c,0.0,c));
    l.push_back(POINT(c,0.0,c));
    l.push_back(POINT(c,0.0,-c));

    return l;
}
