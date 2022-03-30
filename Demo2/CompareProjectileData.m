function [SSE] = CompareProjectileData(v0, d, exp_thetaL, exp_xLand)
theory_xLand = LandingDistance(d, v0, exp_thetaL);
SSE = SumOfSquaredErrors(exp_xLand, theory_xLand);
end