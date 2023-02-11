function [SSE] = CompareLinkageData(params, L, thetaS, thetaL)

thetaL_theory = ThetaLaunch(L, thetaS, params);
SSE = SumOfSquaredErrors(thetaL_theory, thetaL);

end