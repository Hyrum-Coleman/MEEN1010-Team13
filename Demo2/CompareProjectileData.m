function [SSE] = CompareProjectileData(velCoeffs, d, exp_thetaL, exp_xLand)
theory_xLand = LandingDistance(d, velCoeffs, exp_thetaL);
SSE = SumOfSquaredErrors(exp_xLand, theory_xLand);
end