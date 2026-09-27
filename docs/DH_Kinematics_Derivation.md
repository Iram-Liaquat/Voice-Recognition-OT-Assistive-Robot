# Forward Kinematics & Denavit-Hartenberg Derivation

This document details the mathematical modeling of the 4-DOF articulated robotic manipulator. The forward kinematics were derived using the Denavit-Hartenberg (D-H) convention and subsequently validated using **RoboAnalyzer 7** (IIT Delhi).

## 1. Denavit-Hartenberg (D-H) Parameter Table

The manipulator utilizes an **elbow-type articulated configuration**. Coordinate frames were assigned to each joint according to the standard D-H rules. The link lengths ($L_1$ to $L_4$) were determined based on the required planar workspace (1.5 x 1.5 ft) and operating table ergonomics (2.08 - 2.5 ft height).

| Link ($i$) | Link Length $a_i$ | Link Twist $\alpha_i$ | Link Offset $d_i$ | Joint Angle $\theta_i$ |
| :---: | :---: | :---: | :---: | :---: |
| **1** | $0$ | $-90^\circ$ | $L_1$ | $\theta_1^*$ |
| **2** | $L_2$ | $0^\circ$ | $0$ | $\theta_2^*$ |
| **3** | $L_3$ | $0^\circ$ | $0$ | $\theta_3^*$ |
| **4** | $L_4$ | $0^\circ$ | $0$ | $\theta_4^*$ |

$\theta_i$ represents the variable joint angle for link $i$.

---

## 2. Individual Homogeneous Transformation Matrices

Using the standard Denavit-Hartenberg transformation matrix formulation, the individual homogeneous transformation matrices for each joint are derived as follows:

**Notation:** Let $c_i = \cos(\theta_i)$ and $s_i = \sin(\theta_i)$

### Base to Link 1 ($T^0_1$)
$$
T^0_1 = \begin{bmatrix} 
c_1 & 0 & -s_1 & 0 \\ 
s_1 & 0 & c_1 & 0 \\ 
0 & -1 & 0 & L_1 \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
$$

### Link 1 to Link 2 ($T^1_2$)
$$
T^1_2 = \begin{bmatrix} 
c_2 & -s_2 & 0 & L_2 c_2 \\ 
s_2 & c_2 & 0 & L_2 s_2 \\ 
0 & 0 & 1 & 0 \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
$$

### Link 2 to Link 3 ($T^2_3$)
$$
T^2_3 = \begin{bmatrix} 
c_3 & -s_3 & 0 & L_3 c_3 \\ 
s_3 & c_3 & 0 & L_3 s_3 \\ 
0 & 0 & 1 & 0 \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
$$

### Link 3 to Link 4 / End-Effector ($T^3_4$)
$$
T^3_4 = \begin{bmatrix} 
c_4 & -s_4 & 0 & L_4 c_4 \\ 
s_4 & c_4 & 0 & L_4 s_4 \\ 
0 & 0 & 1 & 0 \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
$$

---

## 3. Total Transformation Matrix

The total transformation matrix $T^0_4$, which defines the position and orientation of the end-effector relative to the base frame, is obtained by multiplying the individual matrices:

$$
T^0_4 = T^0_1 \cdot T^1_2 \cdot T^2_3 \cdot T^3_4 = \begin{bmatrix} 
m_x & n_x & o_x & p_x \\ 
m_y & n_y & o_y & p_y \\ 
m_z & n_z & o_z & p_z \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
$$

### Expanded Kinematic Equations

By performing the matrix multiplications, the orientation vectors $(m, n, o)$ and position vector $(p)$ are expanded as follows:

**Orientation Vector $m$ (X-axis of end-effector):**

$$m_x = c_4(c_1 c_2 c_3 - c_1 s_2 s_3) - s_4(c_1 c_2 s_3 + c_1 c_3 s_2)$$

$$m_y = c_4(c_2 c_3 s_1 - s_1 s_2 s_3) - s_4(c_2 s_1 s_3 + c_3 s_1 s_2)$$

$$m_z = -c_4(c_2 s_3 + c_3 s_2) - s_4(c_2 c_3 - s_2 s_3)$$

**Orientation Vector $n$ (Y-axis of end-effector):**

$$n_x = -c_4(c_1 c_2 s_3 + c_1 c_3 s_2) - s_4(c_1 c_2 c_3 - c_1 s_2 s_3)$$

$$n_y = -c_4(c_2 s_1 s_3 + c_3 s_1 s_2) - s_4(c_2 c_3 s_1 - s_1 s_2 s_3)$$

$$n_z = s_4(c_2 s_3 + c_3 s_2) - c_4(c_2 c_3 - s_2 s_3)$$

**Orientation Vector $o$ (Z-axis of end-effector):**

$$o_x = -s_1$$

$$o_y = c_1$$

$$o_z = 0$$

**Position Vector $p$ (Origin of end-effector):**

$$p_x = c_1 c_2 L_2 - c_4 L_4(c_1 c_2 s_3 + c_1 c_3 s_2) + c_4 L_4(c_1 c_2 c_3 - c_1 s_2 s_3) - c_1 c_3 L_3 s_2 + c_1 c_2 c_3 L_3$$

$$p_y = c_2 L_2 s_1 - c_4 L_4(c_2 s_1 s_3 + c_3 s_1 s_2) + c_4 L_4(c_2 c_3 s_1 - s_1 s_2 s_3) + c_2 c_3 L_3 s_1 - c_3 L_3 s_1 s_2$$

$$p_z = L_1 - L_2 s_2 - c_2 c_3 L_3 - c_3 L_3 s_2 - c_4 L_4(c_2 s_3 + c_3 s_2) - c_4 L_4(c_2 c_3 - s_2 s_3)$$

---

### Inverse Kinematics Equations

**Base Joint Angle (`θ₁`):**

$$
\theta_1 = \tan^{-1}\left(\frac{y}{x}\right)
$$

**Auxiliary Angle (`K`):**

$$
K =
\cos^{-1}
\left(
\frac{z-l_1}{\sqrt{x^2+y^2}}
\right)
$$

**Auxiliary Angle (`P`):**

$$
P =
\cos^{-1}
\left(
\frac{
l_2^2-l_3^2+x^2+y^2+z^2+l_1^2-(2xz l_1)
}{
2x l_2
\sqrt{x^2+y^2+z^2+l_1^2-(2xz l_1)}
}
\right)
$$

Where, $x$, $y$, and $z$ represent the coordinates. $l_1$, $l_2$, and $l_3$ represent the link lengths of the base, shoulder, and elbow, respectively.

**Shoulder Joint Angle (`θ₂`):**

$$
\theta_2 = K-P
$$

**Fourth Joint Angle (`θ₄`):**

$$
\theta_4 =
\left(
\frac{
z-l_1-l_2x\sin(\theta_2)
}{
\sqrt{x^2+y^2}-\cos(\theta_2)
}
\right)
-\theta_2
$$

**Transformation Matrix:**

$$
T_3^6 =
\begin{bmatrix}
r_{11} & r_{12} & r_{13} & r_{14} \\
r_{21} & r_{22} & r_{23} & r_{24} \\
r_{31} & r_{32} & r_{33} & r_{34} \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

**Third Joint Angle (`θ₃`):**

$$
\theta_3 =
\mathrm{atan2}
\left(
\frac{r_{23}}{\sin(\theta_4)},
\frac{r_{13}}{\sin(\theta_4)}
\right)
$$
