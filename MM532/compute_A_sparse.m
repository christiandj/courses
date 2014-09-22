function A = compute_A_sparse(nx, ny)
% Generates a sparse matrix A which is discretized Laplace operator.
% nx is the number of points in discretization into direction x.
% ny is the number of points in discretization into direction y.

% Distance between the points in the horizontal direction 
hx = 2 / (nx + 1);
% Distance between the points in the vertical direction
hy = 1 / (ny + 1);

H = -2 / hx^2 - 2 / hy^2;

% Setup a submatrix b, which is used as diagonal elements of the matrix A
B = sparse(1:nx, 1:nx, 1) * H; % First diagonal
B = B + sparse(1:nx-1, 2:nx, 1, nx, nx) / hx^2 + ...
    sparse(2:nx, 1:nx-1, 1, nx, nx) / hx^2; % Then off-diagonal

% Setup the matrix A
A = -kron(sparse(1:ny, 1:ny, 1, ny, ny), B) - ... 
    kron(sparse(1:ny-1, 2:ny, 1, ny, ny), sparse(1:nx, 1:nx, 1, nx, nx) / hy^2) - ...
    kron(sparse(2:ny, 1:ny-1, 1, ny, ny), sparse(1:nx, 1:nx, 1, nx, nx) / hy^2);