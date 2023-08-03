clear
clc
 
% 做一个试验数据，半径为1m的圆
x = [];
y = [];
r = 1;
for i=1:100
    x(i) = r * cos(i*2*pi/100);
    y(i) = r * sin(i*2*pi/100);
end
 
a = [x;y]';
figure(1);
title("待识别图形");
plot(a(:,1),a(:,2))
axis equal;
% RANSCA参数
% 迭代次数
iter = 0;
% 查看圆数据的大小
[m,n] = size(a);
% 误差参数
berr = 0.02;
% 拟合参数
bfit = [];
% 内点个数，本来是自己带入，但是我这里设置了自动的
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
figure(2);
title("识别出的圆形");
para = [p(1)-r, p(2)-r, 2*r, 2*r];
rectangle('Position', para, 'Curvature', [1 1]); 
axis equal;
 
function [R,P0] = ThreePoint2Circle(P1, P2, P3)
%% 求圆心和半径，三个点可以求圆心和半径
    x1 = P1(1);    x2 = P2(1);    x3 = P3(1);
    y1 = P1(2);    y2 = P2(2);    y3 = P3(2);
    z1 = x2^2 + y2^2 - x1^2 - y1^2;
    z2 = x3^2 + y3^2 - x1^2 - y1^2;
    z3 = x3^2 + y3^2 - x2^2 - y2^2;
    A = [(x2-x1), (y2-y1); (x3-x1), (y3-y1); (x3-x2), (y3-y2)];
    B = 0.5*[z1;  z2;  z3];
    P0 = (A'*A)\A'*B;
    R1 = sqrt( (P0(1) - P1(1))^2 + (P0(2) - P1(2))^2 );
    R2 = sqrt( (P0(1) - P2(1))^2 + (P0(2) - P2(2))^2 );
    R3 = sqrt( (P0(1) - P3(1))^2 + (P0(2) - P3(2))^2 );
    R = (R1 + R2 + R3)/3;
    P0 = P0';
end