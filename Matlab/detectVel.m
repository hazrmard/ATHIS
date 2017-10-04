function [ vel ] = detectVel( f0, f1)
% DETECT computes measure of approach speed
 k = 1;
 vel = k * (f1 - f0);
end

