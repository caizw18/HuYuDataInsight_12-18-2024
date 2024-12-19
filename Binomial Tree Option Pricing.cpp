#include <vector>
#include <cmath>

double binomialOptionPrice(double S, double K, double r, double T, double sigma, int steps, bool isCall) {
    double dt = T / steps, u = exp(sigma * sqrt(dt)), d = 1 / u;
    double p = (exp(r * dt) - d) / (u - d), discount = exp(-r * dt);

    std::vector<double> prices(steps + 1), optionValues(steps + 1);
    for (int i = 0; i <= steps; ++i) prices[i] = S * pow(u, steps - i) * pow(d, i);

    for (int i = 0; i <= steps; ++i) optionValues[i] = isCall ? std::max(0.0, prices[i] - K) : std::max(0.0, K - prices[i]);

    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            optionValues[i] = discount * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);
        }
    }

    return optionValues[0];
}