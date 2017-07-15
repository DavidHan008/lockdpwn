% Author: Jonathan Sprinkle
% Compares bag files from several experiments in gazebo using the same
% inputs

%% set up the cell arrays
% bagfiles = cell(2,1);
% ts = cell(2,1);
% complexGazeboInputs/hardLeft-lessbounce1
bagfiles{1} = rosbag('2016-05-24-21-19-08.bag');
bagfiles{2} = rosbag('2016-05-25-14-59-18.bag');
bagfiles{3} = rosbag('2016-05-27-11-36-30.bag');

%% make the cell of titles
titles = cell(2,1);
titles{1} = 'Run 1';
titles{2} = 'Run 2';
titles{3} = 'Run 2';


%% grab data inputs of odometry
for i=1:length(bagfiles)
    bagselect = select(bagfiles{i}, 'Topic', '/azcar_sim/odom');
    ts{i} = timeseries(bagselect, 'Pose.Pose.Position.X', 'Pose.Pose.Position.Y');
end

%% grab data inputs of cmd_vel_safe
for i=1:length(bagfiles)
    bagselect = select(bagfiles{i}, 'Topic', '/azcar_sim/cmd_vel_safe');
    cmd_vel{i} = timeseries(bagselect, 'Linear.X', 'Angular.Z');
end


%% look for the "beginning" of interesting data
for i=1:length(bagfiles)
    diffX = find(abs(ts{i}.Data(:,1)-ts{i}.Data(1,1))>0.01);
    diffY = find(abs(ts{i}.Data(:,2)-ts{i}.Data(1,2))>0.01);
    diff{i} = min(diffX(1),diffY(1));
end


%% produce a plot of data
figure
hold on

for i=1:length(bagfiles)
    plot(ts{i}.Data(diff{i}:end,2),ts{i}.Data(diff{i}:end,1));
end
legend(titles);

% and let's also plot the x/y and the commanded input values in the
% same reference time frame (i.e., subtract away time diffs)
figure
hold on

for i=1:length(bagfiles)
    % the earliest time in this series with interesting data is here
    earliestTime=cmd_vel{i}.Time(diff{i});
    % subtract away the earliest time throughout
    plot(cmd_vel{i}.Time(diff{i}:end,1)-earliestTime,cmd_vel{i}.Data(diff{i}:end,1));
    plot(cmd_vel{i}.Time(diff{i}:end,1)-earliestTime,cmd_vel{i}.Data(diff{i}:end,2));
end
