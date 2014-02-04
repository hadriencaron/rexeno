%% Cette procedure sert à lancer le processus de calibration

cd /home/hadrien/.rexeno/Matlab/
addpath(genpath('/home/hadrien/.rexeno/Matlab'));
%load_my_functions;

[a b] = CreateCalib('/home/hadrien/.rexeno/Dev/ai0');
[a2 b2] = CreateCalibIntegration('/home/hadrien/.rexeno/Dev/ai1', b);

%save 'toto.txt' -ASCII 'a' 'b'
disp(a)
disp(b)

exit
