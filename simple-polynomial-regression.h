#ifndef SIMPLE_POLYNOMIAL_REGRESSION
#define SIMPLE_POLYNOMIAL_REGRESSION

#include <vector>
#include <chrono>

#include "../graph.h"
#include "../orthogonal polynomials/generatePolynomials.h"

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
	Vec polynomial;

	void fit(const Vec& X, const Vec& Y, int degree = 1) {
		Mat polynomials = getOrthogonalPolynomials(degree + 1, X);
		Vec multipliers = leastSquares(X, Y, polynomials);

		// combine all polynomials with it's weights into one (makes it easier to evaluate them)
		polynomial.resize(degree + 1, 0);
		for (size_t i = 0; i < polynomials.size(); ++i) {
			for (size_t j = 0; j < polynomials[i].size(); ++j) {
				polynomial[j] += polynomials[i][j] * multipliers[i];
			}
		}
	}

	double predict(double x) {
		return evaluatePolynomial(polynomial, x);
	}

};


#endif
