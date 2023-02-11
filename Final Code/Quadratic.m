% Hyrum Coleman, u365193, ME EN 1010, HW5b
function [posRoot, negRoot] = Quadratic(a, b, c)
% Calculates the roots of a function
% Inputs: a -- vector constant in front of the x^2 term  
%         b -- vector constant in front of the x term
%         c -- vector constant value
% Output: posRoot -- positive root with the + or -
%         negRoot -- negative root
if((b .^ 2) - (4 .* a .* c) >= 0 ) % setting up if statement, if the function will output complex roots, then the program is aborted, it'll only output if the roots are real.
    posRoot = (-b + sqrt(b.^2 - 4 .* a .* c)) ./ (2 .* a);
    negRoot = (-b - sqrt(b.^2 - 4 .* a .* c)) ./ (2 .* a);
else
    error("Roots are complex, aborting program") % error statement throught the error function
end
end