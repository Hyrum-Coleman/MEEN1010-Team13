function [centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imageArray, targetRGB)
for i=1:6
    [centroidRowVec(i), centroidColVec(i), imageArray] = FindTargetCentroid(imageArray, targetRGB);
end
end