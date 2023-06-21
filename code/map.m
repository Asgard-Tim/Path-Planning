ans=importdata("data1.txt");
angle=ans(:,1);
angle=angle.*2.*3.1415926./360;
distance=ans(:,2);
[x,y] = pol2cart(angle,distance);
ans1=importdata("data2.txt");
angle1=ans1(:,1);
angle1=angle1.*2.*3.1415926./360;
distance1=ans1(:,2);
[x1,y1] = pol2cart(angle1,distance1);
ans2=importdata("data3.txt");
angle2=ans2(:,1);
angle2=angle2.*2.*3.1415926./360;
distance2=ans2(:,2);
[x2,y2] = pol2cart(angle2,distance2);
ans3=importdata("data4.txt");
angle3=ans3(:,1);
angle3=angle3.*2.*3.1415926./360;
distance3=ans3(:,2);
[x3,y3] = pol2cart(angle3,distance3);
ans5=importdata("data5.txt");
angle5=ans5(:,1);
angle5=angle5.*2.*3.1415926./360;
distance5=ans5(:,2);
[x5,y5] = pol2cart(angle5,distance5);
x4 = [x;x1-100;x2+1850;x3+1400;x5+1500]/100;
y4 = [y;y1+1750;y2+100;y3+1650;y5+1000]/100;
scatter(x4,y4,1);
hold on
axis equal
axis( [ -3, 22, -3, 22 ] )