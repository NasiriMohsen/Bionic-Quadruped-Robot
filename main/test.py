import math
import matplotlib.pyplot as plt
import math
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



while True:
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    square_size = 9
    half_size = square_size / 2
    bottom_z = -2.69

    # Define vertices for the top and bottom faces
    top_square = [
        [half_size, half_size, 0],
        [half_size, -half_size, 0],
        [-half_size, -half_size, 0],
        [-half_size, half_size, 0]
    ]

    bottom_square = [
        [half_size, half_size, bottom_z],
        [half_size, -half_size, bottom_z],
        [-half_size, -half_size, bottom_z],
        [-half_size, half_size, bottom_z]
    ]

    # Rotate the vertices
    theta = np.radians(45)
    rotation_matrix = np.array([
        [np.cos(theta), -np.sin(theta), 0],
        [np.sin(theta), np.cos(theta), 0],
        [0, 0, 1]
    ])

    rotated_top = [np.dot(rotation_matrix, point) for point in top_square]
    rotated_bottom = [np.dot(rotation_matrix, point) for point in bottom_square]

    # Extract x, y, z coordinates for plotting
    top_x = [p[0] for p in rotated_top]
    top_y = [p[1] for p in rotated_top]
    top_z = [p[2] for p in rotated_top]

    bottom_x = [p[0] for p in rotated_bottom]
    bottom_y = [p[1] for p in rotated_bottom]
    bottom_z = [p[2] for p in rotated_bottom]

    # Connect top and bottom faces
    for i in range(4):
        ax.plot([top_x[i], bottom_x[i]], [top_y[i], bottom_y[i]], [top_z[i], bottom_z[i]], color='green')

    # Plot top and bottom faces as filled surfaces
    ax.plot_trisurf(top_x, top_y, top_z, color='green', alpha=0.6, shade=True)
    ax.plot_trisurf(bottom_x, bottom_y, bottom_z, color='green', alpha=0.6, shade=True)

    # Connect legs to the cube
    hip_servo_angle, knee_servo_angle = map(int, input("Enter Angles: Hip,Knee: ").replace(" ", "").split(","))
    x, y, z = calculate_leg_endpoint(hip_servo_angle, knee_servo_angle, L1, L2)
    x, y, z = x, y, -z
    hip_angle_rad = math.radians(hip_servo_angle)
    knee_angle_rad = math.radians(knee_servo_angle)

    for i in range(4):
        base_x, base_y, base_z = top_x[i], top_y[i], top_z[i]
        joint_x, joint_y = (L1 * math.cos(hip_angle_rad), L1 * math.sin(hip_angle_rad))
        if i == 0:
            joint_x, joint_y = joint_x, joint_y
            xa, ya = x, y
        elif i == 1:
            joint_x, joint_y = joint_y, joint_x
            xa, ya = y, x    
        elif i == 2:
            joint_x, joint_y = -joint_x, -joint_y
            xa, ya = -x, -y
        elif i == 3:
            joint_x, joint_y = -joint_y, -joint_x
            xa, ya = -y, -x
        x_coords = [base_x, base_x + joint_x, base_x + xa]
        y_coords = [base_y, base_y + joint_y, base_y + ya]
        z_coords = [base_z, base_z, z] 
        ax.plot(x_coords, y_coords, z_coords, color='blue', linewidth=2)
        ax.scatter(x_coords[0], y_coords[0], z_coords[0], color='red', s=25)
        ax.scatter(x_coords[1], y_coords[1], z_coords[1], color='red', s=25)
        ax.scatter(x_coords[-1], y_coords[-1], z_coords[-1], color='black', s=20)

    ax.view_init(elev=90, azim=0)
    ax.set_xlabel('X Axis')
    ax.set_ylabel('Y Axis')
    ax.set_title('Leg Plot with 9x9 Cube')
    ax.legend()
    ax.set_box_aspect([1, 1, 1])
    ax.grid(True)
    ax.set_xlim((-25, 25))
    ax.set_ylim((-25, 25))
    ax.set_zlim((-25, 25))
    ax.set_aspect('equal')
    plt.show()
