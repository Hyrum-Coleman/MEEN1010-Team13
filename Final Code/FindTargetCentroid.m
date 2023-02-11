function [centroidRow, centroidCol, modImage] = FindTargetCentroid(imageArray, targetRGB)

redLayer = imageArray(:, :, 1);
greenLayer = imageArray(:, :, 2);
blueLayer = imageArray(:, :, 3);


logArray = ((redLayer == targetRGB(1)) & (greenLayer == targetRGB(2)) & (blueLayer == targetRGB(3)));
[matchRows, matchCols] = find(logArray);

firstMatchRow = matchRows(1);
firstMatchCol = matchCols(1);

[rows, cols, colors] = size(imageArray);
for i=firstMatchCol:cols
    if(logArray(firstMatchRow ,i+1) == 0)
        break;
    end
end
lastMatchCol = i;

for j=firstMatchRow:rows
    if(logArray(j+1, firstMatchCol) == 0)
        break;
    end
end
lastMatchRow = j;

centroidCol = (lastMatchCol + firstMatchCol) / 2;
centroidRow = (firstMatchRow + lastMatchRow) / 2;

modImage = imageArray;

modImage(firstMatchRow:lastMatchRow, firstMatchCol:lastMatchCol, :) = 0;


end