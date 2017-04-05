function [ a ] = widrow_hoff(Y , a, b, lr, theta)
n = size(Y,1);
iterations = 0;
all_pos =0;
while((all_pos==0)&&(iterations<1000000))
    iterations = iterations+1; 
    fprintf('iteration=%d\n',iterations);
    all_pos = 1;
    for i = 1:n
            if(isnan(b-Y(i,:)*a')||isinf(b-Y(i,:)*a'))
               all_pos=1
               break
            end
            delta = (lr/iterations)*(Y(i,:))*((b-Y(i,:)*a'));
            %a = a + delta;
            if(delta > theta) 
                a = a + delta;                
                %disp(delta)
                all_pos = 0;
            end
            %disp(a);
    end
    if(all_pos==1)
    disp(a);
    end
end

w1 = [2 7; 8, 1; 7, 5; 6, 3; 7, 8; 5, 9; 4, 5];
w2 = [4, 2; -1, -1; 1, 3; 3, -2; 5, 3.25; 2, 4; 7, 1 ];
w1_ = [ones(size(w1,1),1) w1];
w2_ = [ones(size(w2,1),1) w2];
w2_ = -w2_;



Y = [w1_;w2_];
a = [-10  1 1.5 ];
% ground truth vector
b = 0.01;
theta = 0.000001;
color_mat = [ones(size(w1,1)) zeros(size(w2,1))];
O = widrow_hoff(Y,a,b,0.001,theta);



x = min([w1(:,1) ; w2(:,1)]):max([w1(:,1) ; w2(:,1)]);
y = -(O(1) + (O(2)*x))/O(3);
plot(w1(:,1),w1(:,2), 'g.',w2(:,1),w2(:,2), 'rs', x, y); 
