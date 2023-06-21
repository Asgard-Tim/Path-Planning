v=-200:2:2200;
[x,y]=meshgrid(v);
F=log(sqrt((x-900).^2+(y-1430).^2))-log(sqrt((x-1250).^2+(y-1050).^2));
[px,py]=gradient(F,1,1);
figure
contour(x,y,F);
hold on;
title('Field & Potencial');
quiver(x,y,px,py,0);
