#ifndef g_ED887E56_7021_46AD_845E_751D4F869A49
#define g_ED887E56_7021_46AD_845E_751D4F869A49

// Returns whether six edge lengths form a valid tetrahedron.
// a, b, c are the sides of a triangular face, and a1, b1, c1 are
// the edges opposite a, b, c, respectively.
// Implementation uses the Scott Johnson's folding trick.
bool FoldIsTetrahedron(double a, double b, double c,
                      double a1, double b1, double c1);

#endif // g_ED887E56_7021_46AD_845E_751D4F869A49