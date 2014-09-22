function x = myGMRES(A, b, m)
	% Get the size of the square matrix A
	[n, ~] = size(A);
	% Setting up initial guess
	x = zeros(n, 1);
	% Calculate residual
	residual = b - A * x;
	% The tolerance
	tolerance = 1e-5;
	% Initialize a vector of residuals
	residuals = [];
	% Until convergence is reached
	while norm(residual) > tolerance
		% Householder Arnoldi step
		[H, w] = householderArnoldi(A, m, residual);
		% Solve least square problem
		beta = H(1, 1);
		Hbar = H(1:m+1, 2:m+1);
		[newResidual, y] = argMin(m, beta, Hbar);
		% Add a new residual to the vector of residuals
		residuals = [residuals, newResidual];
		% Compute z
		z = zeros(n, 1);
		for i = m:-1:1
			z(i) = z(i) + y(i);
			z = z - 2 * w(:, i) * (w(:, i)' * z);
		end
		% Compute x
		x = x + z;
		% Calculate residual
   		residual = b - A * x;
	end
	% Plot the norm of the residuals
	plot(1:length(residuals), log(norm(residuals)))
	mytitle = sprintf('For m = %d', m);
	title(mytitle);
	xlabel('iteration number');
	ylabel('log(||b - Ax||)');
	grid on;
	hold on;
	% Add the linear fit to the plot
	myfit = polyfit(1:length(residuals), log(residuals), 1);
	plot(myfit(1, 1) * (1:length(residuals)) + myfit(1, 2), 'red');
	fprintf('The slope of the linear fit is %d\n', myfit(1, 1));
	hold off;
	
	% Householder Arnoldi from the weekly exercise
	function [H, w] = householderArnoldi(A, m, residual)
		[n, ~] = size(A);
		z = residual;
		v2 = z;
		H = zeros(m + 1);
		w = zeros(n, m + 1);
		v = eye(n, m);
		for j = 1:m+1
			v2(1:j-1) = zeros(j - 1, 1);
			v2(j:n) = z(j:n);
			v2(j) = v2(j) + nSign(v2(j)) * norm(v2);
			w(:, j) = v2 / norm(v2);
			H(1:j, j) = z(1:j) - 2 * w(1:j, j) * (w(:, j).' * z);
			if j <= m
				for k = j:-1:1			
					v(:, j) = v(:, j) - 2 * w(:, k) * (w(:, k).' * v(:, j));
				end
				z = A * v(:, j);
				for k = 1:j
					z = z - 2 * w(:, k) * (w(:, k).' * z);
				end
			end
		end
	end
	
	% We do not like zeros
	function s = nSign(x)
		if x >= 0
			s = 1;
		else
			s = -1;
		end
	end
	
	function [residual, y] = argMin(m, beta, Hbar)
		g = eye(m + 1, 1) * beta;
		residual = [];
		for k = 1:m
			omega = eye(m + 1);
			omega(k, k) = Hbar(k, k) / sqrt(Hbar(k, k)^2 + Hbar(k + 1, k)^2);
			omega(k + 1, k + 1) = omega(k, k);
			omega(k + 1, k) = -Hbar(k + 1, k) / (sqrt(Hbar(k, k)^2 + Hbar(k + 1, k)^2));
			omega(k, k + 1) = -omega(k + 1, k);
			Hbar = omega * Hbar;
			g = omega * g;
			% The last element of g is the residual
			residual = [residual, abs(g(k + 1))];
		end
		% We could probably have used back substitution
		y = Hbar(1:m, 1:m)\g(1:m);
	end
	
end