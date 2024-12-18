import math
import matplotlib.pyplot as plt
import numpy as np

L1 = 4.4
L2 = 6.2

def servo_to_physical_angle(servo_angle):
    physical_angle = -0.857 * servo_angle + 119.98
    return physical_angle

def physical_to_servo_angle(physical_angle):
    servo_angle = (119.98 - physical_angle) / 0.857
    return round(servo_angle)

def calculate_leg_endpoint(hip_angle_deg, knee_angle_deg, L1, L2):
    hip_angle_rad = math.radians(hip_angle_deg)
    knee_angle_rad = math.radians(servo_to_physical_angle(knee_angle_deg))
    x = round((L1 + L2 * math.cos(knee_angle_rad)) * math.cos(hip_angle_rad), 2)
    y = round((L1 + L2 * math.cos(knee_angle_rad)) * math.sin(hip_angle_rad), 2)
    z = round(L2 * math.sin(knee_angle_rad), 2)
    return x, y, z

def inverse_kinematics(x, y, z, L1, L2):
    x, y, z = round(x, 2), round(y, 2), round(z, 2)
    d = math.sqrt(x**2 + y**2)
    r = math.sqrt(d**2 + z**2)
    theta1 = math.atan2(y, x)
    hip_angle_deg = math.degrees(theta1)
    if r < abs(L1 - L2) or r > (L1 + L2):
        raise ValueError("Target point is out of reach for the given arm dimensions.")
    cos_phi = (L1**2 + r**2 - L2**2) / (2 * L1 * r)
    cos_phi = max(min(cos_phi, 1), -1)
    phi = math.acos(cos_phi)
    alpha = math.atan2(z, d)
    hip_angle_adjusted_deg = math.degrees(alpha - phi)
    hip_servo_angle = hip_angle_deg + hip_angle_adjusted_deg
    cos_theta2 = (L1**2 + L2**2 - r**2) / (2 * L1 * L2)
    cos_theta2 = max(min(cos_theta2, 1), -1)
    theta2 = math.acos(cos_theta2)
    knee_physical_angle_deg = 180 - math.degrees(theta2)
    knee_servo_angle = physical_to_servo_angle(knee_physical_angle_deg)
    return round(hip_servo_angle), round(knee_servo_angle)

def rotate_points(angle,x,y):
    rotation_angle = math.radians(angle)
    x_rotated = x * math.cos(rotation_angle) - y * math.sin(rotation_angle)
    y_rotated = x * math.sin(rotation_angle) + y * math.cos(rotation_angle)
    return x_rotated, y_rotated 

possible_points = [{}, {}, {}, {}]
for i in range(181):
    for j in range(181):
        x, y, z = calculate_leg_endpoint(i,j, L1, L2)
        possible_points[0][(i, j)] = (x, y, -z)
        possible_points[1][(i, j)] = (y, x, -z)
        possible_points[2][(i, j)] = (-x, -y, -z)
        possible_points[3][(i, j)] = (-y, -x, -z)

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

while True:
    hip_servo_angle, knee_servo_angle = map(int, input("Enter Angles: Hip,Knee: ").replace(" ", "").split(","))
    x, y, z = calculate_leg_endpoint(hip_servo_angle, knee_servo_angle, L1, L2)

    print(f"x: {x}cm        ",f"Hip : {hip_servo_angle}°")
    print(f"y: {y}cm        ",f"Knee: {knee_servo_angle}°")
    print(f"z: {z}cm        ","\n")

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x, y, z = x, y, -z
    hip_angle_rad = math.radians(hip_servo_angle)
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
        points = list(possible_points[i].values())
        xp, yp, zp = zip(*points)
        ax.scatter(xp + base_x, yp + base_y, zp + base_z, color='green', alpha=0.01, marker='o', edgecolor='none')
    ax.plot_trisurf(top_x, top_y, top_z, color='orange',alpha=0.6)
    ax.plot_trisurf(bottom_x, bottom_y, bottom_z, color='orange',alpha=0.6)

    ax.view_init(elev=90, azim=0)
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