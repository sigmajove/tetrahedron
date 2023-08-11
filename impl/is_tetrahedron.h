#ifndef g_1b49d29e_27e5_4287_bb43_8e22063c3b1b
#define g_1b49d29e_27e5_4287_bb43_8e22063c3b1b

// Returns whether six edge lengths form a valid tetrahedron.
// a, b, c are the sides of a triangular face, and a1, b1, c1 are
// the edges opposite a, b, c, respectively.
bool IsTetrahedron(double a, double b, double c,
                   double a1, double b1, double c1);

#endif // g_1b49d29e_27e5_4287_bb43_8e22063c3b1b