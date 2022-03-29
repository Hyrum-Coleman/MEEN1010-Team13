function SSE = SumOfSquaredErrors(x, y)
error = x - y;
errorSquared = error .^ 2;
SSE = sum(errorSquared);
end