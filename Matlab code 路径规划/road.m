%Step1:处理激光雷达扫描数据，绘制二维坐标系地图

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
figure(1);
scatter(x4,y4,1);
hold on
axis equal
axis( [ -3, 22, -3, 22 ] )

%Step2:利用RANSAC算法识别直线和圆

%(1)圆的识别
a = [x4,y4];
% RANSCA参数：
% 迭代次数
iter = 0;
% 查看圆数据的大小
[m,n] = size(a);
% 误差参数
berr = 0.02;
% 拟合参数
bfit = [];
% 内点个数为点数的1/3
t = floor(m/3);
% 开始循环迭代
while iter<100
    % 随机挑选三个点，三个点不重复
    % 拟合圆最少需要三个点，拟合直线最少需要两个
    % ran为索引编号
    ran = randperm(m,3)';
    % b为索引得到的点
    b = a(ran,:);
    % 根据随机得到的三个点，计算圆的半径和圆心
    [r1,p1] = ThreePoint2Circle(b(1,1:2), b(2,1:2), b(3,1:2));
    % 选择除了随机得到的三个点外的其他点
    c = setdiff(a,b,"rows");
    % 计算每个点到圆心的距离dis
    dis = sqrt(sum((c(:,1:2)-p1).^2,2));
    % 计算 dis和拟合圆的误差
    res = dis - r1;
    % 选择小于误差的点，进入到内点中
    d = c(res<berr,:);
    len = length(d(:,1));
    % 判断内点数量是否满足条件
    if len > t
        % 满足条件时，多点拟合圆，这里用平均值计算圆心
        p = mean(d);
        r = mean(sqrt(sum((d(:,1:2)-p(:,1:2)).^2,2)));
        % 多点拟合的圆和随机点拟合的圆的误差
        err = sqrt(sum((p-p1).^2))+sqrt((r-r1)^2);
        % 如果误差满足条件，则可以结束循环
        % 不满足则继续
        if err < berr
            bfit = [p,r];
            berr = err;
            break
        else
            iter = iter+1;
            continue
        end
    else
        iter = iter+1;
    end
end
%绘图
para = [p(1)-r, p(2)-r, 2*r, 2*r];
rectangle('Position', para, 'Curvature', [1 1]); 

%（2）直线的识别
iter = 100;
data1=transpose(x4);
data2=transpose(y4);
data=[data1;data2];
for t=1:10
 number = size(data,2); % 总点数
 bestParameter1=0; bestParameter2=0; % 最佳匹配的参数
 sigma = 1;
 pretotal=0;     %符合拟合模型的数据的个数
 for i=1:iter
 %随机选择两个点
     idx = randperm(number,2); 
     sample = data(:,idx); 
     %拟合直线方程 y=kx+b
     line = zeros(1,3);
     x = sample(:, 1);
     y = sample(:, 2);
     k=(y(1)-y(2))/(x(1)-x(2));      %直线斜率
     b = y(1) - k*x(1);
     line = [k -1 b];
     mask=abs(line*[data; ones(1,size(data,2))]);    %求每个数据到拟合直线的距离
     total=sum(mask<sigma);              %计算数据距离直线小于一定阈值的数据的个数
     if total>pretotal            %找到符合拟合直线数据最多的拟合直线
         pretotal=total;
         bestline=line;          %找到最好的拟合直线
    end  
 end
%显示符合最佳拟合的数据
 mask=abs(bestline*[data; ones(1,size(data,2))])<sigma;    
 hold on;
 k=1;
 index=[];
 for i=1:length(mask)
    if mask(i)
        inliers(1,k) = data(1,i);
        k=k+1;
        index=[index i];
    end
 end
 %删除完成拟合的点以进行下一次拟合
 for i=1:length(index)
    data(:,index(i))=[];
    for j=1:length(index)
        if(index(j)>index(i))
            index(j)=index(j)-1;
        end
    end
 end
 % 绘制最佳匹配曲线
 bestParameter1 = -bestline(1)/bestline(2);
 bestParameter2 = -bestline(3)/bestline(2);
 xAxis = min(inliers(1,:)):max(inliers(1,:));
 yAxis = bestParameter1*xAxis + bestParameter2;
 plot(xAxis,yAxis,'r-','LineWidth',2);
end

%Step3:通过识别得到的障碍物和目标坐标建立势场

v=-2:1:22;
[x,y]=meshgrid(v);
F=log(sqrt((x-4.75).^2+(y-12.5).^2))+log(sqrt((x-12).^2+(y-7.6).^2))+log(sqrt((x-11.2).^2+(y-13).^2))-5*log(sqrt((x-16.5).^2+(y-18.5).^2));
[px,py]=gradient(F,1,1);
contour(x,y,F);
hold on;
title('人工势场法路径规划');
quiver(x,y,px,py,0);
figure(2);
surf(x,y,-F);

%Step4:通过人工势场法确定最优路径

axis([-3 22 -3 22]);
begin=[0;0]%起始点坐标
over=[16.5;18.5];%目标点坐标
figure(1);
hold on;
plot(begin(1),begin(2),'*b','MarkerSize',10);
plot(over(1),over(2),'*b','MarkerSize',10);
obstacle=[4.75,12,11.35;12.75,7.5,12];%障碍物坐标
point= path_plan(begin,over,obstacle);