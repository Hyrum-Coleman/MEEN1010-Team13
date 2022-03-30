% Hyrum Coleman, u1365193, ME EN 1010, HW7

function [xLand] = LandingDistance(d, velCoeffs, thetaL)
% Calculates the landing distance of a particle in projectile motion
% Inputs: d     -- array with all 3 distances in it
%         v0    -- initial velocity
%         theta -- array wit hall the angles
% Output: xLand -- landing distance
g = 9.81; % initializing the gravity constant

[x0, y0] = InitialCoords(d, thetaL); % calling the initial coordinates function
k = velCoeffs(1);
lamda = velCoeffs(2);
v0 = k + lamda * thetaL;
[v0x, v0y] = InitialVelocityComponents(v0, thetaL); % calling the inital velocity components function
[~, negRoot] = Quadratic(-g/2, v0y, y0); % performing the quadratic formula
    tLand = negRoot; % It also checks to make sure the function is pulling the larger time value in case both roots are positive

xLand = x0 + (v0x .* tLand); % defines the output as xLand and finishes the function

if(nargout == 0)
    plot(thetaL, xLand, 'b');
    title('Ping Pong Ball Projectile Data');
    xlabel('Launch Angle [deg]');
    ylabel('Horizontal Distance Traveled');
end

end