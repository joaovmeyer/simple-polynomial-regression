#include <iostream>
#include <cmath>

#include "simple-polynomial-regression.h"
#include "../rng.h"

using namespace std;


int main() {

	Graph graph(1100, 750);

	Vec X;
	Vec Y;

	for (double x = -10; x < 10; x += 0.05) {
		double y = std::sin(x);
		y += rng::fromNormalDistribution(0, 0.2); // add noise

		X.push_back(x);
		Y.push_back(y);
	}

	PolynomialRegression model;
    model.fit(X, Y, 11);

	for (size_t i = 0; i < X.size(); ++i) {
		Point p(X[i], Y[i], 2, olc::RED);
		graph.addPoint(p);
	}

	Line l;
	for (double x = X[0] - 2; x < X[X.size() - 1] + 2; x += 0.1) {
		double y = model.predict(x);

		l.addPoint(Point(x, y));
	}
	graph.addLine(l);


	graph.waitFinish();

	return 0;
}
