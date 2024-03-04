# Simple Polynomial Regression

## The problem

Given a set of m points ((x_1, y_1), ..., (x_m, y_m)) and n polynomials (p_1, ..., p_n) of degrees (0, ..., n - 1), we want to "fit" the weighted sum of those polynomials into the set of points. In other words, we want to minimize the diference between the actual value y_i and the prediction a_1 * p_1(x_i) + ... + a_n * p_n(x_i) = g(x_i). The task is to find (a_1, ..., a_n) that achieves that.

## The solution

The least squares method is designed to do exactly that. If we can define a function that says how wrong a solution a = (a_1, ..., a_n) is, we can minimize this function and we will have our solution. We can express the error function as follows:

E = sum((y_i - g(x_i)) ^ 2) = sum((y_i - (a_1 * p_1(x_i) + ... + a_n * p_n(x_i))) ^ 2)

We can take it's gradient in relation to a and find it's 0, and it will be the minimum of the function:

d/da_j = 2 * sum(y_i - (a_1 * p_1(x_i) + ... + a_n * p_n(x_i)) * -p_j(x_i)) = 0

Sow we have the equations
<pre>
sum(y_1 - (a_1 * p_1(x_1) + ... + a_n * p_n(x_1)) * p_1(x_1)) = 0
                             .
                             .
                             .
sum(y_m - (a_1 * p_1(x_m) + ... + a_n * p_n(x_m)) * p_n(x_m)) = 0
</pre>

Note that if we define the polynomial inner product as <f, g> = sum(f(x_i) * g(x_i)), we can represent this nicely as 
a system Sa = b, where s_ij = <p_i, p_j> and b_i = <f, g_i), where f(x_i) = y_i. We could simply solve this linear system of equations, but it's noticible that if all p_1, ..., p_n are orthogonal between themselves, <p_i, p_j> will be 0 if i != j, and non-zero if i = j, so our system would get much much simpler, having only it's diagonal set, leading for the easy solution of a_i = <f. g_i> / <g_i, g_i>. This is also nicer for numerical stability and it reduces multicolinearity in the model, so it's all great. We can simply apply the Gram-Schmidt method in our polynomials and we got our orthogonal polynomials. Great!
