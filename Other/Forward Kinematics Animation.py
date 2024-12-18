import math
import matplotlib.pyplot as plt
import numpy as np

L1 = 4.4
L2 = 6.2

def servo_to_physical_angle(servo_angle):
    physical_angle = -0.857 * servo_angle + 119.98
    return physical_angle

def calculate_leg_endpoint(hip_angle_deg, knee_angle_deg, L1, L2):
    hip_angle_rad = math.radians(hip_angle_deg)
    knee_angle_rad = math.radians(servo_to_physical_angle(knee_angle_deg))
    x = round((L1 + L2 * math.cos(knee_angle_rad)) * math.cos(hip_angle_rad), 2)
    y = round((L1 + L2 * math.cos(knee_angle_rad)) * math.sin(hip_angle_rad), 2)
    z = round(L2 * math.sin(knee_angle_rad), 2)
    return x, y, z

def rotate_points(angle,x,y):
    rotation_angle = math.radians(angle)
    x_rotated = x * math.cos(rotation_angle) - y * math.sin(rotation_angle)
    y_rotated = x * math.sin(rotation_angle) + y * math.cos(rotation_angle)
    return x_rotated, y_rotated 


square_size = 9
half_size = square_size / 2
bottom_z = -2.69
top_square = [[half_size, half_size, 0],[half_size, -half_size, 0],[-half_size, -half_size, 0],[-half_size, half_size, 0]]
bottom_square = [[half_size, half_size, bottom_z],[half_size, -half_size, bottom_z],[-half_size, -half_size, bottom_z],[-half_size, half_size, bottom_z]]
rotation_theta = np.radians(45)
rotation_matrix = np.array([[np.cos(rotation_theta), -np.sin(rotation_theta), 0],[np.sin(rotation_theta), np.cos(rotation_theta), 0],[0, 0, 1]])
rotated_top = [np.dot(rotation_matrix, point) for point in top_square]
rotated_bottom = [np.dot(rotation_matrix, point) for point in bottom_square]
top_x = [p[0] for p in rotated_top]
top_y = [p[1] for p in rotated_top]
top_z = [p[2] for p in rotated_top]
bottom_x = [p[0] for p in rotated_bottom]
bottom_y = [p[1] for p in rotated_bottom]
bottom_z = [p[2] for p in rotated_bottom]

plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

while True:
    for hip_angle in range(0, 181,20):
        for knee_angle in range(0, 181,20):
            ax.clear()
            ax.text(0, 0, 0, '1', fontsize=10)
            x, y, z = calculate_leg_endpoint(hip_angle, knee_angle, L1, L2)
            x, y, z = x, y, -z
            hip_angle_rad = math.radians(hip_angle)
            joint_x, joint_y = (L1 * math.cos(hip_angle_rad), L1 * math.sin(hip_angle_rad))
            rotated_xa, rotated_ya = rotate_points(-90, x, y)
            rotated_xj, rotated_yj = rotate_points(-90, joint_x, joint_y)
            for i in range(4):
                ax.plot([top_x[i], bottom_x[i]], [top_y[i], bottom_y[i]], [top_z[i], bottom_z[i]], color='orange')
                base_x, base_y, base_z = top_x[i], top_y[i], top_z[i]
                if i == 0:
                    xj, yj, xa, ya = joint_x, joint_y, x, y
                elif i == 1:
                    xj, yj, xa, ya = rotated_xj, rotated_yj, rotated_xa, rotated_ya
                elif i == 2:
                    xj, yj, xa, ya = -joint_x, -joint_y, -x, -y
                elif i == 3:
                    xj, yj, xa, ya = -rotated_xj, -rotated_yj, -rotated_xa, -rotated_ya
                x_coords = [base_x, base_x + xj, base_x + xa]
                y_coords = [base_y, base_y + yj, base_y + ya]
                z_coords = [base_z, base_z, z] 
                ax.plot(x_coords, y_coords, z_coords, color='black', linewidth=2)
                ax.scatter(x_coords[0], y_coords[0], z_coords[0], color='red', s=25)
                ax.scatter(x_coords[1], y_coords[1], z_coords[1], color='red', s=25)
                ax.scatter(x_coords[-1], y_coords[-1], z_coords[-1], color='blue', s=10)
            ax.plot_trisurf(top_x, top_y, top_z, color='orange',alpha=0.6)
            ax.plot_trisurf(bottom_x, bottom_y, bottom_z, color='orange',alpha=0.6)

            
            ax.set_xlabel('X Axis')
            ax.set_ylabel('Y Axis')
            ax.set_title('Robot')
            ax.set_box_aspect([1, 1, 1])
            ax.grid(True)
            ax.set_xlim((-25, 25))
            ax.set_ylim((-25, 25))
            ax.set_zlim((-25, 25))
            ax.set_aspect('equal')
            plt.show()
            plt.pause(0.001)