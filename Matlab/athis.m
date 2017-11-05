% This is a protptype demonstration of Approaching Traffic Haptic
% Information System (ATHIS)

FNAME = 'C:\Users\Ibrahim\Downloads\traffic.wav';
SAMPLESIZE = 1e-1;      % length of audio sample (in seconds)
PERIOD = 5e-1;          % interval between audio samples (in seconds)
CHANNELS = 1;           % number of channels in file (1 or 2)
WINDOWSIZE = 30;         % # of seconds' readings to plot at once

info = audioinfo(FNAME);
% T = info.Duration;      % total time (in secods)
T=30;
Fs = info.SampleRate;
N = floor(T / PERIOD);

amp = zeros(1, CHANNELS);
freq = zeros(1, CHANNELS);
ampprev = zeros(1, CHANNELS);
freqprev = zeros(1, CHANNELS);
y0 = audioread(FNAME, [1, Fs * SAMPLESIZE]);
for j = 1:CHANNELS 
    [ampprev(:, j), freqprev(:, j)] = sense(y0(:, j));
end
vels = zeros(1, ceil(WINDOWSIZE / PERIOD));
times = zeros(1, ceil(WINDOWSIZE / PERIOD));
figure;
for i = 2:N
    range = double(uint32([Fs * (i-1) * PERIOD + 1, Fs * ((i-1) * PERIOD + SAMPLESIZE)]));
    y = audioread(FNAME, range);
    for j = 1:CHANNELS 
        [amp(:, j), freq(:, j)] = sense(y(:, j));
        vel = detectVel(freqprev(:, j), freq(:, j));
        vels = [vels(2:end) vel];
        times = [times(2:end) i*PERIOD];
        plot(times, vels); xlabel('Time'); ylabel('Approach Speed Measure');title(strcat('Duty cycle: ', sprintf('%5.2f', SAMPLESIZE/PERIOD)));
    end
    pause(PERIOD);
    ampprev = amp;
    freqprev = freq;
end