# Hybrid A Star
![GIF](images/gif.gif)

## 1. Introduce

Hybrid A Star achieved very good results in the DARPA Urban Challenge. And after years of development, the algorithm has been verified to perform very well in parking and some autonomous driving environments without driving rules.

This code is based on the works of https://github.com/zm0612/Hybrid_A_Star and https://github.com/teddyluo/hybrid-a-star-annotation.
See [bilibili](https://www.bilibili.com/video/BV14y411a77H/?spm_id_from=333.999.0.0)

## 2. Prerequisites

(1). **C++17 Compiler**

(2). **ROS2 Humble** (or later): This package has been migrated to ROS2

```shell
# Install ROS2 Humble (if not already installed)
# Follow instructions at: https://docs.ros.org/en/humble/Installation.html

# Install required ROS2 packages
sudo apt-get install ros-humble-nav-msgs ros-humble-geometry-msgs ros-humble-sensor-msgs ros-humble-visualization-msgs
sudo apt-get install ros-humble-tf2 ros-humble-tf2-ros ros-humble-tf2-geometry-msgs
sudo apt-get install ros-humble-nav2-map-server
```

(3). **Eigen 3**

```shell
sudo apt-get install libeigen3-dev
```

(4).  **glog**

```shell
sudo apt-get install libgoogle-glog-dev
```

(5).  **osqp**

```shell
git clone --recursive -b release-0.6.3 https://github.com/oxfordcontrol/osqp.git
cd osqp
mkdir build && cd build
cmake .. 
make
sudo make install
```

## 3. Build 

```shell
# Create ROS2 workspace
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src

# Clone the repository
git clone https://github.com/zsanmu52/Hybrid_A_Star-and-mpc_controller.git

# Build
cd ~/ros2_ws
colcon build --packages-select hybrid_a_star_zm0612

# Source the workspace
source install/setup.bash
```

## 4. Run

```shell
# Source the workspace
source ~/ros2_ws/install/setup.bash

# Run Hybrid A Star
ros2 run hybrid_a_star_zm0612 hybrid_a_star_zm0612

# In a separate terminal, you can publish the map and set start/goal poses
# The starting point is selected by publishing to /initialpose topic
# The goal point is selected by publishing to /goal_pose topic
```

**Note:** The launch file needs to be migrated to ROS2 format separately. For now, run the node directly and use RViz2 to visualize and interact.

**The starting point is selected by the `2D Pose Estimate` in RViz2, and the end point is selected by the `2D Goal Pose`.**

> I provide multiple maps, you just need to modify the variable image in `hybrid_a_star/maps/map.yaml` file. The map resolution can be changed.

> If your start and end points are too close to obstacles, the collision detection mechanism may be triggered and no feasible paths will be searched and displayed

> You can change the algorithm parameters by using ROS2 parameter system (ros2 param set).

## 5. ROS2 Migration Notes

This package has been migrated from ROS1 to ROS2. Key changes include:

### API Changes:
- `ros::NodeHandle` → `rclcpp::Node::SharedPtr`
- `ros::Publisher` → `rclcpp::Publisher<MessageType>::SharedPtr`
- `ros::Subscriber` → `rclcpp::Subscription<MessageType>::SharedPtr`
- `ros::Time` → `rclcpp::Time`
- `tf` → `tf2` with `tf2_geometry_msgs`
- Message types: `geometry_msgs::PoseStamped` → `geometry_msgs::msg::PoseStamped`

### Parameter System:
- Parameters now use namespaced format: `planner.steering_angle` instead of `planner/steering_angle`
- Parameters must be declared before use with `declare_parameter()`
- Values retrieved with `get_parameter().as_<type>()`

### Build System:
- `catkin` → `ament_cmake`
- `catkin_make` → `colcon build`
- Package format updated from 2 to 3

### Topic Changes:
- Goal pose topic changed from `/move_base_simple/goal` to `/goal_pose` for ROS2 compatibility

## 6. Bug 报告和改进建议 | Bug Reports and Improvement Suggestions

当前程序可能还存在一些 Bug 或不稳定的地方。如果你在使用过程中发现了问题，或者有更好的解决方案，请不要犹豫，通过以下方式告诉我：

The current program may still have some bugs or instability issues. If you encounter any problems during use or have a better solution, please don't hesitate to let me know through the following methods:

1. **提交 Issue | Submit an Issue**: 你可以在 [Issues 页面] 提交一个新的 Issue，描述你遇到的问题或改进建议。

   You can submit a new issue on the [Issues page], describing the problem you've encountered or your improvement suggestions.

2. **Pull Request | Pull Request**: 如果你已经有了解决方案，可以直接 Fork 这个仓库并提交 Pull Request，我会尽快进行审核和合并。

   If you already have a solution, you can directly Fork this repository and submit a Pull Request. I will review and merge it as soon as possible.

## 7. References

(1). [Practical Search Techniques in Path Planning for Autonomous Driving](https://ai.stanford.edu/~ddolgov/papers/dolgov_gpp_stair08.pdf)

(2). [The Bresenham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)

(3). [A simple car](http://planning.cs.uiuc.edu/node658.html)
