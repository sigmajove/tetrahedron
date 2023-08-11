#ifndef g_2049987f_ab1e_4178_bef9_640a026898a4
#define g_2049987f_ab1e_4178_bef9_640a026898a4

// Returns whether six edge lengths form a valid tetrahedron.
// a, b, c are the sides of a triangular face, and a1, b1, c1 are
// the edges opposite a, b, c, respectively.
// Implementation uses the Cayley-Menginger Determinant.
bool CmdIsTetrahedron(double a, double b, double c,
                      double a1, double b1, double c1);

#endif // g_2049987f_ab1e_4178_bef9_640a026898a4
