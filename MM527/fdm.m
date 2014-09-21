% Example 1: Stable choice
% w = fdm(2.0, 0.025, 0.05)
% Example 2: Unstable choice
% w = fdm(2.0, 0.032, 0.05)
% Example 3: Satisfied CFL condition
% w = fdm(6.0, 0.008, 0.05)

function w = fdm(c,k,h)

% Some definitions
sigma = c*k/h;
x = h:h:1.0-h;
t = k:k:1.0;
m = size(x,2);
n = size(t,2);
f = sin(pi*x);

% Set up the matrix A
A = (2.0-2.0*sigma^2)*eye(m);
A = A+diag(sigma^2*ones(m-1,1),1);
A = A+diag(sigma^2*ones(m-1,1),-1);

% Some steps
w = zeros(m,m+2);
w(:,1) = 0.5*A*f';
w(:,2) = w(:,1);
for j = 2:n-1
    w(:,j+1) = A*w(:,j)-w(:,j-1);
end

% Draw a wireframe mesh
mesh(t,x,w)
xlabel('time')
ylabel('space')
axis([0 1 0 1 -1 2])
