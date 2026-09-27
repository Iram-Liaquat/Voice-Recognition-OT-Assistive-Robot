# Differential Kinematics & Singularity Analysis

This document outlines the velocity kinematics (Jacobian matrix) of the 4-DOF manipulator and the identification of kinematic singularities. Understanding the Jacobian is critical for mapping joint-space velocities to Cartesian-space end-effector velocities, and for ensuring the robot operates safely away from singular configurations.

## 1. Velocity Kinematics & The Jacobian Matrix

 *Note: The differential kinematics formulation and Jacobian matrix derivation detailed in this section are based directly on the original thesis (Equations 5.1 – 5.12).*
 
The relationship between the joint velocities $\dot{q}$ and the end-effector linear ($v$) and angular ($\omega$) velocities is defined by the Jacobian matrix $J(q)$:

$$
\begin{bmatrix} v \\ \omega \end{bmatrix} = J(q) \dot{q}
$$

For a 6-DOF system, $J$ is a $6 \times 6$ matrix. However, for our **4-DOF manipulator**, the Jacobian is a **$6 \times 4$ matrix**, structured as:

$$
J(q) = \begin{bmatrix} J_1 & J_2 & J_3 & J_4 \end{bmatrix} = \begin{bmatrix} J_{v1} & J_{v2} & J_{v3} & J_{v4} \\ J_{w1} & J_{w2} & J_{w3} & J_{w4} \end{bmatrix}
$$

### Column Vector Formulation
Since all joints in this manipulator are **revolute**, the columns of the Jacobian are calculated using the following standard cross-product and vector formulas:

* **Linear Velocity Component:** $J_{vi} = z_{i-1} \times (o_4 - o_{i-1})$
* **Angular Velocity Component:** $J_{wi} = z_{i-1}$

Where:
* $z_{i-1}$ is the unit vector of the $z$-axis for frame $i-1$.
* $o_4$ is the position vector of the end-effector.
* $o_{i-1}$ is the position vector of the origin of frame $i-1$.

### Origin and Z-Axis Vectors
From the forward kinematics derivation, the origin vectors ($o_i$) and z-axis vectors ($z_i$) are extracted as:

$$
o_0 = o_1 = o_2 = \begin{bmatrix} 0 \\ 0 \\ 0 \end{bmatrix}, \quad 
o_4 = \begin{bmatrix} p_x \\ p_y \\ p_z \end{bmatrix}
$$

$$
z_0 = \begin{bmatrix} 0 \\ 0 \\ 1 \end{bmatrix}, \quad 
z_1 = \begin{bmatrix} 0 \\ 0 \\ 1 \end{bmatrix}, \quad 
z_2 = \begin{bmatrix} -s_1 \\ c_1 \\ 0 \end{bmatrix}, \quad 
z_3 = \begin{bmatrix} -s_1 \\ c_1 \\ 0 \end{bmatrix}
$$

By substituting these into the cross-product equations, the full $6 \times 4$ Jacobian matrix $J(q)$ is constructed, mapping the 4 joint velocities $(\dot{\theta}_1, \dot{\theta}_2, \dot{\theta}_3, \dot{\theta}_4)$ to the 6D Cartesian velocity space.

---

## 2. Kinematic Singularities

A kinematic singularity occurs when the manipulator loses one or more degrees of freedom in Cartesian space. Mathematically, this happens when the rank of the Jacobian matrix $J(q)$ drops below its maximum value (i.e., the determinant of the $6 \times 6$ sub-matrices becomes zero).

### Why Singularities Matter in System Design
Operating near a singularity is highly dangerous for robotic control systems:
1. **Unbounded Joint Velocities:** To maintain a bounded end-effector velocity, the joint velocities ($\dot{q} = J^{-1}(q) v$) approach infinity.
2. **Loss of Control:** The robot cannot move in certain Cartesian directions, regardless of how the joints move.
3. **Infinite Torques:** Bounded end-effector forces require infinite joint torques.

### Singularity Identification for the 4-DOF Arm
By analyzing the Jacobian matrix of this specific elbow-type manipulator, singularities typically occur at:
* **Workspace Boundaries:** When the arm is fully stretched out ($\theta_2 + \theta_3 = 0$ or $\pi$), the wrist center aligns with the shoulder joint, causing a loss of linear mobility in the direction of the arm.
* **Internal Singularities:** When the projection of the wrist center onto the base plane coincides with the base origin (typically when $\theta_1$ is undefined or the arm is pointing straight up/down).

**Engineering Mitigation:** 
In the trajectory planning phase (implemented via RoboAnalyzer and Arduino joint-space control), the workspace was restricted to ensure the manipulator operates strictly within the non-singular region, maintaining a healthy condition number for the Jacobian matrix during the 8-second pick-and-place cycle.

---

## 📚 References & Equation Citations

All mathematical formulations in this document are derived from the official B.Sc. thesis:

**Primary Source:**
> Baig, A. F., Ahmed, A., Liaquat, I., & Noor, S. (2019). *Voice Recognition based Operation Theatre Assistive Robot*. B.Sc. Thesis, Department of Mechatronics and Control Engineering, University of Engineering and Technology, Lahore (Faisalabad Campus).

**Equation References:**
- **Forward Kinematics**: Thesis Equations 4.1 - 4.13 (Chapter 4)
- **Jacobian Matrix**: Thesis Equations 5.1 - 5.12 (Chapter 5)
- **D-H Parameters**: Thesis Table 2.1 (Chapter 4)

**Standard Robotics Literature:**
1. R. K. Mittal and I. J. Nagrath, *Robotics and Control*. Tata McGraw-Hill, 2003.
2. M. W. Spong and M. Vidyasagar, *Robot Dynamics and Control*. John Wiley & Sons, 1989.
3. J. J. Craig, *Introduction to Robotics: Mechanics and Control*. Pearson Prentice Hall, 2005.
