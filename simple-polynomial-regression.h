#ifndef SIMPLE_POLYNOMIAL_REGRESSION
#define SIMPLE_POLYNOMIAL_REGRESSION

#include <vector>

#include "../graph.h"
#include "../orthogonal-polynomials/generatePolynomials.h"

using namespace std;


// least squares where the polynomial functions must be orthogonal
Vec leastSquares(const Vec& X, const Vec& Y, const Mat& polynomials) {
	Vec m(polynomials.size());

	for (size_t i = 0; i < polynomials.size(); ++i) {
		double a = 0;
		double b = 0;

		for (size_t k = 0; k < X.size(); ++k) {
			double g = evaluatePolynomial(polynomials[i], X[k]);

			a += g * g;
			b += Y[k] * g;
		}

		m[i] = b / a;
	}

	return m;
}


struct PolynomialRegression {
	Mat polynomials;
	Vec multipliers;

	void fit(const Vec& X, const Vec& Y, int degree = 1) {
		polynomials = getOrthogonalPolynomials(degree + 1, X);
		multipliers = leastSquares(X, Y, polynomials);
	}

	double predict(double x) {
		double y = 0;

		for (size_t i = 0; i < polynomials.size(); ++i) {
			y += evaluatePolynomial(polynomials[i], x) * multipliers[i];
		}

		return y;
	}

};


#endif
