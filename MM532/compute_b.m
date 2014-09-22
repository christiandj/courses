function b = compute_b(nx, ny)
% Preallocate a vector b
b = zeros(nx * ny, 1);
% Loop through b
for r = 1:ny
	for c = 1:nx
		b(c + (r - 1) * nx) = rho(2 * c / nx, r / ny);
	end
end
