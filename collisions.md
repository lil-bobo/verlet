# Résolution des collisions

$$
M(\delta t) = M(t) + k \times \vec{M(t) M(t +dt)}
$$

Soit $H$ le projeté de $M(\delta t)$ sur le plan

On résout pour l'inconnue $k$ et on suppose $\lVert M(\delta t) - H \rVert = r$ où $r$ est le rayon de la sphère.

$$
H = \vec{AM(\delta t)} - \frac{\langle \vec{AM(\delta t)}, \vec{n} \rangle}{\langle \vec{n},\vec{n} \rangle} \vec{n}
$$

Donc on développe :
$$
\lVert M(\delta t) - H \rVert = \sqrt{\langle M(\delta t) - H, M(\delta t) - H \rangle}
$$

$$
{\lVert M(\delta t) - H \rVert}^2 = \langle M(\delta t) - H, M(\delta t) - H \rangle \\ = \langle M(\delta t),  M(\delta t) - H \rangle - \langle H, M(\delta t) - H \rangle \\ = \langle M(\delta t), M(\delta t) \rangle - \langle M(\delta t), H \rangle - \langle H, M(\delta t) \rangle + \langle H, H \rangle \\ = {\lVert M(\delta t) \rVert}^2 - 2 \langle M(\delta t), H \rangle + {\lVert H \rVert}^2 \\ \\ = r
$$

Donc finalement on a :
$$
{\lVert M(\delta t) \rVert}^2 - 2 \langle M(\delta t), H \rangle + {\lVert H \rVert}^2 = r
$$

résolution numérique car c'est penible