function out = rho(x, y)
	if 1/3 <= x && x <= 5/3 && y == 1/3
		out = -1; % The segment AB
    elseif 1/3 <= x && x <= 5/3 && y == 2/3
		out = 1; % The segment CD
	else
		out = 0;
	end
end