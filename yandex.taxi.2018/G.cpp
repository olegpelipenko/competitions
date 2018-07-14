
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Ride {
	pair<int, int> begin, end;
	int length;
	//map<int, int> driversDist;
};

struct Driver {
	pair<int, int> p;
	int idx;
};

int Dist(int x1, int x2, int y1, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

vector<int> FindRoutes(vector<Driver>& drivers, vector<Ride>& rides) {
	vector<int> result;

	for (const auto & r : rides) {
		map<int, int> nearestDrivers;
		for (int i = 0; i < drivers.size(); i++) {
			nearestDrivers.insert(
			{ Dist(drivers[i].p.first, r.begin.first, drivers[i].p.second, r.begin.second) + r.length, i });
		}
		const auto& d = drivers[nearestDrivers.begin()->second];
		result.push_back(d.idx);
		drivers.erase(drivers.begin() + nearestDrivers.begin()->second);
	}
	return result;
}


int main(int argc, char ** argv) {
	ifstream input(argv[1]);
	vector<string> vs(3);

	int N;
	input >> N;

	vector<Driver> drivers(N);

	for (uint32_t i = 0; i < N; ++i) {
		int x = 0, y = 0;
		input >> x >> y;
		Driver d;
		d.p = make_pair(x, y);
		d.idx = i;

		drivers[i] = d;
	}
	
	
	vector<Ride> rides(N);

	for (uint32_t i = 0; i < N; ++i) {
		int xBegin = 0, yBegin = 0, xEnd = 0, yEnd;
		input >> xBegin >> yBegin >> xEnd >> yEnd;
		Ride r;
		r.begin = make_pair(xBegin, yBegin);
		r.end = make_pair(yBegin, yEnd);
		r.length = Dist(xBegin, xEnd, yBegin, yEnd);
		rides[i] = r;
	}

	auto result = FindRoutes(drivers, rides);
	for (const auto & r : result) {
		cout << r + 1 << endl;
	}
	
}