function [ amp, freq ] = sense( sample )
%SENSE cleans and processes raw audio data into amplitudes and frequencies.
    freq = fftshift(fft(sample));
    freq = freq(floor(end/2):end);
    freq = mean(abs(freq));
    amp = mean(sample);
end

